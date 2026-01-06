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

#endif

#ifndef ARM1_UTILITIES_H
#define ARM1_UTILITIES_H

// ARM-1 addresses and instructions
#define sev() __asm__("sev")
#define ARM1_STARTADR   0xF8000244      // Correct SLCR register
#define ARM1_BASEADDR   0x1B500000      // ARM1 code load address
#define ARM1_SIZE      0x04A00000
#define COMM_BASE_ADDR 0x17300000
#define COMM_MEM ((volatile unsigned long *)COMM_BASE_ADDR)
#define CLK_CPU_FREQ_KHZ 100
#define CLK_MEM_FREQ_KHZ 400

void cpu_clk_up(void);
void cpu_clk_down(void);
void mem_clk_up(void);
void mem_clk_down(void);
u32 clk_compute_delay_us(float);

#endif
