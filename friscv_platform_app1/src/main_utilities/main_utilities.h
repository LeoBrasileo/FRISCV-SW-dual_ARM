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

void setTargetAdress(u32 adress);
void setInputData(u32 data);
void raiseDebugClock();
void lowerDebugClock();
void waitDebugClockCycle();
void turnDebugOn();
void turnDebugAndWriteOn();
void turnDebugOff();

#endif
