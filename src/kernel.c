#include "mini_uart.h"
#include "utils.h"

#include "printf.h"

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
void putc(void* p, char c){
  if(c == '\n'){
	uart_send('\n');
  }

  uart_send(c);
}

void kernel_main() {
  uart_init(); /**< Initialize the UART */
  init_printf(0, putc); /**< Init printf w/ a function ptr to putchar */
  printf("RPi Baremetal OS initializing...\n");

#if RPI_VERSION == 3
  printf("\tBoard: RPi 3\n");
#endif

#if RPI_VERSION == 4
  printf("\tBoard: RPi 4\n");
#endif

  printf("\n\nEL = %d\n", get_el()); /**< Get current Exception level */

  while(1) {
	uart_send( uart_recv() );
  }
}
