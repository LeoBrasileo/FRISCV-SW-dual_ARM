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
int run(void);
int pause(void);
int clearMem(void);
int writeProgram(void);
int writeData(void);
int readMemRange(void);
int readMemSingle(void);

// Memory now is managed in DRAM, no use for inserting data from debug
//void setTargetAdress(u32 adress);
//void setInputData(u32 data);

// debug clock ceased to exist :(
//void raiseDebugClock();
//void lowerDebugClock();
//void waitDebugClockCycle();

void turnDebugOn();
// there is no write on flag anymore
//void turnDebugAndWriteOn();
void turnDebugOff();

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

void start_arm1(void);

#endif
