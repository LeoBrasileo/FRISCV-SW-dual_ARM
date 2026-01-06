#ifndef UART_HEADER
#define UART_HEADER

#include <stdint.h>
#include "xil_types.h"

int uart_init(void);

unsigned int uart_recv_byte(void);
void uart_send_byte(const uint8_t byte);
void uart_send_int(const uint32_t intp);
void uart_send_string(const char *string, const unsigned int strlen);

u32 uart_receive_4_digit_num();
void uart_send_u32(u32 number);

#endif
