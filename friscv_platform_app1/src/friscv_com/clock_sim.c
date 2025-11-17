#include "friscv_com.h"

#include "../util/delay/delay.h"

// --- Simulate clock delay ---
void clock_half_delay(void)
{
	// f_debug = 500 kHz
	//delay_usec(1);
	delay_msec(1000);
}
