#ifndef FRISCV_COMMUNICATION_HEADER
#define FRISCV_COMMUNICATION_HEADER

#include <stdint.h>

void reset_friscv(void);

#define DEBUG_MODE_OFF	0
#define DEBUG_MODE_ON	1
#define DEBUG_MEM_WR	2


/**
 * Load binary program from buffer 'buff' of length 'len' in words into
 * FRISC-V device under test.
 */
void load_into_friscv(uint32_t *buff, const unsigned int len);

/**
 * Reads 'len' words from 'address' of FRISC-V memory into 'buff' buffer.
 */
void load_from_friscv(uint32_t *buff, const unsigned int address, const unsigned int len);

// --- Simulate clock delay ---
void clock_half_delay(void);

#endif
