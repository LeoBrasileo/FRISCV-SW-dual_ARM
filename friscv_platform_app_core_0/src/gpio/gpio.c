#include "gpio.h"

// --- Initialization state ---
int gpio_initialized = 0;

// --- Driver instances ---
XGpio axi_gpio_rst_n_extern;
XGpio axi_gpio_debug;
XGpio axi_gpio_debug_mem_data;
XGpio axi_gpio_debug_mem_addr;
XGpio axi_gpio_clk_gen;

// --- XGpio initialization ---
static int gpio_init_single(XGpio *gpio_instance, const u16 device_id, const u32 dirmask, unsigned Channel)
{
	// Get configuration for device id
	XGpio_Config *configPtr = XGpio_LookupConfig(device_id);
	if (configPtr == NULL) {
		return XST_FAILURE;
	}

	// Initialize with configuration
	int status = XGpio_CfgInitialize(gpio_instance, configPtr, configPtr->BaseAddress);
	if (status == XST_FAILURE) {
		return XST_FAILURE;
	}

	// Set direction of GPIO
	// XGpio_SetDataDirection(gpio_instance, Channel, dirmask);    OVO SAM ZAKOMETIRAO!!

	return XST_SUCCESS;
}

int gpio_init(void)
{
	if (gpio_initialized) {
		return XST_SUCCESS;
	}


	if (	// GPIO_RST_N_EXTERN_CHANNEL_1
			gpio_init_single(&axi_gpio_rst_n_extern, GPIO_ID_RST_N_EXTERN, DIRM_RST_N_EXTERN_CHANNEL_1, 1) == XST_FAILURE ||

			//GPIO_RST_N_EXTERN_CHANNEL_2
			gpio_init_single(&axi_gpio_rst_n_extern, GPIO_ID_RST_N_EXTERN, DIRM_RST_N_EXTERN_CHANNEL_2, 2) == XST_FAILURE ||

			// GPIO_DEBUG_CHANNEL_1
			gpio_init_single(&axi_gpio_debug, GPIO_ID_DEBUG, DIRM_DEBUG_CLK, 1) == XST_FAILURE ||

			// GPIO_DEBUG_CHANNEL_2
			gpio_init_single(&axi_gpio_debug, GPIO_ID_DEBUG, DIRM_DEBUG_CONTROL, 2) == XST_FAILURE ||

			// GPIO_DATA_CHANNEL_1 data from friscv(friscv output)
			gpio_init_single(&axi_gpio_debug_mem_data, GPIO_ID_DEBUG_MEM_DATA, DIRM_DEBUG_MEM_DATA_INPUT, 1) == XST_FAILURE ||

			// GPIO_DATA_CHANNEL_2, data to friscv(friscv input)
			gpio_init_single(&axi_gpio_debug_mem_data, GPIO_ID_DEBUG_MEM_DATA, DIRM_DEBUG_MEM_DATA_OUTPUT, 2) == XST_FAILURE ||

			// GPIO_DEBUG_ADDR
			gpio_init_single(&axi_gpio_debug_mem_addr, GPIO_ID_DEBUG_MEM_ADDR, DIRM_DEBUG_MEM_ADDR, 1) == XST_FAILURE ||

			// GPIO_CLK_GEN_CHANNEL_1 (CPU clock output)
			gpio_init_single(&axi_gpio_clk_gen, GPIO_ID_CLK_GEN, DIRM_CLK_GEN_CHANNEL_1, 1) == XST_FAILURE ||

			// GPIO_CLK_GEN_CHANNEL_2 (MEM clock output)
			gpio_init_single(&axi_gpio_clk_gen, GPIO_ID_CLK_GEN, DIRM_CLK_GEN_CHANNEL_2, 2) == XST_FAILURE
		) {
		return XST_FAILURE;
	}

	gpio_initialized = 1;
	return XST_SUCCESS;
}

// --- Gpio current outputs ---
int crnt_addr_in;
int crnt_data_in;
int crnt_dbg_ctrl;
int crnt_rst_n_ext;
int crnt_dbg_clk;
int crnt_dbg_cpu_stopped_out;
int crnt_clk_gen_cpu;
int crnt_clk_gen_mem;
