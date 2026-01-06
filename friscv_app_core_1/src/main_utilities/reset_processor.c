#include "main_utilities.h"

int reset_processor(){
	int status;
	status = XST_SUCCESS;

	turnDebugOff();

	crnt_rst_n_ext = 0;
	XGpio_DiscreteWrite(&axi_gpio_rst_n_extern, 2, crnt_rst_n_ext);
	delay_sec(5);

	crnt_rst_n_ext = 1;
	XGpio_DiscreteWrite(&axi_gpio_rst_n_extern, 2, crnt_rst_n_ext);
	delay_msec(1);

	LOG("[ARM] FRISCV reset completed.\n");
	return status;
}
