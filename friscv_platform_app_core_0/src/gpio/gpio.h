#ifndef GPIO_HEADER
#define GPIO_HEADER

#include <xgpio.h>
// ne zaboravi i DIRM promjeniti

//Bits set to 0 are output and bits set to 1 are input.
//ovdje su reset i cpu_clock stopped, jedna maska
#define GPIO_ID_RST_N_EXTERN	XPAR_AXI_GPIO_RST_N_EXTERN_DEVICE_ID
#define DIRM_RST_N_EXTERN_CHANNEL_1		0x00000001u
#define DIRM_RST_N_EXTERN_CHANNEL_2		0x00000001u

//ovdje su dva kanala, jedan za dbg clk i jedan za debug control, dvije maske
#define GPIO_ID_DEBUG	XPAR_AXI_GPIO_DEBUG_DEVICE_ID
#define DIRM_DEBUG_CLK		0x00000000u
#define DIRM_DEBUG_CONTROL 0x00000000u

//ovdje su debug mem input i output, treba dvije maske
#define GPIO_ID_DEBUG_MEM_DATA	XPAR_AXI_GPIO_DEBUG_MEM_DATA_DEVICE_ID
#define DIRM_DEBUG_MEM_DATA_OUTPUT		0x00000000u
#define DIRM_DEBUG_MEM_DATA_INPUT		0xFFFFFFFFu

//ovdje je dbg mem addr, jedna maska
#define GPIO_ID_DEBUG_MEM_ADDR	XPAR_AXI_GPIO_DEBUG_MEM_ADDR_DEVICE_ID
#define DIRM_DEBUG_MEM_ADDR		0x00000000u

// --- CLK GENERATOR GPIO ---
#define GPIO_ID_CLK_GEN	XPAR_AXI_GPIO_CLK_GEN_DEVICE_ID
#define DIRM_CLK_GEN_CHANNEL_1	0x00000000u	// output
#define DIRM_CLK_GEN_CHANNEL_2	0x00000000u	// output

#define DBG_DEBUG_MODE_POS	0
#define DBG_WRITE_IN_POS	1
#define DBG_CLEAR_IN_POS	2

#define DBG_DEBUG_MODE_MSK	(1u << DBG_DEBUG_MODE_POS)
#define DBG_WRITE_IN_MSK	(1u << DBG_WRITE_IN_POS)
#define DBG_CLEAR_IN_MSK	(1u << DBG_CLEAR_IN_POS)

// --- Initialization state ---
extern int gpio_initialized;

// --- Driver instances ---
extern XGpio axi_gpio_rst_n_extern;	// INPUT AND OUTPUT TO FRISC-V
extern XGpio axi_gpio_debug;	// OUTPUT TO FRISC-V
extern XGpio axi_gpio_debug_mem_data;	// INPUT AND OUTPUT FROM FRISC-V
extern XGpio axi_gpio_debug_mem_addr;	// OUTPUT TO FRISC-V
extern XGpio axi_gpio_clk_gen;			// OUTPUTS TO CLOCK GENERATOR

// --- XGpio initialization ---
int gpio_init(void);

// --- Gpio current outputs ---
extern int crnt_addr_in;
extern int crnt_data_in;
extern int crnt_dbg_ctrl;
extern int crnt_rst_n_ext;
extern int crnt_dbg_clk;
extern int crnt_dbg_cpu_stopped_out;
extern int crnt_clk_gen_cpu;
extern int crnt_clk_gen_mem;

#endif
