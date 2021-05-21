/**
 * @file      usb.cpp
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

#include "usb/usb.hpp"

#include <stdbool.h>

#include "usb/usb_definitions.hpp"
#include "usb/usb_descriptors.hpp"
#include "util/bitop.hpp"
#include "util/debug.hpp"
#include "util/macros.hpp"
#include "stm32f0xx.h"  // NOLINT

// usb handler needs C linkage
extern "C" void USB_IRQHandler(void);

// Total number of EPs used
#define NUM_EP (2)

// Buffer descriptor table offset in PMA
#define BDT_OFFSET (0x0000U)

// Value to set into USB_COUNTn_RX BDT register to set max bytes to receive
#define RX_MAX_64BYTES  (0x8400U)  // BL_SIZE = 1, NUM_BLOCK = 2, Total size = 64 bytes
#define RX_MAX_0BYTES   (0x0000U)  // BL_SIZE = 0, NUM_BLOCK = 0, Total size =  0 bytes

// Mask for getting # of bytes received in packet from USB_COUNTn_RX BDT register
#define RX_CNT_MSK (0x03FF)

// set tx/rx pointer to this if no data is sent/received
#define NO_PMA_USE (0)

// access a specific EP register
#define EP_REG(epn) (*((&USB->EP0R) + (epn << 1U)))

// Set the TX_STATUS EP register bits (they are toggle-bits)
#define SET_TX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPTX_STAT)) & (USB_EPREG_MASK | USB_EPTX_STAT));

// Set the RX_STATUS EP register bits (they are toggle-bits)
#define SET_RX_STATUS(epn, status) \
    (EP_REG(epn) = (EP_REG(epn) ^ (status & USB_EPRX_STAT)) & (USB_EPREG_MASK | USB_EPRX_STAT));

// SETUP packet as it will appear in memory
typedef struct {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __PACKED usb_setup_packet_t;

// Buffer descriptor table entry as it will appear in memory
typedef struct {
    uint16_t tx_addr;
    uint16_t tx_size;
    uint16_t rx_addr;
    uint16_t rx_size;
} __PACKED buf_desc_t;

// Entire buffer descriptor table
typedef struct {
    buf_desc_t bd_ep[NUM_EP];
} buf_desc_table_t;

typedef struct {
    const uint16_t flags;
    const uint16_t tx_pma_offset;
    const uint16_t tx_max;
    bool tx_done;
    const uint16_t rx_pma_offset;
    const uint16_t rx_max;
} ep_ctrl_t;

static ep_ctrl_t ep_ctrl[NUM_EP] = {
    {   // Endpoint 0
        USB_EP_CONTROL,    // flags
        0x0080,            // tx_pma_offset
        128,               // tx_max
        true,              // tx_done
        0x0100,            // rx_pma_offset
        RX_MAX_64BYTES,    // rx_max
    },
    {   // Endpoint 1 (not using RX)
        USB_EP_INTERRUPT,  // flags
        0x0180,            // tx_pma_offset
        128,               // tx_max
        true,              // tx_done
        NO_PMA_USE,        // rx_pma_offset
        RX_MAX_0BYTES,     // rx_max
    },
};

// The buffer descriptor table itself, at the given offset
static volatile buf_desc_table_t *const BDT =
    reinterpret_cast<volatile buf_desc_table_t *>(USB_PMAADDR + BDT_OFFSET);

// TODO: restructure so these aren't needed
static usb_setup_packet_t last_setup;

static void usb_reset(void);
static void init_ep(uint16_t ep);
static void ep0_setup(void);
static void ep0_tx_sent(void);

/**
 * @brief Performs USB port, clock, and peripheral initialization
 *
 * USB port is used in startup (for DFU), so the ports come up configured. Host detects device upon
 * DP pullup enable.
 */
void usb::init(void)
{
    // Disble embedded pullup on DP
    bitop::clr_msk(USB->BCDR, USB_BCDR_DPPU);

    // Set USB clock source from PLL, enable USB clocking
    bitop::set_msk(RCC->CFGR3, RCC_CFGR3_USBSW);
    bitop::set_msk(RCC->APB1ENR, RCC_APB1ENR_USBEN);

    // Ensure USB clock is set
    while (bitop::read_bit(RCC->APB1ENR, RCC_APB1ENR_USBEN_Pos) != 1) {}

    // Exit USB power down
    bitop::clr_msk(USB->CNTR, USB_CNTR_PDWN);

    // Startup can take a max of 1us
    LOOP_DELAY(50);

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
    bitop::set_msk(USB->BCDR, USB_BCDR_DPPU);

    debug::puts("Initialized: USB\r\n");
}

/**
 * @brief Write data from input buffer into PMA, set TX byte count, and set TX STATUS to VALID
 *
 * Due to a bug when writing bytes into the PMA, only halfword accesses work. So `len` will
 * need to always be even (and `buf` an even number of bytes).
 *
 * Only works because MCU architecture and USB protocol is little endian.
 *
 * `buf` MUST be a pointer to a 16-bit aligned buffer...
 *
 * @param[in] ep   the endpoint to write with
 * @param[in] buf  input buffer that contains data to be tranmitted
 * @param[in] len  number of bytes in `buf`
 */
void usb::write(uint16_t ep, const uint8_t *buf, uint16_t len)
{
    if ((ep >= NUM_EP) || (ep_ctrl[ep].tx_pma_offset == NO_PMA_USE) || (len > ep_ctrl[ep].tx_max)) {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return;
    }

    debug::printf("[write %d] ", len);

    BDT->bd_ep[ep].tx_size = len;

    for (int i = 0; i < len/2; ++i) {
        reinterpret_cast<uint16_t *>(USB_PMAADDR + ep_ctrl[ep].tx_pma_offset)[i] =
            reinterpret_cast<const uint16_t *>(buf)[i];
    }

    SET_TX_STATUS(ep, USB_EP_TX_VALID);
}

/**
 * @brief Read RX byte count sized block from PMA into input buffer and set RX STATUS to VALID
 *
 * @param[in, out] buf  output buffer that is filled with received data
 * @param[in]      ep   endpoint to read from
 */
void usb::read(uint16_t ep, uint8_t *buf)
{
    if ((ep >= NUM_EP) || (ep_ctrl[ep].rx_pma_offset == NO_PMA_USE)) {
        DBG_ASSERT(debug::FORCE_ASSERT);
        return;
    }

    int rx_size = BDT->bd_ep[ep].rx_size & RX_CNT_MSK;

    debug::printf("[read %d] ", rx_size);

    for (int i = 0; i < rx_size; ++i) {
        buf[i] = reinterpret_cast<uint8_t *>(USB_PMAADDR + ep_ctrl[ep].rx_pma_offset)[i];
    }

    SET_RX_STATUS(ep, USB_EP_RX_VALID);
}

/**
 * @brief Initialize an endpoint
 *
 * Set buffer locations/sizes in the PMA for transmission and reception.
 */
static void init_ep(uint16_t ep)
{
    EP_REG(ep) = (ep & USB_EPADDR_FIELD) | ep_ctrl[ep].flags;

    // set our TX and RX PMA addresses in BDT
    BDT->bd_ep[ep].tx_addr = ep_ctrl[ep].tx_pma_offset;
    BDT->bd_ep[ep].rx_addr = ep_ctrl[ep].rx_pma_offset;

    // set max # of bytes to RX (64) in BDT (TX set right before sending)
    BDT->bd_ep[ep].rx_size = ep_ctrl[ep].rx_max;

    if (ep_ctrl[ep].tx_pma_offset != NO_PMA_USE) {
        // we NAK until we get something to send
        SET_TX_STATUS(ep, USB_EP_TX_NAK);
    }

    if (ep_ctrl[ep].rx_pma_offset != NO_PMA_USE) {
        // allow reception of data from host
        SET_RX_STATUS(ep, USB_EP_RX_VALID);
    }
}

/**
 * @brief Handle ep0 IN packet completion
 *
 * This will be called when an IN for ep0 has completed.
 */
static void ep0_tx_sent(void)
{
    if (REQ(last_setup.bmRequestType, last_setup.bRequest)
            == REQ(REQ_OUT_STD_DEV, REQ_SET_ADDR)) {
        // set device address to new address, if our last setup was SET_ADDR
        USB->DADDR |= last_setup.wValue & USB_DADDR_ADD;
        SET_RX_STATUS(0, USB_EP_RX_VALID);
    }

    if (ep_ctrl[0].tx_done == false) {
        // host will want more, prep empty packet
        usb::write(0, 0, 0);
        ep_ctrl[0].tx_done = true;
    }
}

/**
 * @brief Handle SETUP packet
 *
 * Called when a CTR interrupt is received, and CTR_RX and SETUP field in the endpoint 0 register
 * (control ep) are set, indicating a SETUP packet has been received. This is read into a buffer,
 * then the request contained in the packet is handled.
 */
static void ep0_setup(void)
{
    int ret = -1;
    usb_desc::USBDesc  desc;

    // get the setup packet contents
    usb::read(0, reinterpret_cast<uint8_t *>(&last_setup));
    debug::printf("%02x %02x %04x %04x %04x ", last_setup.bmRequestType, last_setup.bRequest,
            last_setup.wValue, last_setup.wIndex, last_setup.wLength);

    // determine request type, and proceed accordingly
    switch (REQ(last_setup.bmRequestType, last_setup.bRequest)) {
    // handle both device and interface get descriptor
    case REQ(REQ_IN_STD_DEV, REQ_GET_DESC):
    case REQ(REQ_IN_STD_ITF, REQ_GET_DESC):
        debug::printf("GET DESC 0x%04x ", last_setup.wValue);
        ret = usb_desc::get_desc(last_setup.wValue, &desc);
        if (ret >= 0) {
            if (last_setup.wLength > desc.size) {
                // more data is requested than needs to be sent, we will need to handle
                // the host expecting more
                ep_ctrl[0].tx_done = false;
            } else if (last_setup.wLength < desc.size){
                // less data is requested than can be sent, make sure to only send requested
                desc.size = last_setup.wLength;
            }

            usb::write(0, desc.buf_ptr, desc.size);
        } else {
            // Stall for unknown descriptors
            debug::puts("? (STALLING) ");
            SET_RX_STATUS(0, USB_EP_RX_STALL);
            SET_TX_STATUS(0, USB_EP_TX_STALL);
        }
        break;

    // this is a class-specific request
    case REQ(REQ_OUT_CLS_ITF, REQ_SET_IDLE):
        debug::puts("SET IDLE ");
        usb::write(0, 0, 0);
        break;

    // this is a class-specific request
    case REQ(REQ_OUT_CLS_ITF, REQ_SET_RPT):
        debug::puts("SET RPT ");
        break;

    // device has been addressed
    case REQ(REQ_OUT_STD_DEV, REQ_SET_ADDR):
        debug::puts("SET ADDR ");

        // Send 0 length packet with address 0
        usb::write(0, 0, 0);
        break;

    // our device has now been configured, can use ep1 now
    case REQ(REQ_OUT_STD_DEV, REQ_SET_CFG):
        debug::printf("SET CFG (%x) ", last_setup.wValue);
        usb::write(0, 0, 0);
        init_ep(1);
        break;

    // host request status
    case REQ(REQ_IN_STD_DEV, REQ_GET_STAT):
    {
        const uint8_t status[] = { 0x01, 0x00 };  // self powered
        debug::puts("GET STAT ");
        usb::write(0, status, sizeof(status));
        break;
    }

    // clearing an endpoint feature (always ENDPOINT_HALT)
    case REQ(REQ_OUT_STD_EP, REQ_CLR_STAT):
        debug::puts("CLR STAT ");
        break;

    default:
        debug::puts("UNKNOWN REQUEST ");
        break;
    }
}

/**
 * @brief Handle RESET request
 *
 * Called when reset interrupt recieved. Restores peripheral to known starting state, with address
 * 0. Only EP0 (control ep) is initialized. SETUP packets should follow.
 */
static void usb_reset(void)
{
    // clear interrupts
    USB->ISTR = 0;

    // set our BDT offset in PMA
    USB->BTABLE = BDT_OFFSET;

    init_ep(0);

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

    debug::printf("> EP%d %s: ", int_ep, (int_reg & USB_ISTR_DIR) ? "IN " : "OUT");

    if (int_reg & USB_ISTR_PMAOVR) {
        USB->ISTR = ~USB_ISTR_PMAOVR;
        debug::puts("PMAOVR ");
    }

    if (int_reg & USB_ISTR_ERR) {
        USB->ISTR = ~USB_ISTR_ERR;
        debug::puts("ERR ");
    }

    if (int_reg & USB_ISTR_WKUP) {
        USB->ISTR = ~USB_ISTR_WKUP;
        debug::puts("WKUP ");
    }

    if (int_reg & USB_ISTR_SUSP) {
        USB->ISTR = ~USB_ISTR_SUSP;
        debug::puts("SUSP ");
    }

    if (int_reg & USB_ISTR_RESET) {
        usb_reset();
        USB->ISTR = ~USB_ISTR_RESET;
        debug::puts("RESET ");
    }

    if (int_reg & USB_ISTR_SOF) {
        USB->ISTR = ~USB_ISTR_SOF;
    }

    if (int_reg & USB_ISTR_ESOF) {
        USB->ISTR = ~USB_ISTR_ESOF;
        debug::puts("ESOF ");
    }

    if (int_reg & USB_ISTR_L1REQ) {
        USB->ISTR = ~USB_ISTR_L1REQ;
        debug::puts("L1REQ ");
    }

    if (int_reg & USB_ISTR_CTR) {
        debug::puts("CTR ");
        ep_reg = EP_REG(int_ep);

        if (ep_reg & USB_EP_CTR_RX) {
            debug::puts("RX ");

            if (ep_reg & USB_EP_SETUP) {
                debug::puts("SETUP ");
                ep0_setup();
            }

            EP_REG(int_ep) = ep_reg & USB_EPREG_MASK & ~USB_EP_CTR_RX;
        }

        if (ep_reg & USB_EP_CTR_TX) {
            debug::puts("TX ");
            EP_REG(int_ep) = ep_reg & USB_EPREG_MASK & ~USB_EP_CTR_TX;

            if (int_ep == 0) {
                ep0_tx_sent();
            }
        }
    }

    debug::puts("\r\n");
}
