#include "uart.h"
#include "internal.h"

#define LOG(string) (uart_send_string((string), sizeof((string)) - 1))

#include <stdio.h>

// --- XUartPs initialization ---
int uart_init(void)
{
	if (uart_initialized) {
		return XST_SUCCESS;
	}

	// Get configuration for device id
	XUartPs_Config *configPtr = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
	if (configPtr == NULL) {
		return XST_FAILURE;
	}

	// Initialize with configuration
	int status = XUartPs_CfgInitialize(&uart_driver, configPtr, configPtr->BaseAddress);
	if (status == XST_FAILURE) {
		return XST_FAILURE;
	}

	// Configure the device
	XUartPs_SetBaudRate(&uart_driver, 115200);

	uart_initialized = 1;
	return XST_SUCCESS;
}

unsigned int uart_recv_byte(void)
{
	// Receive 1 byte
	u8 received_byte;
	while (XUartPs_Recv(&uart_driver, &received_byte, 1) == 0);
	return received_byte;
}

void uart_send_byte(const uint8_t byte)
{
	// Send 1 byte
	XUartPs_Send(&uart_driver, (uint8_t *)&byte, 1);
}

u32 uart_receive_4_digit_num(){
	uint8_t number1 = uart_recv_byte();
	uint8_t number2 = uart_recv_byte();
	uint8_t number3 = uart_recv_byte();
	uint8_t number4 = uart_recv_byte();
	return (number1 - 48) * 1000 + (number2 - 48) * 100 + (number3 - 48) * 10 + number4 - 48;
}

void uart_send_u32(u32 number){
	uart_send_byte((uint8_t)((number & 0xff000000) >> 24));
	uart_send_byte((uint8_t)((number & 0x00ff0000) >> 16));
	uart_send_byte((uint8_t)((number & 0x0000ff00) >> 8));
	uart_send_byte((uint8_t)(number & 0x000000ff));
	uart_send_byte('\n');
}

void uart_send_int(const u32 intp)
{
	uint8_t i;

	i= (uint8_t)(intp & 15);
	if (i<10)
		i=i+48;
	else
		i=i+54;

	uart_send_byte(i);
}

void uart_send_hex(const u32 value)
{
    int i;
    uint8_t nibble;

    /* Print 8 hex digits (32 bits) */
    for (i = 28; i >= 0; i -= 4) {
        nibble = (value >> i) & 0xF;

        if (nibble < 10)
            uart_send_byte(nibble + '0');
        else
            uart_send_byte(nibble + 'A' - 10);
    }
}


void uart_send_string(const char *string, const unsigned int strlen)
{
	// Send buffer
	XUartPs_Send(&uart_driver, (u8 *)string, strlen);
}

u32 uart_recv_u32(void)
{
    u32 v = 0;
    for (int i = 0; i < 4; i++) {
        v |= ((u32)uart_recv_byte()) << (8 * i);
    }
    return v;
}
