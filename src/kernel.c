#include "mini_uart.h"
#include "pl011.h"
#include "utils.h"

#include "printf.h"

pl011_uart uart5 = {.regs = (pl011_regs *)UART5,
                    .tx_pin = 12, /* GPIO12: TXD5 Pin */
                    .rx_pin = 13, /* GPIO13: RXD5 pin */
                    .gpio_func = GFAlt4};

pl011_uart uart0 = {.regs = (pl011_regs *)UART0,
                    .tx_pin = 14,
                    .rx_pin = 15,
                    .gpio_func = GFAlt0};

#define UART_PL011 1 /**< UART to use: 1 (PL011), 0 (mini-uart) */

/**
 * @brief Put a char on the output (UART)
 * @param p: unused
 * @param c: char to print
 *
 * This is a custom implementation of putchar that is meant to be used
 * as a callback for printf
 * - We send the character via UART (in case of NEWLINE, prepend it w/ CR)
 *
 * We pass this function, as a pointer to @init_printf
 * void init_printf(void* putp, void (*putf) (void*,char));
 *
 * So we need to implement a function with the following prototype scheme:
 * - args: (void *, char c)
 * - return: void
 */
#if UART_PL011 == 1
void putc(void *p, char c) {
  pl011_uart *uart = (pl011_uart *) p;
  if(c == '\n'){
	pl011_send(uart, '\r');
  }
  pl011_send(uart, c);
}
#else
void putc(void* p, char c){
  if(c == '\n'){
	uart_send('\r');
  }
  uart_send(c);
}
#endif

void kernel_main() {

#if UART_PL011 == 1

  pl011_uart *uart = &uart5;

  pl011_init(uart, 115200);
  init_printf(uart, putc); /**< Init printf w/ a function ptr to putchar */
  printf("\n\nuart5->regs %u\n", (unsigned long)uart5.regs);
  printf("UART0 %u\n", (unsigned long)UART0);

  printf("RPI4 Baremetal UART5 PL011");
#else
  uart_init(); /**< Initialize the UART */
  init_printf(0, putc); /**< Init printf w/ a function ptr to putchar */
  printf("RPi Baremetal OS initializing...\n");
#endif  

#if RPI_VERSION == 3
  printf("\tBoard: RPi 3\n");
#endif

#if RPI_VERSION == 4
  printf("\tBoard: RPi 4\n");
#endif

  printf("\n\nEL = %d\n", get_el()); /**< Get current Exception level */

  while (1) {
#if UART_PL011 == 1
	pl011_send( uart, pl011_recv(uart) );
#else
	uart_send( uart_recv() );
#endif  
  }
}
