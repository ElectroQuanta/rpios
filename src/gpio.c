/**
 * @file gpio.c
 * @author Jose Pires
 * @date 2024-09-25
 *
 * @brief GPIO user implementation
 *
 * Provides utility functions to handle the GPIO:
 * - Set the alternate function
 * - Enable a GPIO
 *
 * @copyright Jose Pires 2024
 */

#include "gpio.h"
#include "utils.h"

#define GPIO_BITS 3
#define GPIO_PINS_PER_REG 10
#define GPIO_BITS_TOTAL (GPIO_PINS_PER_REG * GPIO_BITS)

void gpio_pin_set_func(u8 pinNumber, GpioFunc func) {
  /* Get the bit start and register */
  u8 bitStart = (pinNumber * GPIO_BITS) % GPIO_BITS_TOTAL;
  u8 reg = pinNumber / GPIO_PINS_PER_REG;

  /* Store the current function to an auxiliary var */
  u32 selector = REGS_GPIO->func_select[reg];

  /* Set the new function in the aux */
  selector &= ~(0b111 << bitStart); // clear the 3 bits
  selector |= (func << bitStart); // Set the 3 bits to the new func

  /* Load the config back to the registor */
  REGS_GPIO->func_select[reg] = selector; 
}

/**
 * GPIO Pull-up/down Clock Registers (GPPUDCLKn)
 * SYNOPSIS
 * The GPIO Pull-up/down Clock Registers control the actuation of internal pull-downs on
 * the respective GPIO pins. These registers must be used in conjunction with the GPPUD
 * register to effect GPIO Pull-up/down changes. The following sequence of events is
 * required:
 * 1. Write to GPPUD to set the required control signal (i.e. Pull-up or Pull-Down or neither
 * to remove the current Pull-up/down)
 * 2. Wait 150 cycles – this provides the required set-up time for the control signal
 * 3. Write to GPPUDCLK0/1 to clock the control signal into the GPIO pads you wish to
 * modify – NOTE only the pads which receive a clock will be modified, all others will
 * retain their previous state.
 * 4. Wait 150 cycles – this provides the required hold time for the control signal
 * 5. Write to GPPUD to remove the control signal
 * 6. Write to GPPUDCLK0/1 to remove the clock
 */
void gpio_pin_enable(u8 pinNumber){
  REGS_GPIO->pupd_enable = GPUD_Off;
  delay(150);
  REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 1 << (pinNumber % 32);
  delay(150);
  REGS_GPIO->pupd_enable = GPUD_Off;
  REGS_GPIO->pupd_enable_clocks[pinNumber / 32] = 0;
}
