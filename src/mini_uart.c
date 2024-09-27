/**
 * @file mini_uart.c
 * @author Jose Pires
 * @date 2024-09-25
 *
 * @brief Mini-UART implementation
 *
 * detailed
 *
 * @copyright Jose Pires
 */

#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"
#include "common.h" /**< Type definition */

#define TXD 14
#define RXD 15

/**
 * @brief Calculate Baudrate register value
 * @param sysclk: system clock frequency (in Hz) [in]
 * @param baudrate: baud rate (in bps) [in]
 * @return register value
 *
 * BR_reg = sysclk / (8 * BR) - 1 (see BCM2835 Peripherals - MiniUART)
 */
u32 static inline calc_br_reg(u32 sysclk, u32 baudrate){
  return (sysclk / ( 8 * baudrate ) - 1);
};


/**
 * Initialize the UART
 * - Set the TXD and RXD pins to alternate function 5 (UART)
 * - Enable the clocks for each pin
 * - Configure the Mini UART:
 *   - Enable the mini uart before doing any setup
 *   - disable the control to manipulate extra flags
 *   - Set the data size to 8-bits
 *   - Clear modem signals (RTS low)
 *   - Set the baudrate to 115200 bps
 *   - Send some characters over to fix boot messages
 */
void uart_init(){
  gpio_pin_set_func(TXD, GFAlt5);
  gpio_pin_set_func(RXD, GFAlt5);

  gpio_pin_enable(TXD);
  gpio_pin_enable(RXD);

  REGS_AUX->enables = (1 << 0); // first bit is Mini-UART enable
  REGS_AUX->mu_control = 0; // disable control to manipulate extra flags
  REGS_AUX->mu_ier = 0; // interrupts disabled
  REGS_AUX->mu_lcr = (1 << 0) | (1 << 1); // Why?
  REGS_AUX->mu_mcr = 0;


#if RPI_VERSION == 3
  //REGS_AUX->mu_baud_rate = 270;
  REGS_AUX->mu_baud_rate = (reg32)calc_br_reg(250e6, 115200);
#endif

#if RPI_VERSION == 4
  //REGS_AUX->mu_baud_rate = 541;
  REGS_AUX->mu_baud_rate = (reg32) calc_br_reg(500e6, 115200);
#endif

  REGS_AUX->mu_control = (1 << 0) | (1 << 1); /**< Enable TX and RX */

  uart_send('\r');
  uart_send('\n');
  uart_send('\n');
}


/**
 * Send a character through UART
 * - Wait until bit 5 from LSR_REG is empty (this mean the TX FIFO can
 *   accept at least one byte)
 * - Data written to IO_REG is put in the transmit FIFO
 *   (provided it is not full)
 */
void uart_send(char c) {
  while (! (REGS_AUX->mu_lsr & (1 << 5)) )
    ;

  REGS_AUX->mu_io = c;
}

/**
 * Receive a character from UART
 * - Wait until a character is received: LSR_REG bit 1 is set
 * - Return a byte from the IO register
 *  - As the IO register is 32-bit we need to AND-it with 0xFF
 */
char uart_recv(){
  while (!(REGS_AUX->mu_lsr & (1 << 0)))
    ;

  return REGS_AUX->mu_io & 0xFF;
}

/**
 * Send a string
 * - While the NUL terminator is not found
 *  - Send the character
 *  - Increment the pointer to point to the next char
 *  - If a newline is found, send a CR before it
 */
void uart_send_string(char *str) {

  while(*str){
	if(*str == '\n'){
	  uart_send('\r');
	}
  
	uart_send(*str);
	str++;
  }  

}
