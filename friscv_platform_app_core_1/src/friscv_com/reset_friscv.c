#include "friscv_com.h"

#include "../gpio/gpio.h"

void reset_friscv(void)
{
	// Reset signal active low
	crnt_rst_n_ext = 0;
	XGpio_DiscreteWrite(&axi_gpio_rst_n_extern, 2, crnt_rst_n_ext);

	for(int i = 0;i < 10;i++){
		// Raise debug_clk
		crnt_dbg_clk = 1;
		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);

		// Wait a debug half-cycle
		clock_half_delay();

		// Lower debug_clk
		crnt_dbg_clk = 0;
		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);

		// Wait a debug half-cycle
		clock_half_delay();
}
	// Deactivate reset signal
	crnt_rst_n_ext = 1;
	XGpio_DiscreteWrite(&axi_gpio_rst_n_extern, 1, crnt_rst_n_ext);

	// Set clear_in = 0
	//crnt_dbg_ctrl = (crnt_dbg_ctrl & (~DBG_CLEAR_IN_MSK)); // ne treba više?
	//XGpio_DiscreteWrite(&axi_gpio_debug, 2, crnt_dbg_ctrl); //ne treba više?
}
