/**
 * @file mini_uart.h
 * @author Jose Pires
 * @date 2024-09-24
 *
 * @brief Mini UART interface
 *
 * Define the Mini UART interface to initialize the HW, receive and
 * send a string
 *
 * @copyright Jose Pires 2024
 */

#pragma once

/**
 * @brief Initialize the Mini UART
 *
 * detailed
 */
void uart_init();

/**
 * @brief Receive a character from the Mini UART
 * @return char read
 *
 * detailed
 */
char uart_recv();

/**
 * @brief Send a character via UART
 * @param c: character to send
 *
 * detailed
 */
void uart_send(char c);

/**
 * @brief Send a string via UART
 * @param str: null-terminated string to send
 *
 * detailed
 */
void uart_send_string(char *str);
