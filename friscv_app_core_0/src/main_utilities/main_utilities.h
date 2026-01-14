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

void turnDebugOn();
void turnDebugOff();

#define barrier_system() __asm__ volatile("dmb sy")
#define sync_system() __asm__ volatile("dsb sy")

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


void start_arm1(void);

#endif
