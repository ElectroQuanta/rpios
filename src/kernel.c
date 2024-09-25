#include "mini_uart.h"

void kernel_main() {
  uart_init();
  uart_send_string("RPi Baremetal OS initializing...\n");

#if RPI_VERSION == 3
  uart_send_string("\tBoard: RPi 3\n");
#endif

#if RPI_VERSION == 4
  uart_send_string("\tBoard: RPi 4\n");
#endif

  uart_send_string("\n\nDone\n");

  while(1) {
	uart_send( uart_recv() );
  }
}
