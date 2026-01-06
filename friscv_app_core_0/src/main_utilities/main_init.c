#include "main_utilities.h"

int main_init(){
	// Initialize UART driver
	int status;
	status = uart_init();
	if (status == XST_FAILURE) {
		// Can't print: LOG("[ERROR] Failed to initialize UART driver\n");
		return XST_FAILURE;
	}

	// Initialize AXI GPIOs
	status = gpio_init();
	if (status == XST_FAILURE) {
		LOG("[ERROR] Failed to initialize AXI GPIOs\n");
		return XST_FAILURE;
	}

	crnt_rst_n_ext = 1;
	XGpio_DiscreteWrite(&axi_gpio_rst_n_extern, 2, crnt_rst_n_ext);

	delay_sec(1);
	return status;
}
