/**
 * @file      usb.c
 * @brief     USB driver
 *
 * @author    Anthony Needles
 * @date      2020/11/02
 * @copyright (c) 2020 Anthony Needles
 * @license   GNU GPL v3 (see LICENSE)
 *
 * This module interfaces with the USB peripheral to establish basic USB HID communications with
 * host.
 *
 * Endpoint 0 -> Control
 * Endpoint 1 -> Interrupt, TX only
 */

#include "usb.h"

#include <stdbool.h>

#include "debug.h"
#include "macros.h"
#include "stm32f0xx.h"
#include "usb_descriptors.h"

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

// SETUP packet bRequest
#define REQ_GET_DESC (0x06U)
#define REQ_SET_ADDR (0x05U)
#define REQ_SET_CFG  (0x09U)
#define REQ_SET_IDLE (0x0AU)
#define REQ_SET_RPT  (0x09U)

// Entire bmRequestType field
#define REQ_IN_STD_DEV  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_DEV)
#define REQ_IN_STD_ITF  (REQ_DIR_IN  | REQ_TYP_STD | REQ_RCP_ITF)
#define REQ_OUT_CLS_ITF (REQ_DIR_OUT | REQ_TYP_CLS | REQ_RCP_ITF)
#define REQ_OUT_STD_DEV (REQ_DIR_OUT | REQ_TYP_STD | REQ_RCP_DEV)

// Obtains endpoint register for ep identifier 'epn'
#define EP_REG(epn) (*((&USB->EP0R) + (epn << 2U)))

// Combines SETUP packet bRequest/bmRequestType fields
#define REQ(type, req) (((uint16_t)(type) << 8) | ((uint16_t)(req) & 0xFF))

#define SET_TX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPTX_STAT)) & (USB_EPREG_MASK | USB_EPTX_STAT));

#define SET_RX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPRX_STAT)) & (USB_EPREG_MASK | USB_EPRX_STAT));

#define PRINT_EPNR(x) \
    DbgPrintf("[%04x: %x %x %x  %x %x %x  %x %x %x  %x]\n", x, \
        (x & 0x8000) >> 15, (x & 0x4000) >> 14, (x & 0x3000) >> 12, \
        (x & 0x0800) >> 11, (x & 0x0600) >> 9,  (x & 0x0100) >> 8, \
        (x & 0x0080) >> 7,  (x & 0x0040) >> 6,  (x & 0x0030) >> 4, \
        (x & 0x000F));

#define PRINT_SETUP(x) \
    DbgPrintf("%02x %02x %04x %04x %04x ", setup_pkt.bmRequestType,\
        setup_pkt.bRequest, setup_pkt.wValue, \
        setup_pkt.wIndex, setup_pkt.wLength);

// SETUP packet as it will appear in memory
typedef struct __PACKED {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_setup_packet_t;

// Buffer descriptor table entry as it will appear in memory
typedef struct __PACKED {
    uint16_t tx_addr;
    uint16_t tx_size;
    uint16_t rx_addr;
    uint16_t rx_size;
} buf_desc_t;

// Entire buffer descriptor table
typedef struct {
    buf_desc_t bd_ep[NUM_EP];
} buf_desc_table_t;

static volatile buf_desc_table_t *const BDT =
    (buf_desc_table_t *const)(USB_PMAADDR + BDT_OFFSET);

static volatile uint8_t *const ep0_tx =
    (volatile uint8_t *const)(USB_PMAADDR + TX0_ADDR);

static volatile uint8_t *const ep0_rx =
    (volatile uint8_t *const)(USB_PMAADDR + RX0_ADDR);

static volatile uint8_t *const ep1_tx =
    (volatile uint8_t *const)(USB_PMAADDR + TX1_ADDR);

static void usb_reset(void);
static void usb_ep0_init(void);
static void usb_ep0_setup(void);
static void usb_read(uint8_t *in_buf);
static void usb_write(const uint8_t *out_buf, uint16_t len);

static bool usb_configured = false;

/*
 * USBInit
 *
 * @brief: Performs USB port, clock, and peripheral initialization
 *
 * USB port is used in startup (for DFU), so the ports come up configured. Host detects device upon
 * DP pullup enable.
 */
void USBInit(void)
{
    // Enable GPIOA clocking
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // PA15 into AF mode
    GPIOA->MODER = ((GPIOA->MODER & ~GPIO_MODER_MODER15_Msk)
            | GPIO_MODER_MODER15_1);

    // PA15 fast output speed
    GPIOA->OSPEEDR = ((GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEEDR15_Msk)
            | GPIO_OSPEEDR_OSPEEDR15);

    // PA15 into AF5 (USB_NOE)
    GPIOA->AFR[1] = ((GPIOA->AFR[1] & ~GPIO_AFRH_AFSEL15_Msk)
            | (5U << GPIO_AFRH_AFSEL15_Pos));

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

    // Clear interrupts
    USB->ISTR = 0;

    // Enable USB interrupts
    NVIC_ClearPendingIRQ(USB_IRQn);

    // Enable USB interrupts
    NVIC_EnableIRQ(USB_IRQn);

    // Enable the USB reset interrupt
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_ERRM;

    // Enable embedded pullup on DP
    USB->BCDR |= USB_BCDR_DPPU;

    DbgPrintf("Initialized: USB\r\n");
}

/*
 * usb_ep0_init
 *
 * @brief Initialize endpoint 0 as control endpoint
 *
 * Set buffer locations/sizes in the PMA for transmission and reception.
 */
static void usb_ep0_init(void)
{
    EP_REG(0) = USB_EP_CONTROL | (0 & USB_EPADDR_FIELD);

    // Set our TX and RX PMA addresses
    BDT->bd_ep[0].tx_addr = TX0_ADDR;
    BDT->bd_ep[0].rx_addr = RX0_ADDR;

    // Set max # of bytes to RX (64)
    BDT->bd_ep[0].rx_size = RX0_CNT;

    SET_RX_STATUS(0, USB_EP_RX_VALID);
}

/*
 * usb_ep1_init
 *
 * @brief Initialize endpoint 1 as control endpoint
 *
 * Set buffer locations/sizes in the PMA for transmission only.
 */
static void usb_ep1_init(void)
{
    EP_REG(1) = USB_EP_INTERRUPT | (1 & USB_EPADDR_FIELD);

    // Set our TX and RX PMA addresses
    BDT->bd_ep[1].tx_addr = TX1_ADDR;
    BDT->bd_ep[1].tx_size = 8;
}

/*
 * usb_read
 *
 * @brief Read RX byte count sized block from PMA into input buffer and set RX STATUS to VALID
 *
 * @param[in, out] buf output buffer that is filled with received data
 */
static void usb_read(uint8_t *buf) {
    int rx_size = BDT->bd_ep[0].rx_size & USB_CNT_RX_MSK;
    //DbgPrintf("%02x BYTES ", rx_size);

    for (int i = 0; i < rx_size; ++i) {
        buf[i] = ep0_rx[i];
    }

    SET_RX_STATUS(0, USB_EP_RX_VALID);
}

/*
 * usb_write
 *
 * @brief Write data from input buffer into PMA, set TX byte count, and set TX STATUS to VALID
 *
 * @param[in] buf input buffer that contains data to be tranmitted
 * @param[in] len number of bytes in @buf
 */
static void usb_write(const uint8_t *buf, uint16_t len) {
    BDT->bd_ep[0].tx_size = len;
    //DbgPrintf("%02x BYTES ", len);

    for (int i = 0; i < len/2; ++i) {
        ((uint16_t *)ep0_tx)[i] = ((uint16_t *)buf)[i];
    }

    SET_TX_STATUS(0, USB_EP_TX_VALID);
}

/*
 * usb_ep0_setup
 *
 * @brief Handle SETUP packet
 *
 * Called when a CTR interrupt is received, and CTR_RX and SETUP field in the endpoint 0 register
 * (control ep) are set, indicating a SETUP packet has been received. This is read into a buffer,
 * then the request contained in the packet is handled.
 */
static void usb_ep0_setup(void)
{
    usb_setup_packet_t setup_pkt;
    usb_read((uint8_t *)&setup_pkt);
    PRINT_SETUP(setup_pkt);

    // Determine request type, and proceed accordingly
    switch(REQ(setup_pkt.bmRequestType, setup_pkt.bRequest)) {
    case REQ(REQ_IN_STD_DEV, REQ_GET_DESC):
        DbgPrintf("GET DESC ");

        if (setup_pkt.wValue == 0x100) {
            DbgPrintf("DEV ");
            usb_write(USBDesc_Device, setup_pkt.wLength);
        } else if (setup_pkt.wValue == 0x200) {
            DbgPrintf("CFG ");
            usb_write(USBDesc_Config, setup_pkt.wLength);
        } else if (setup_pkt.wValue == 0x300) {
            DbgPrintf("STR0 ");
            usb_write(USBDesc_Lang, sizeof(USBDesc_Lang));
        } else if (setup_pkt.wValue == 0x301) {
            DbgPrintf("STR1 ");
            usb_write(USBDesc_Manufact, sizeof(USBDesc_Manufact));
        } else if (setup_pkt.wValue == 0x302) {
            DbgPrintf("STR2 ");
            usb_write(USBDesc_Product, sizeof(USBDesc_Product));
        } else {
            // Stall for unknown descriptors
            DbgPrintf("0x%04x? (STALLING) ", setup_pkt.wValue);
            SET_RX_STATUS(0, USB_EP_RX_STALL);
            SET_TX_STATUS(0, USB_EP_TX_STALL);
        }
        break;

    case REQ(REQ_IN_STD_ITF, REQ_GET_DESC):
        DbgPrintf("GET DESC ");

        if (setup_pkt.wValue == 0x2200) {
            DbgPrintf("RPT ");
            usb_write(USBDesc_HIDReport, sizeof(USBDesc_HIDReport));
            usb_configured = true;
            SET_TX_STATUS(1, USB_EP_TX_NAK);
        } else {
            // Stall for unknown descriptors
            DbgPrintf("0x%04x? (STALLING) ", setup_pkt.wValue);
            SET_RX_STATUS(0, USB_EP_RX_STALL);
            SET_TX_STATUS(0, USB_EP_TX_STALL);
        }
        break;

    case REQ(REQ_OUT_CLS_ITF, REQ_SET_IDLE):
        DbgPrintf("SET IDLE ");
        usb_write(0, 0);
        break;

    case REQ(REQ_OUT_CLS_ITF, REQ_SET_RPT):
        DbgPrintf("SET RPT ");
        usb_write(0, 0);
        break;

    case REQ(REQ_OUT_STD_DEV, REQ_SET_ADDR):
        DbgPrintf("SET ADDR ");

        // Send 0 length packet with address 0
        usb_write(0, 0);

        // TODO: determine required delay
        LOOP_DELAY(500);

        // Set device address to new address
        USB->DADDR |= setup_pkt.wValue & USB_DADDR_ADD;
        SET_RX_STATUS(0, USB_EP_RX_VALID);
        break;

    case REQ(REQ_OUT_STD_DEV, REQ_SET_CFG):
        DbgPrintf("SET CFG (%x) ", setup_pkt.wValue);
        usb_write(0, 0);
        SET_TX_STATUS(1, USB_EP_TX_VALID);
        break;

    default:
        DbgPrintf("UNKNOWN REQUEST ");
        break;
    }
}

/*
 * usb_reset
 *
 * @brief Handle RESET request
 *
 * Called when reset interrupt recieved. Restores peripheral to known starting state, with address
 * 0. Only EP0 (control ep) is initialized. SETUP packets should follow.
 */
static void usb_reset(void)
{
    // Clear interrupts
    USB->ISTR = 0;

    // Set our BDT offset in PMA
    USB->BTABLE = BDT_OFFSET;

    usb_ep0_init();
    usb_ep1_init();

    // Enable reset/transfer interrupts
    USB->CNTR = USB_CNTR_RESETM | USB_CNTR_ERRM | USB_CNTR_RESETM;

    // Enable device with address 0
    USB->DADDR = USB_DADDR_EF;
}

/*
 * USB_IRQHandler()
 *
 * @brief Route USB events
 *
 * Routes module function based on received interrupts. Most are ignored, except RESET and CTR.
 */
void USB_IRQHandler(void)
{
    uint16_t ep_reg;
    uint16_t int_reg = USB->ISTR;
    uint16_t int_ep = (int_reg & USB_ISTR_EP_ID);
    char c = (int_reg & USB_ISTR_DIR) ? 'R' : 'T';

    DbgPrintf("INT %x %c: ", int_reg & 0x000F, c);

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
        USB->ISTR = ~USB_ISTR_RESET;
        DbgPrintf("RESET ");
        usb_reset();
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
                usb_ep0_setup();
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
