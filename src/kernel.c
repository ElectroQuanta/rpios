#include "common.h"
//#include "mini_uart.h"
#include "peripherals/pl011.h"
#include "pl011.h"
#include "utils.h"

#include "printf.h"

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

void test_pl011() {
#define UART_DR			(UART5)
#define UART_FR			(UART_DR + 0x18)
#define UART_IBRD		(UART_DR + 0x24)
#define UART_FBRD		(UART_DR + 0x28)
#define UARTLCR_LCRH    (UART_DR + 0x2C)
#define UART_CR			(UART_DR + 0x30)

#define GPFSEL1         (PBASE+0x00200004)
#define GPSET0          (PBASE+0x0020001C)
#define GPCLR0          (PBASE+0x00200028)
#define GPPUD           (PBASE+0x00200094)
#define GPPUDCLK0       (PBASE+0x00200098)

  unsigned int selector;

#define TXD 12
#define RXD 13
#define GPFSEL_START_TXD 6
#define GPFSEL_START_RXD 9
#define ALT0  (0b100)
#define ALT4  (0b011)

  selector = get32(GPFSEL1);
  selector &= ~(7<<GPFSEL_START_TXD);                   // clean gpio14
  selector |= ALT4<<GPFSEL_START_TXD;                      // set alt0 for gpio14
  selector &= ~(7<<GPFSEL_START_RXD);                   // clean gpio15
  selector |= ALT4<<GPFSEL_START_RXD;                      // set alt0 for gpio15
  put32(GPFSEL1,selector);

  put32(GPPUD,0);
  delay(150);
  put32(GPPUDCLK0,(1<<TXD)|(1<<RXD));
  delay(150);
  put32(GPPUDCLK0,0);

  put32(UART_CR,0);						// disable RX and TX to configure
	
  put32(UART_IBRD,26);					//PrimeCell UART (PL011) rev.r1p5 pag.3-9 BAUDDIV = (FUARTCLK/(16 Baud rate)) = 48MHz/(16*115200) = 26.041666
  put32(UART_FBRD,3);					
  put32(UARTLCR_LCRH,0x60);				//Enable 8 bit mode

  put32(UART_CR, 0x301);

  while(get3
2(UART_FR)&0x20) {}			// wait if TX is full
  put32(UART_DR,'H');
  while(get32(UART_FR)&0x20) {}			// wait if TX is full
  put32(UART_DR,'H');
  while(get32(UART_FR)&0x20) {}			// wait if TX is full
  put32(UART_DR,'H');
  while(get32(UART_FR)&0x20) {}			// wait if TX is full
  put32(UART_DR,'H');
}

void kernel_main() {

#if UART_PL011 == 1
#warning "PL011 UART is being used"

  // test_pl011();
  const uart_gpio uart5_alt4 = {.tx = 12, .rx = 13, .func = GFAlt4};
  pl011_uart uart5 = {.regs = (pl011_regs *const)UART5, .gpio = &uart5_alt4};

  pl011_uart *uart = &uart5;

 pl011_init(uart, 115200);
 init_printf(uart, putc); /**< Init printf w/ a function ptr to putchar */
 printf("\n\nuart5->regs %u\n", (unsigned long)uart5.regs);
 printf("UART0 %u\n", (unsigned long)UART0);

 printf("RPI4 Baremetal UART5 PL011 in the house");
#else
#warning "mini-UART is being used"
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
