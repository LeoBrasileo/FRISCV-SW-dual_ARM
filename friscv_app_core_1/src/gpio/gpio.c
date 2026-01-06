#include "gpio.h"

// --- Initialization state ---
int gpio_initialized = 0;

// --- Driver instances ---
XGpio axi_gpio_clk_gen_n_debug;
XGpio axi_gpio_rst_n_extern;
XGpio axi_gpio_i_mem_data;
XGpio axi_gpio_i_mem_ctrl;
XGpio axi_gpio_d_mem_data;
XGpio axi_gpio_d_mem_addr;
XGpio axi_gpio_d_mem_ctrl;

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


	if (	// GPIO_CLK_GEN_N_DEBUG_CHANNEL_1 (CPU clock output)
			gpio_init_single(&axi_gpio_clk_gen_n_debug, GPIO_ID_CLK_GEN_N_DEBUG, DIRM_CLK_GEN_N_DEBUG_CHANNEL_1, 1) == XST_FAILURE ||

			// GPIO_CLK_GEN_N_DEBUG_CHANNEL_2 (Debug signal output)
			gpio_init_single(&axi_gpio_clk_gen_n_debug, GPIO_ID_CLK_GEN_N_DEBUG, DIRM_CLK_GEN_N_DEBUG_CHANNEL_2, 2) == XST_FAILURE ||

			// GPIO_RST_N_EXTERN_CHANNEL_1
			gpio_init_single(&axi_gpio_rst_n_extern, GPIO_ID_RST_N_EXTERN, DIRM_RST_N_EXTERN_CHANNEL_1, 1) == XST_FAILURE ||

			// GPIO_RST_N_EXTERN_CHANNEL_2
			gpio_init_single(&axi_gpio_rst_n_extern, GPIO_ID_RST_N_EXTERN, DIRM_RST_N_EXTERN_CHANNEL_2, 2) == XST_FAILURE ||

			// GPIO_I_MEM_DATA_CHANNEL_1
			gpio_init_single(&axi_gpio_i_mem_data, GPIO_ID_I_MEM_DATA, DIRM_I_MEM_DATA_OUTPUT, 1) == XST_FAILURE ||

			// GPIO_I_MEM_DATA_CHANNEL_2
			gpio_init_single(&axi_gpio_i_mem_data, GPIO_ID_I_MEM_DATA, DIRM_I_MEM_DATA_INPUT, 2) == XST_FAILURE ||

			// GPIO_I_MEM_CTRL_CHANNEL_1
			gpio_init_single(&axi_gpio_i_mem_ctrl, GPIO_ID_I_MEM_CTRL, DIRM_I_MEM_CTRL_OUTPUT, 1) == XST_FAILURE ||

			// GPIO_D_MEM_DATA_CHANNEL_1
			gpio_init_single(&axi_gpio_d_mem_data, GPIO_ID_D_MEM_DATA, DIRM_I_MEM_DATA_OUTPUT, 1) == XST_FAILURE ||

			// GPIO_D_MEM_DATA_CHANNEL_2
			gpio_init_single(&axi_gpio_d_mem_data, GPIO_ID_D_MEM_DATA, DIRM_I_MEM_DATA_INPUT, 2) == XST_FAILURE ||

			// GPIO_D_MEM_ADDR_CHANNEL_1
			gpio_init_single(&axi_gpio_d_mem_addr, GPIO_ID_D_MEM_ADDR, DIRM_D_MEM_ADDR_INPUT, 1) == XST_FAILURE ||

			// GPIO_D_MEM_CTRL_CHANNEL_1
			gpio_init_single(&axi_gpio_d_mem_ctrl, GPIO_ID_D_MEM_CTRL, DIRM_D_MEM_CTRL, 1) == XST_FAILURE ||

			// GPIO_D_MEM_CTRL_CHANNEL_1
			gpio_init_single(&axi_gpio_d_mem_ctrl, GPIO_ID_D_MEM_CTRL, DIRM_D_MEM_SIZE, 2) == XST_FAILURE
		) {
		return XST_FAILURE;
	}

	gpio_initialized = 1;
	return XST_SUCCESS;
}

// --- Gpio current outputs ---
int crnt_clk_gen_cpu;
int crnt_debug_mode_in;
int crnt_rst_n_ext;
int crnt_cpu_i_mem_data_in;
int crnt_cpu_d_mem_data_in;
