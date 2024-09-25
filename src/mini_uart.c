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

#define TXD 14
#define RXD 15

void uart_init(){
  gpio_pin_set_func(TXD, GFAlt5);
  gpio_pin_set_func(RXD, GFAlt5);

  gpio_pin_enable(TXD);
  gpio_pin_enable(RXD);

  REGS_AUX->enables = 0b01; // first bit is Mini-UART enable
  REGS_AUX->mu_control = 0; // disable control to manipulate extra flags
  REGS_AUX->mu_ier = 0; // interrupts disabled
  //REGS_AUX->mu_lcr = (1 << 0) | (1 << 1);
  REGS_AUX->mu_lcr = 3; // Why?
  REGS_AUX->mu_mcr = 0;


  #if RPI_VERSION == 3
  REGS_AUX->mu_baud_rate = 250;
  #endif

  
  
}
