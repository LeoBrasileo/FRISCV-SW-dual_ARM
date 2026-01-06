#ifndef GPIO_HEADER
#define GPIO_HEADER

#include <xgpio.h>
// don't forget to change DIRM too

//Bits set to 0 are output and bits set to 1 are input.

#define GPIO_ID_CLK_GEN_N_DEBUG XPAR_AXI_GPIO_CLK_GEN_N_DEBUG_DEVICE_ID
#define DIRM_CLK_GEN_N_DEBUG_CHANNEL_1		0x00000000u //clk_cpu signal
#define DIRM_CLK_GEN_N_DEBUG_CHANNEL_2		0x00000000u //debug_mode_in signal

//here are reset and cpu_clock stopped, one mask
#define GPIO_ID_RST_N_EXTERN	XPAR_AXI_GPIO_RST_N_EXTERN_DEVICE_ID
#define DIRM_RST_N_EXTERN_CHANNEL_1		0x00000001u
#define DIRM_RST_N_EXTERN_CHANNEL_2		0x00000001u

#define GPIO_ID_I_MEM_DATA XPAR_AXI_GPIO_I_MEM_DATA_DEVICE_ID
#define DIRM_I_MEM_DATA_OUTPUT		0x00000000u
#define DIRM_I_MEM_DATA_INPUT		0xFFFFFFFFu

#define GPIO_ID_I_MEM_CTRL XPAR_AXI_GPIO_I_MEM_CTRL_DEVICE_ID
#define DIRM_I_MEM_CTRL_OUTPUT 0x00000000u

#define GPIO_ID_D_MEM_DATA XPAR_AXI_GPIO_D_MEM_DATA_DEVICE_ID
#define DIRM_D_MEM_DATA_OUTPUT		0x00000000u
#define DIRM_D_MEM_DATA_INPUT		0xFFFFFFFFu

#define GPIO_ID_D_MEM_ADDR XPAR_AXI_GPIO_D_MEM_ADDR_DEVICE_ID
#define DIRM_D_MEM_ADDR_INPUT		0xFFFFFFFFu

#define GPIO_ID_D_MEM_CTRL XPAR_AXI_GPIO_D_MEM_CTRL_DEVICE_ID
#define DIRM_D_MEM_CTRL 		0x00000000u
#define DIRM_D_MEM_SIZE			0x00000000u

#define DBG_CPU_WRITE_OUT_POS	0
#define DBG_CPU_EN_OUT_POS	1
#define DBG_CPU_WRITE_OUT_MSK (1u << DBG_CPU_WRITE_OUT_POS)
#define DBG_CPU_EN_OUT_MSK (1u << DBG_CPU_EN_OUT_POS)

// --- Initialization state ---
extern int gpio_initialized;

// --- Driver instances ---
extern XGpio axi_gpio_clk_gen_n_debug; // OUTPUTS OF CLK GENERATOR AND DEBUG MODE SIGNAL
extern XGpio axi_gpio_rst_n_extern;	// INPUT AND OUTPUT TO FRISC-V
extern XGpio axi_gpio_i_mem_data;	// INPUT AND OUTPUT 32b INSTRUCTIONS TO FRISC-V
extern XGpio axi_gpio_i_mem_ctrl;	// INPUT 1b CPU CTRL FROM FRISC-V
extern XGpio axi_gpio_d_mem_data;	// INPUT AND OUTPUT 32b DATA TO FRISC-V
extern XGpio axi_gpio_d_mem_addr;	// INPUT 32b DATA FROM FRISC-V
extern XGpio axi_gpio_d_mem_ctrl;	// INPUT 2b DATA CTRL AND SIZE FROM FRISC-V

// --- XGpio initialization ---
int gpio_init(void);

// --- Gpio current outputs ---
extern int crnt_clk_gen_cpu;
extern int crnt_debug_mode_in;
extern int crnt_rst_n_ext;
extern int crnt_cpu_i_mem_data_in;
extern int crnt_cpu_d_mem_data_in;


#endif
