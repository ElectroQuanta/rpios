/**
 * @file pl011.h
 * @author Jose Pires
 * @date 2024-09-30
 *
 * @brief PL011 register definitions
 *
 * It follows the documentation:
 * - PrimeCell UART (PL011)
 * - BCM2711 peripherals
 *
 * @copyright copyright
 */    

#pragma once

#include "common.h"
#include "peripherals/base.h"
#include <stdint.h>

#define UART0 (PBASE + 0x00201000)
#define UART2 (PBASE + 0x00201400)
#define UART3 (PBASE + 0x00201600)
#define UART4 (PBASE + 0x00201800)
#define UART5 (PBASE + 0x00201a00)

/**
 * See BCM2711 UART: Control Register (UARTCR)
 */
#define PL011_UARTCR_UARTEN 0 /**< UART Enable (bit 0) */
#define PL011_UARTCR_TXE 8 /**< TX Enable (bit 8) */
#define PL011_UARTCR_RXE 9 /**< RX Enable (bit 9) */

/**
 * See BCM2711 UART: Flag Register (UARTFR)
 */
#define PL011_UARTFR_BUSY 3 /**< UART Busy (bit 3) */
#define PL011_UARTFR_RXFE 4 /**< UART Receive FIFO Empty (bit 4) */
#define PL011_UARTFR_TXFF 5 /**< UART Transmit FIFO full (bit 5) */
#define PL011_UARTFR_RXFF 6 /**< UART Receive FIFO Full (bit 6) */

/**
 * See BCM2711 UART: Line Control Register (UART_LCRH)
 */
#define PL011_UARTLCRH_FEN 4 /**< UART Enable FIFOs (bit 4) */
#define PL011_UARTLCRH_WLEN 5 /**< UART Word length (bit 6:5) */

enum PL011_WLEN {
  PL011_WLEN_5 = 0b00,
  PL011_WLEN_6 = 0b01,
  PL011_WLEN_7 = 0b10,
  PL011_WLEN_8 = 0b11,
};


#define PL011_FSYSCLK (u64)48e6 /**< Sysclk frequency for UART */

// struct __attribute__((packed)) pl011  // ensure no unexpected padding
/**
 * @brief PL011 Registers definition
 *
 * See BCM2711 UART: Table 172
 */
//struct __attribute__((packed)) pl011_regs {
typedef struct {
    reg32 dr;        /**< Data register (0x00) */
    reg32 rsrecr;    /**< Reserved (0x04) */
    const uint32_t reserved1[4]; /**< Reserved gap (0x08 to 0x18, 16 bytes = 4 registers) */
    reg32 fr;        /**< Flag register (0x18) */
    const uint32_t reserved2; /**< Reserved gap (0x1C to 0x20) */
    reg32 ilpr;      /**< ILPR (0x20, not used) */
    reg32 ibrd;      /**< Integer Baud rate divisor (0x24) */
    reg32 fbrd;      /**< Fractional Baud rate divisor (0x28) */
    reg32 lcrh;      /**< Line Control register (0x2C) */
    reg32 cr;        /**< Control register (0x30) */
//  reg32 ifls;        /**< Interrupt FIFO Level Select Register */
//  reg32 imsc;        /**< Interrupt Mask Set Clear Register */
//  reg32 ris;         /**< Raw Interrupt Status Register */
//  reg32 mis;         /**< Masked Interrupt Status Register */
//  reg32 icr;         /**< Interrupt Clear Register */
//  reg32 dmacr;       /**< DMA Control Register */
//  reg32 itcr;        /**< Test Control Register */
//  reg32 itip;        /**< Integration Test Input Register */
//  reg32 itop;        /**< Integration Test Output Register */
//  reg32 tdr;         /**< Test Data Register */
} pl011_regs;
