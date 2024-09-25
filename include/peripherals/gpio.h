/**
 * @file gpio.h
 * @author Jose Pires
 * @date 2024-09-24
 *
 * @brief GPIO interface definition
 *
 * detailed
 *
 * @copyright copyright
 */

#include "common.h"

#include "peripherals/base.h"

/**
 * @brief Recurring Gpio Pin data 
 *
 * GPIO pin data follows a pattern with a reserved register
 * and two 32-bit register
 */
struct GpioPinData {
  reg32 reserved;
  reg32 data[2];
};

/**
 * @brief GPIO Registers
 *
 * See BCM2835 ARM peripherals; GPIO section
 */
struct GpioRegs {
  reg32 func_select[6]; /**< GPIO Function select 0-5 */
  struct GpioPinData output_set; /**< GPIO Output Set */
  struct GpioPinData output_clear; /**< GPIO Output clear */
  struct GpioPinData level; /**< GPIO level */
  struct GpioPinData ev_detect_status; /**< Event detect status */
  struct GpioPinData re_detect_enable; /**< Rising Edge Detect Enable */
  struct GpioPinData fe_detect_enable; /**< Falling Edge Detect Enable */
  struct GpioPinData hi_detect_enable; /**< High Detect Enable */
  struct GpioPinData lo_detect_enable; /**< Low Detect Enable */
  struct GpioPinData async_re_enable; /**< Async Rising Edge Detect */
  struct GpioPinData async_fe_enable; /**< Async Falling Edge Detect */
  reg32 reserved; /**< Reserved */
  reg32 pupd_enable; /**< Pull-up/down enable */
  reg32 pupd_enable_clocks[2]; /**< Pull-up/down Enable clocks */
};

#define REGS_GPIO ((struct GpioRegs *)(PBASE + 0x00200000))
