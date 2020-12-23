/**
 * @file      usb.c
 * @brief     USB driver
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles. GNU GPL v3 (see LICENSE)
 *
 * This module interfaces with the USB peripheral to establish basic USB HID communications with
 * host.
 *
 * Endpoint 0 -> Control
 * Endpoint 1 -> Interrupt, TX only
 */

#include "usb/usb.h"

#include <stdbool.h>

#include "stm32f0xx.h"
#include "usb/usb_descriptors.h"
#include "util/debug.h"
#include "util/macros.h"

// Total number of EPs used
#define NUM_EP (2)

// Buffer descriptor table offset in PMA
#define BDT_OFFSET (0x0000U)

// Mask for getting # of bytes received in packet
#define USB_CNT_RX_MSK (0x03FF)

// EP0 BDT entry (TX_SIZE is filled right before transmission)
#define TX0_ADDR (0x0080U)
#define RX0_ADDR (0x0100U)
#define RX0_CNT  (0x8400U)  // BL_SIZE = 1, NUM_BLOCK = 2, Total size = 64 bytes

// EP1 BDT entry (TX only)
#define TX1_ADDR (0x0180U)

// SETUP packet bmRequestType[7]
#define REQ_DIR_IN   (0x80U)
#define REQ_DIR_OUT  (0x00U)

// SETUP packet bmRequestType[6:5]
#define REQ_TYP_STD  (0x00U)
#define REQ_TYP_CLS  (0x20U)
#define REQ_TYP_VDR  (0x40U)

// SETUP packet bmRequestType[4:0]
#define REQ_RCP_DEV  (0x00U)
#define REQ_RCP_ITF  (0x01U)
#define REQ_RCP_EP   (0x02U)

// Entire bmRequestType field
#define REQ_IN_STD_DEV  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_DEV)
#define REQ_IN_STD_ITF  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_ITF)
#define REQ_OUT_CLS_ITF (REQ_DIR_OUT | REQ_TYP_CLS | REQ_RCP_ITF)
#define REQ_OUT_STD_DEV (REQ_DIR_OUT | REQ_TYP_STD | REQ_RCP_DEV)
#define REQ_OUT_STD_EP  (REQ_DIR_OUT | REQ_TYP_STD | REQ_RCP_EP)

// SETUP packet bRequest
#define REQ_GET_STAT (0x00U)
#define REQ_CLR_STAT (0x01U)
#define REQ_SET_ADDR (0x05U)
#define REQ_GET_DESC (0x06U)
#define REQ_SET_CFG  (0x09U)
#define REQ_SET_IDLE (0x0AU)
#define REQ_SET_RPT  (0x09U)

//  -------------------------------------------------------------------
// |    THIS MONUMENT MARKS THE SPOT AT WHICH I WAS STUCK FOR WEEKS    |
// |       UNTIL I REALIZED I FORGOT THIS WAS POINTER ARITHMETIC       |
// |      AND HAD "2U" INSTEAD OF "1U", SO EP1 WAS NOT BEING SET       |
//  -------------------------------------------------------------------
#define EP_REG(epn) (*((&USB->EP0R) + (epn << 1U)))

// Combines SETUP packet bRequest/bmRequestType fields
#define REQ(type, req) (((uint16_t)(type) << 8) | ((uint16_t)(req) & 0xFF))

// Set the TX_STATUS EP register bits (they are toggle-bits)
#define SET_TX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPTX_STAT)) & (USB_EPREG_MASK | USB_EPTX_STAT));

// Set the RX_STATUS EP register bits (they are toggle-bits)
#define SET_RX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPRX_STAT)) & (USB_EPREG_MASK | USB_EPRX_STAT));

#define PRINT_SETUP(pkt) \
    DbgPrintf("%02x %02x %04x %04x %04x ", pkt.bmRequestType, pkt.bRequest, pkt.wValue, \
        pkt.wIndex, pkt.wLength);

// SETUP packet as it will appear in memory
typedef struct {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_setup_packet_t __PACKED;

// Buffer descriptor table entry as it will appear in memory
typedef struct {
    uint16_t tx_addr;
    uint16_t tx_size;
    uint16_t rx_addr;
    uint16_t rx_size;
} buf_desc_t __PACKED;

// Entire buffer descriptor table
typedef struct {
    buf_desc_t bd_ep[NUM_EP];
} buf_desc_table_t;

// The buffer descriptor table itself, at the given offset
static volatile buf_desc_table_t *const BDT =
    (buf_desc_table_t *const)(USB_PMAADDR + BDT_OFFSET);

// EP0 tx buffer in the PMA memory space
static volatile uint8_t *const ep0_tx =
    (volatile uint8_t *const)(USB_PMAADDR + TX0_ADDR);

// EP0 rx buffer in the PMA memory space
static volatile uint8_t *const ep0_rx =
    (volatile uint8_t *const)(USB_PMAADDR + RX0_ADDR);

// EP1 tx buffer in the PMA memory space
static volatile uint8_t *const ep1_tx =
    (volatile uint8_t *const)(USB_PMAADDR + TX1_ADDR);

static void usbReset(void);
static void usbEP0Init(void);
static void usbEP1Init(void);
static void usbEP0Setup(void);
static void usbEP0Read(uint8_t *in_buf);

/**
 * @brief Performs USB port, clock, and peripheral initialization
 *
 * USB port is used in startup (for DFU), so the ports come up configured. Host detects device upon
 * DP pullup enable.
 */
void USBInit(void)
{
    // Disble embedded pullup on DP
    USB->BCDR &= ~USB_BCDR_DPPU;

    // Set USB clock source from PLL, enable USB clocking
    RCC->CFGR3   |= RCC_CFGR3_USBSW;
    RCC->APB1ENR |= RCC_APB1ENR_USBEN;

    // Ensure USB clock is set
    while ((RCC->APB1ENR & RCC_APB1ENR_USBEN_Msk) != RCC_APB1ENR_USBEN) {};

    // Exit USB power down
    USB->CNTR &= ~USB_CNTR_PDWN;

    // Startup can take a max of 1us
    //nop_delay(50);

    // Clear peripheral reset
    USB->CNTR = USB_CNTR_FRES;

    // Clear interrupt register
    USB->ISTR = 0;

    // Clear any existing USB interrupts
    NVIC_ClearPendingIRQ(USB_IRQn);

    // Enable USB interrupts
    NVIC_EnableIRQ(USB_IRQn);

    // Enable the USB reset interrupt
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_ERRM;

    // Enable embedded pullup on DP
    USB->BCDR |= USB_BCDR_DPPU;

    DbgPrintf("Initialized: USB\r\n");
}

/**
 * @brief Write data from input buffer into PMA, set TX byte count, and set TX STATUS to VALID
 *
 * Due to a bug when writing bytes into the PMA, only halfword accesses work. So `len` will
 * need to always be even (and `buf` an even number of bytes).
 *
 * Only works because MCU architecture and USB protocol is little endian.
 *
 * @param[in] ep  the endpoint to write with
 * @param[in] buf input buffer that contains data to be tranmitted
 * @param[in] len number of bytes in `buf`
 */
void USBWrite(int ep, const uint8_t *buf, uint16_t len)
{
    BDT->bd_ep[ep].tx_size = len;

    switch (ep) {
    case 0:
        for (int i = 0; i < len/2; ++i) {
            ((uint16_t *)ep0_tx)[i] = ((uint16_t *)buf)[i];
        }
        break;
    case 1:
        for (int i = 0; i < len/2; ++i) {
            ((uint16_t *)ep1_tx)[i] = ((uint16_t *)buf)[i];
        }
        break;
    default:
        return;
    }

    SET_TX_STATUS(ep, USB_EP_TX_VALID);
}

/**
 * @brief Initialize endpoint 0 as control endpoint
 *
 * Set buffer locations/sizes in the PMA for transmission and reception.
 */
static void usbEP0Init(void)
{
    EP_REG(0) = USB_EP_CONTROL | (0 & USB_EPADDR_FIELD);

    // set our TX and RX PMA addresses
    BDT->bd_ep[0].tx_addr = TX0_ADDR;
    BDT->bd_ep[0].rx_addr = RX0_ADDR;

    // set max # of bytes to RX (64)
    BDT->bd_ep[0].rx_size = RX0_CNT;

    SET_RX_STATUS(0, USB_EP_RX_VALID);
}

/**
 * @brief Initialize endpoint 1 as interrupt endpoint
 *
 * Set buffer locations/sizes in the PMA for transmission only.
 */
static void usbEP1Init(void)
{
    EP_REG(1) = USB_EP_INTERRUPT | (1 & USB_EPADDR_FIELD);

    // set our TX and RX PMA addresses
    BDT->bd_ep[1].tx_addr = TX1_ADDR;
    BDT->bd_ep[1].tx_size = 4;

    // we NAK until we get something to send
    SET_TX_STATUS(1, USB_EP_TX_NAK);
}

/**
 * @brief Read RX byte count sized block from PMA into input buffer and set RX STATUS to VALID
 *
 * @param[in, out] buf output buffer that is filled with received data
 */
static void usbEP0Read(uint8_t *buf) {
    int rx_size = BDT->bd_ep[0].rx_size & USB_CNT_RX_MSK;

    for (int i = 0; i < rx_size; ++i) {
        buf[i] = ep0_rx[i];
    }

    SET_RX_STATUS(0, USB_EP_RX_VALID);
}

/**
 * @brief Handle SETUP packet
 *
 * Called when a CTR interrupt is received, and CTR_RX and SETUP field in the endpoint 0 register
 * (control ep) are set, indicating a SETUP packet has been received. This is read into a buffer,
 * then the request contained in the packet is handled.
 */
static void usbEP0Setup(void)
{
    int ret = -1;
    usb_setup_packet_t setup_pkt;
    usb_desc_t         desc;

    // get the setup packet contents
    usbEP0Read((uint8_t *)&setup_pkt);
    PRINT_SETUP(setup_pkt);

    // determine request type, and proceed accordingly
    switch(REQ(setup_pkt.bmRequestType, setup_pkt.bRequest)) {

    // handle both device and interface get descriptor
    case REQ(REQ_IN_STD_DEV, REQ_GET_DESC):
    case REQ(REQ_IN_STD_ITF, REQ_GET_DESC):
        DbgPrintf("GET DESC ");

        if (setup_pkt.wValue == 0x100) {
            DbgPrintf("DEV ");
            ret = USBGetDescriptor(DESCRIPTOR_DEVICE_ID,    &desc);
        } else if (setup_pkt.wValue == 0x200) {
            DbgPrintf("CFG ");
            ret = USBGetDescriptor(DESCRIPTOR_CONFIG_ID,    &desc);

            // TODO: Windows gives 255 for "compatability reasons"
            desc.size = (setup_pkt.wLength == 0xff) ? desc.size : setup_pkt.wLength;
        } else if (setup_pkt.wValue == 0x300) {
            DbgPrintf("STR0 ");
            ret = USBGetDescriptor(DESCRIPTOR_LANG_ID,      &desc);
        } else if (setup_pkt.wValue == 0x301) {
            DbgPrintf("STR1 ");
            ret = USBGetDescriptor(DESCRIPTOR_MANUFACT_ID,  &desc);
        } else if (setup_pkt.wValue == 0x302) {
            DbgPrintf("STR2 ");
            ret = USBGetDescriptor(DESCRIPTOR_PRODUCT_ID,   &desc);
        } else if (setup_pkt.wValue == 0x2200) {
            DbgPrintf("RPT ");

            // TODO: why the hell does Windows request twice the size
            if (setup_pkt.wLength == 0x80) {
                ret = USBGetDescriptor(DESCRIPTOR_HIDREPORT_ID, &desc);
                USBWrite(0, desc.buf_ptr, desc.size);
                LOOP_DELAY(1000);
            }
        } else {
            // Stall for unknown descriptors
            DbgPrintf("0x%04x? (STALLING) ", setup_pkt.wValue);
            SET_RX_STATUS(0, USB_EP_RX_STALL);
            SET_TX_STATUS(0, USB_EP_TX_STALL);
        }

        if (ret >= 0) {
            USBWrite(0, desc.buf_ptr, desc.size);
        }
        break;

    // this is a class-specific request
    case REQ(REQ_OUT_CLS_ITF, REQ_SET_IDLE):
        DbgPrintf("SET IDLE ");
        break;

    // this is a class-specific request
    case REQ(REQ_OUT_CLS_ITF, REQ_SET_RPT):
        DbgPrintf("SET RPT ");
        break;

    // device has been addressed
    case REQ(REQ_OUT_STD_DEV, REQ_SET_ADDR):
        DbgPrintf("SET ADDR ");

        // Send 0 length packet with address 0
        USBWrite(0, 0, 0);

        // TODO: determine required delay
        LOOP_DELAY(1000);

        // Set device address to new address
        USB->DADDR |= setup_pkt.wValue & USB_DADDR_ADD;
        SET_RX_STATUS(0, USB_EP_RX_VALID);
        break;

    // our device has now been configured, can use ep1 now
    case REQ(REQ_OUT_STD_DEV, REQ_SET_CFG):
        DbgPrintf("SET CFG (%x) ", setup_pkt.wValue);
        USBWrite(0, 0, 0);
        usbEP1Init();
        break;

    // host request status
    case REQ(REQ_IN_STD_DEV, REQ_GET_STAT):
    {
        const uint8_t status[] = { 0x01, 0x00 }; // self powered
        DbgPrintf("GET STAT ");
        USBWrite(0, status, sizeof(status));
        break;
    }

    // clearing an endpoint feature (always ENDPOINT_HALT)
    case REQ(REQ_OUT_STD_EP, REQ_CLR_STAT):
        DbgPrintf("CLR STAT ");
        break;

    default:
        DbgPrintf("UNKNOWN REQUEST ");
        break;
    }
}

/**
 * @brief Handle RESET request
 *
 * Called when reset interrupt recieved. Restores peripheral to known starting state, with address
 * 0. Only EP0 (control ep) is initialized. SETUP packets should follow.
 */
static void usbReset(void)
{
    // clear interrupts
    USB->ISTR = 0;

    // set our BDT offset in PMA
    USB->BTABLE = BDT_OFFSET;

    usbEP0Init();

    // enable reset/transfer interrupts
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_ERRM | USB_CNTR_RESETM;

    // enable device with address 0
    USB->DADDR = USB_DADDR_EF;
}

/**
 * @brief Route USB events
 *
 * Routes module function based on received interrupts. Most are ignored, except RESET and CTR.
 */
void USB_IRQHandler(void)
{
    uint16_t ep_reg;
    uint16_t int_reg = USB->ISTR;
    uint16_t int_ep = (int_reg & USB_ISTR_EP_ID);

    DbgPrintf("> EP%d %s: ", int_ep, (int_reg & USB_ISTR_DIR) ? "IN " : "OUT");

    if (int_reg & USB_ISTR_PMAOVR) {
        USB->ISTR = ~USB_ISTR_PMAOVR;
        DbgPrintf("PMAOVR ");
    }

    if (int_reg & USB_ISTR_ERR) {
        USB->ISTR = ~USB_ISTR_ERR;
        DbgPrintf("ERR ");
    }

    if (int_reg & USB_ISTR_WKUP) {
        USB->ISTR = ~USB_ISTR_WKUP;
        DbgPrintf("WKUP ");
    }

    if (int_reg & USB_ISTR_SUSP) {
        USB->ISTR = ~USB_ISTR_SUSP;
        DbgPrintf("SUSP ");
    }

    if (int_reg & USB_ISTR_RESET) {
        usbReset();
        USB->ISTR = ~USB_ISTR_RESET;
        DbgPrintf("RESET ");
    }

    if (int_reg & USB_ISTR_SOF) {
        USB->ISTR = ~USB_ISTR_SOF;
    }

    if (int_reg & USB_ISTR_ESOF) {
        USB->ISTR = ~USB_ISTR_ESOF;
        DbgPrintf("ESOF ");
    }

    if (int_reg & USB_ISTR_L1REQ) {
        USB->ISTR = ~USB_ISTR_L1REQ;
        DbgPrintf("L1REQ ");
    }

    if (int_reg & USB_ISTR_CTR) {
        DbgPrintf("CTR ");
        ep_reg = EP_REG(int_ep);

        if (ep_reg & USB_EP_CTR_RX) {
            DbgPrintf("RX ");

            if (ep_reg & USB_EP_SETUP) {
                DbgPrintf("SETUP ");
                usbEP0Setup();
            }
            EP_REG(int_ep) = ep_reg & USB_EPREG_MASK & ~USB_EP_CTR_RX;
        }

        if (ep_reg & USB_EP_CTR_TX) {
            DbgPrintf("TX ");
            EP_REG(int_ep) = ep_reg & USB_EPREG_MASK & ~USB_EP_CTR_TX;
        }
    }

    DbgPrintf("\r\n");
}
