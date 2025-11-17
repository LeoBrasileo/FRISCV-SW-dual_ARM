#include "friscv_com.h"

#include "../gpio/gpio.h"

/**
 * Reads 'len' words from 'address' of FRISC-V memory into 'buff' buffer.
 */
void load_from_friscv(uint32_t *buff, const unsigned int address, const unsigned int len)
{
	// Enable debug mode if not enabled already
	//set_debug_mode(DEBUG_MODE_ON);

	// Set write_in = 0
	//set_debug_write_in(WRITE_IN_OFF);

	//lowerDebugClock();

	//raiseDebugClock();

	// Write in 'len' words from 'buff'
	crnt_addr_in = address;
	for (uint32_t *wbuff = buff; wbuff - buff != len; ++wbuff)
	{
		// Set target address
		XGpio_DiscreteWrite(&axi_gpio_debug_mem_addr, 1, crnt_addr_in);
		crnt_addr_in += 4;
		clock_half_delay();

		// Lower debug_clk
		crnt_dbg_clk = 0;
		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);
		clock_half_delay();

		// Raise debug_clk
		crnt_dbg_clk = 1;
		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);
		clock_half_delay();

		// Wait a debug half-cycle (to stabilize the target address)
		//clock_half_delay();

		// Read from combinational logic memory
		if (crnt_addr_in == 0xffc){
			*wbuff = XGpio_DiscreteRead(&axi_gpio_debug_mem_data, 1);
		} else {
			*wbuff = XGpio_DiscreteRead(&axi_gpio_debug_mem_data, 1);
		}
	}

	// Does not exit debug mode
}
