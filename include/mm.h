/**
 * @file mm.h
 * @author Jose Pires
 * @date 2024-09-24
 *
 * @brief Memory management interface
 *
 * Memory management interface, heavily influenced by the Linux Kernel
 *
 * @copyright Jose Pires 2024
 */

#pragma once

#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define PAGE_SIZE (1 << PAGE_SHIFT) // Page size
#define SECTION_SIZE (1 << SECTION_SHIFT) // Section size

#define LOW_MEMORY (2 * SECTION_SIZE)

/**< Make sure the functions below are only included in C compilations */
#ifndef __ASSEMBLER__

/**
 * @brief Clear the memory (zero it)
 * @param src: pointer to memory to clear
 * @param n: nr of bytes to clear
 * void memzero( unsigned long src, unsigned int n);
 */
void memzero( unsigned long src, unsigned int n);

#endif

