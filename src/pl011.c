/**
 * @file pl011.c
 * @author Jose Pires
 * @date 2024-09-30
 *
 * @brief PL011 UART implementation
 *
 * It follows the documentation:
 * - PrimeCell UART (PL011)
 * - BCM2711 peripherals
 *
 * @copyright Jose Pires 2024
 */

#include "pl011.h"
#include "common.h"
#include "gpio.h"
#include "peripherals/pl011.h"

//const uart_gpio uart0_alt0 = {.tx = 14, .rx = 15, .func = GFAlt0};
//const uart_gpio uart5_alt4 = {.tx = 12, .rx = 13, .func = GFAlt4};
//const uart_gpio uart2_alt0 = {.tx = 12, .rx = 13, .func = GFAlt0};

// pl011_uart uart0 = {.regs = (pl011_regs *)UART0, .gpio = &uart0_alt0};
// pl011_uart uart5 = {.regs = (pl011_regs *)UART5, .gpio = &uart5_alt4};
// pl011_uart uart2 = {.regs = (pl011_regs *)UART2, .gpio = &uart2_alt0};


// Static variables to hold UART configurations
// Define the array of UART instances
//static pl011_uart uart_instances[] = {
//    {.regs = (pl011_regs *)UART0,
//     .tx_pin = 14,
//     .rx_pin = 15,
//     .gpio_func = GFAlt0}, // UART0
//    {.regs = (pl011_regs *)UART5,
//     .tx_pin = 12,
//     .rx_pin = 13,
//     .gpio_func = GFAlt4} // UART5
//};
//
//// Function to get a pointer to a UART by index
//pl011_uart *get_uart_by_index(int index) {
//  if (index < 0 || index >= (sizeof(uart_instances) / sizeof(pl011_uart))) {
//	return NULL; // Return NULL for invalid index
//  }
//  return &uart_instances[index];
//}

/**
 * Set the baudrate register
 * - Check the baudrate is valid
 * - Disable the UART and wait until it is disabled, before we configure it
 * - Calculate the Baud rate divisor integer (IBRD) and fractional parts (FBRD)
 *   - BAUDDIV = FUARTCLK / (16 * Baud_rate)
 *   - IBRD = (int) BAUDDIV
 *   - FBRD = (reg32)((brd - uart->regs->ibrd) * 2 ** n + 0.5)
 *     - n = FBDR_Width (6 bits)
 *
 *   ### Integer-arithmetic implementation
 * u64 brd_scaled = ( PL011_FSYSCLK * 4 + baudrate / 2 ) / baudrate;
 * uart->regs->ibrd = (reg32)( brd_scaled / 64 );
 * uart->regs->fbrd = (reg32)( brd_scaled % 64 );
 */
void pl011_set_br(pl011_uart *uart, u32 baudrate) {
 if (baudrate == 0) {
        return;
 }

    /* Disable the UART first */
    //uart->regs->cr &= ~(1 << PL011_UARTCR_UARTEN);
    uart->regs->cr = 0;

    /* Optionally wait until UART is disabled */
    //while (uart->regs->fr & (1 << PL011_UARTFR_BUSY)) {
    //    // Wait or implement a timeout
	//  ;
    //}

    /* Flush the Transmit FIFO by setting FEN bit to 0 */
    // uart->regs->lcrh &= ~(1 << PL011_UARTLCRH_FEN);

  /* Calculate BAUDDIV = FUARTCLK / (16 * Baud rate) */
  /* To calculate FBRD = round((BAUDDIV - IBRD) * 64) */
  /* BAUDDIV * 64 = (FUARTCLK * 4) / baudrate */
  u64 brd_scaled = ( PL011_FSYSCLK * 4 + baudrate / 2 ) / baudrate; // Adding baudrate/2 for rounding

  uart->regs->ibrd = (reg32)( brd_scaled / 64 );
  uart->regs->fbrd = (reg32)( brd_scaled % 64 );
  //uart->regs->ibrd = 26;
  //uart->regs->fbrd = 3;
}


/**
 * Initialize the UART with a defined baudrate
 *  - Calculate the baudrate register
 *  - Set the Word length to 8-bits
 *  - Enable RX, TX and the UART
 */
void pl011_init(pl011_uart *uart, u32 baudrate) {
  gpio_pin_set_func(uart->gpio->tx, uart->gpio->func);
  gpio_pin_set_func(uart->gpio->rx, uart->gpio->func);

  gpio_pin_enable(uart->gpio->tx);
  gpio_pin_enable(uart->gpio->rx);

  // Set the base address for UART registers if it's not set
  if (uart->regs == NULL) {
	return;
  }

  pl011_set_br(uart, baudrate);

  uart->regs->lcrh = (PL011_WLEN_8 << PL011_UARTLCRH_WLEN);
  //uart->regs->lcrh = 0x60;

  uart->regs->cr = (1 << PL011_UARTCR_RXE) | (1 << PL011_UARTCR_TXE) |
                   (1 << PL011_UARTCR_UARTEN);
  //uart->regs->cr = 0x301;
}

/**
 * Send a char
 * - While UART TX FIFO is full, wait
 * - Send a char to the Data Register
 */
void pl011_send(pl011_uart *uart, char c){
  while( uart->regs->fr & (1 << PL011_UARTFR_TXFF)){
          ;
  }
  uart->regs->dr = c;
}

/**
 * Receive a char
 * - While UART RX FIFO is empty, wait
 * - Return a byte from the data register
 */
char pl011_recv(pl011_uart *uart) {  
  while( uart->regs->fr & (1 << PL011_UARTFR_RXFE) ){
          ;
  }
  return ((char)(uart->regs->dr & 0xFF));
}

/**
 * Send a string over UART
 */
void pl011_send_string(pl011_uart *uart, char *str) {

  while (*str) {
	if (*str == '\n'){
	  pl011_send(uart, '\r');
	}
	pl011_send(uart, *str);
	str++;
  }

}
