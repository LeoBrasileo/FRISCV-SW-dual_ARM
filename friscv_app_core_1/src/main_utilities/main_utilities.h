#ifndef MAIN_UTILS_HEADER
#define MAIN_UTILS_HEADER

#include "../friscv_com/friscv_com.h"
#include "../uart/uart.h"
#include "../gpio/gpio.h"
#include "../util/delay/delay.h"
#include <xstatus.h>
#include <stdio.h>
#include <xil_printf.h>
#include <string.h>

#define LOG(string) (uart_send_string((string), sizeof((string)) - 1))

#define PROGRAM_WORD_COUNT (1 << 10) // 1024 * 4B = 4kB
#define PRINTABLE_BUFFER_LEN 256

int main_init(void);
void cpu_clk_up(void);
void cpu_clk_down(void);
void cpu_clk_half_cycle(void);


void send_i_mem_data(u32 data);
u32 receive_i_mem_address(void);

uint8_t i_mem_enable_out(void); // it is really just a bit

void send_d_mem_data(u32 data);
u32 receive_d_mem_data(void);

u32 receive_d_mem_address(void);

uint8_t d_write_out(void);
uint8_t d_mem_enable_out(void);
int d_size_out(void);


// ARM-1 addresses and instructions
#define sev() __asm__("sev")
#define ARM1_STARTADR   0xF8000244      // Correct SLCR register
#define ARM1_BASEADDR   0x1B500000      // ARM1 code load address
#define ARM1_SIZE      0x04A00000
#define COMM_BASE_ADDR 0x17300000
#define COMM_MEM ((volatile unsigned long *)COMM_BASE_ADDR)
#define CLK_CPU_FREQ_KHZ 100
#define CLK_MEM_FREQ_KHZ 400

#define COMM_SHARED_SIZE   (62 * 1024 * 1024)  // 62 MB
// Internal control flags, last 4 bytes
#define COMM_CTRL_ADDR   (COMM_BASE_ADDR + COMM_SHARED_SIZE - 4)
typedef union {
    u32 raw;
    struct {
        u32 pause : 1;   // bit 0
        u32 debug : 1;   // bit 1
        u32 reserved : 30;
    };
} comm_ctrl_t;
#define COMM_CTRL   (*(volatile comm_ctrl_t *)COMM_CTRL_ADDR)
// Debug buffer, 4kB
#define COMM_DEBUG_SIZE  (4 * 1024)
#define COMM_DEBUG_ADDR  (COMM_CTRL_ADDR - COMM_DEBUG_SIZE)
#define COMM_DEBUG_WORDS (COMM_DEBUG_SIZE / sizeof(u32))
#define COMM_DEBUG_MEM  ((volatile u32 *)COMM_DEBUG_ADDR)

u32 clk_compute_delay_us(float);


#define INSTRUCTION_CACHE_SIZE 1024
void preload_instruction_cache(u32);

#endif
