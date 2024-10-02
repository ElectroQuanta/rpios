/**
 * @file pl011.h
 * @author Jose Pires
 * @date 2024-09-30
 *
 * @brief PL011 UART interface
 *
 * PrimeCell UART (PL011)
 *
 * @copyright Jose Pires 2024
 */

#pragma once

#include "peripherals/pl011.h"
#include "gpio.h"

//typedef struct __attribute__((packed)) {  // ensure no unexpected padding
typedef struct {
  const u8 tx;        /**< GPIO pin for TX */
  const u8 rx;        /**< GPIO pin for RX */
  const GpioFunc func; /**< GPIO Function for TX and RX */
} uart_gpio;

/**
 * @brief PL011 UART typedef
 */

//typedef struct __attribute__((packed)) {  // ensure no unexpected padding
typedef struct {
  pl011_regs * const regs; /**< const Pointer to UART register */
  const uart_gpio * const gpio; /**< Const pointer to const UART GPIO cfg */
} pl011_uart;


//extern const uart_gpio uart5_alt4;
//extern const uart_gpio uart0_alt0;
//extern pl011_uart uart5; /**< UART5 is implemented in pl011.c */
//extern pl011_uart uart0; /**< UART0 is implemented in pl011.c */

// Function declarations
//pl011_uart *get_uart_by_index(int index);


/**
 * @brief Set the baudrate for the UART
 * @param uart: pointer to a UART struct
 * @param baudrate: baudrate in bps
 */
void pl011_set_br(pl011_uart *uart, u32 baudrate);

/**
 * @brief Set the baudrate for the UART
 * @param uart: pointer to a UART struct
 * @param baudrate: baudrate in bps
 */
void pl011_init(pl011_uart * uart, u32 baudrate);

/**
 * @brief Set the baudrate for the UART
 * @param uart: pointer to a UART struct
 * @param c: character to send
 */
void pl011_send(pl011_uart * uart, char c);

/**
 * @brief Set the baudrate for the UART
 * @param uart: pointer to a UART struct
 * @return a char read from the UART
 */
char pl011_recv(pl011_uart * uart);

/**
 * @brief Set the baudrate for the UART
 * @param uart: pointer to a UART struct
 * @param string: string to send
 */
void pl011_send_string(pl011_uart *uart, char *str);
