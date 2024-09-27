/**
 * @file gpio.h
 * @author Jose Pires
 * @date 2024-09-25
 *
 * @brief GPIO user interface
 *
 * detailed
 *
 * @copyright Jose Pires 2024
 */

#pragma once

#include "peripherals/gpio.h"

/**
 * @brief GPIO functions
 *
 * GPIO functions as defined by GPFSELn registers 
 */
typedef enum _GpioFunc {
  GFInput  = 0b000, /**< Input */ 
  GFOutput = 0b001, /**< Output */
  GFAlt0   = 0b100, /**< Alt0 */
  GFAlt1   = 0b101, /**< Alt1 */
  GFAlt2   = 0b110, /**< Alt2 */
  GFAlt3   = 0b111, /**< Alt3 */
  GFAlt4   = 0b011, /**< Alt4 */
  GFAlt5   = 0b010, /**< Alt5 */
} GpioFunc;

/**
 * @brief Gpio Pull Down modes
 *
 * GPIO Pull Down modes (PUD) described in GPPUD
 */
typedef enum _GpioPUD {
  GPUD_Off = 0b00, /**< Disable Pull-up/down */
  GPUD_PullDown = 0b01, /**< Enable Pull down control */
  GPUD_PullUp = 0b10, /**< Enable Pull Up control */
} GpioPUD;

/**
 * @brief Set the GPIO Pin function
 * @param pinNumber: pin number to set function (0-54)
 * @param func: function to set
 *
 * It sets the GPIO pin function
 */
void gpio_pin_set_func(u8 pinNumber, GpioFunc func);


/**
 * @brief Enable the GPIO clock
 * @param pinNumber: pin to enable
 *
 * Enable the GPIO clock
 */
void gpio_pin_enable(u8 pinNumber);
