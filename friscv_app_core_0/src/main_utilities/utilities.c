#include "main_utilities.h"

void turnDebugOn(){
	XGpio_DiscreteWrite(&axi_gpio_clk_gen_n_debug, 2, DEBUG_MODE_ON);
	delay_msec(1);

	COMM_CTRL.pause = 1;
}

void turnDebugOff(){
	XGpio_DiscreteWrite(&axi_gpio_clk_gen_n_debug, 2, DEBUG_MODE_OFF);
	delay_msec(1);

	COMM_CTRL.pause = 0;
}

