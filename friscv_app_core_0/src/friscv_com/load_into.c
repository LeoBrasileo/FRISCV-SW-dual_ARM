#include "friscv_com.h"

#include "../gpio/gpio.h"

// DEPRECATED: It does not make sense to load into FRISCV if memory is in DRAM

/**
 * Load binary program from buffer 'buff' of length 'len' into
 * FRISC-V device under test.
 */
void load_into_friscv(uint32_t *buff, const unsigned int len)
{
//	// Enable debug mode if not enabled already
//	//set_debug_mode(DEBUG_MODE_ON);
//
//	// Clear FRISC-V memory
//	crnt_addr_in = 0;
//
//	//u32 test;
//	//test = XGpio_DiscreteRead(&axi_gpio_rst_n_extern, 1);
//
//	// Set write_in = 1
//	//set_debug_write_in(WRITE_IN_ON);
//
//	// Write in 'len' words from 'buff'
//	for (uint32_t *wbuff = buff; wbuff - buff != len; ++wbuff)
//	{
//		// Lower debug_clk
//		crnt_dbg_clk = 0;
//		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);
//
//		// Set target address
//		XGpio_DiscreteWrite(&axi_gpio_debug_mem_addr, 1, crnt_addr_in);
//		crnt_addr_in += 4;
//
//		clock_half_delay();
//
//		// Set input data
//		crnt_data_in = *wbuff;
//		XGpio_DiscreteWrite(&axi_gpio_debug_mem_data, 2, crnt_data_in);
//
//		// Wait a debug half-cycle
//		clock_half_delay();
//
//		// Raise debug_clk
//		crnt_dbg_clk = 1;
//		XGpio_DiscreteWrite(&axi_gpio_debug, 1, crnt_dbg_clk);
//
//		// Wait a debug half-cycle
//		clock_half_delay();
//	}
//
//	// Set write_in = 0
//	//set_debug_write_in(WRITE_IN_OFF);
//
//	// Does not exit debug mode
}
