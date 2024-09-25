/**
 * @file aux.h
 * @author Jose Pires
 * @date 2024-09-24
 *
 * @brief Peripherals Auxiliary registers definitions
 *
 * detailed
 *
 * @copyright Jose Pires 2024
 */

#pragma once

#include "common.h"

#include "peripherals/base.h"

/**
 * @brief Auxiliary Registers
 *
 * See BCM2835 Auxiliary peripherals
 */
struct AuxRegs {
  reg32 irq_status; /**< Auxiliary Interrupt status */
  reg32 enables; /**< Auxiliary enables */
  reg32 reserved[14]; // (0x5040 - 1 - (0x5004 + 3)) / 4
  reg32 mu_io;         /**< Mini UART I/O Data */
  reg32 mu_ier;        /**< Mini UART Interrupt Enable */
  reg32 mu_iir;        /**< Mini UART Interrupt Identify */
  reg32 mu_lcr;        /**< Mini UART Line Control */
  reg32 mu_mcr;        /**< Mini UART Modem Control */
  reg32 mu_lsr;        /**< Mini UART Line Status */
  reg32 mu_msr;        /**< Mini UART Modem Status */
  reg32 mu_scratch;    /**< Mini UART Scratch */
  reg32 mu_control;    /**< Mini UART Extra Control */
  reg32 mu_status;     /**< Mini UART Extra Status */
  reg32 mu_baud_rate;  /**< Mini UART Baudrate */
};

#define REGS_AUX ((struct AuxRegs *)(PBASE + 0x00215000))
