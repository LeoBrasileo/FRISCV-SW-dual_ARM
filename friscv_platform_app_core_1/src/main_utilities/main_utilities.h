#ifndef MAIN_UTILS_HEADER
#define MAIN_UTILS_HEADER

#include "../friscv_com/friscv_com.h"
#include "../host_loader/host_loader.h"
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

int reset_processor(void);
int main_init(void);
int clk_gpio_init(void);
int run(void);
int pause(void);
int clearMem(void);
int writeProgram(void);
int writeData(void);
int readMemRange(void);
int readMemSingle(void);

void setTargetAdress(u32 adress);
void setInputData(u32 data);
void raiseDebugClock();
void lowerDebugClock();
void waitDebugClockCycle();
void turnDebugOn();
void turnDebugAndWriteOn();
void turnDebugOff();

#endif

#ifndef ARM1_UTILITIES_H
#define ARM1_UTILITIES_H

// ARM-1 addresses and instructions
#define sev() __asm__("sev")
#define ARM1_STARTADR 0xFFFFFFF0
#define ARM1_BASEADDR 0x1FF00000
#define ARM1_SIZE      0x00040000
#define COMM_VAL  (*(volatile unsigned long *)(0xFFFF0000))
#define CLK_CPU_FREQ_MHZ 100
#define CLK_MEM_FREQ_MHZ 200

void start_arm1(void);
void signal_arm1(void);

void cpu_clk_up(void);
void cpu_clk_down(void);
void mem_clk_up(void);
void mem_clk_down(void);
u32 clk_compute_delay_us(float);

#endif
