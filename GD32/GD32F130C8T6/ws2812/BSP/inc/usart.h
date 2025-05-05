#ifndef __USART_H
#define __USART_H

#include <stdio.h>

#include "gd32f1x0.h"
#include "gd32f1x0_usart.h"

void uart_init(uint32_t baudrate);
void debug_print_matrix(const uint32_t *buf, uint16_t rows, uint16_t cols);
#endif