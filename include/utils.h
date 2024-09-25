/**
 * @file utils.h
 * @author Jose Pires
 * @date 2024-09-24
 *
 * @brief Utility functions interface
 *
 * Useful generic functions
 *
 * @copyright Jose Pires 2024
 */

#pragma once

#include "common.h"

/**
 * @brief Create a delay for a nr of ticks
 * @param ticks: nr of ticks to delay
 *
 * Creates a delay for a specified nr of ticks
 */
void delay(u64 ticks);

/**
 * @brief Put a 32-bit value at a designated address
 * @param val: 32-bit value to copy
 * @param addr: address to copy the value from
 *
 * detailed
 */
void put32(u64 addr, u32 val);

/**
 * @brief Get a 32-bit value from a designated address
 * @param address: address to get the value from
 * @return 32-bit value
 *
 * detailed
 */
u32 get32(u64 address);
