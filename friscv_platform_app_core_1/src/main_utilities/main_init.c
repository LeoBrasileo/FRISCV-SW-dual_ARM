#include "main_utilities.h"
#include "xgpio.h"

int main_init(){
	// Initialize UART driver
	int status;
	status = uart_init();
	if (status == XST_FAILURE) {
		return XST_FAILURE;
	}

	delay_sec(1);
	return status;
}

int clk_gpio_init(){
	int status;
	status = XGpio_Initialize(&axi_gpio_clk_gen, XPAR_GPIO_0_DEVICE_ID);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XGpio_SetDataDirection(&axi_gpio_clk_gen, 0, 0x0);
	XGpio_SetDataDirection(&axi_gpio_clk_gen, 1, 0x0);
	return status;
}
