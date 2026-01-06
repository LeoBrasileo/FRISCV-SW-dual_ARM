#include "main_utilities.h"

int clearMem(){
	int status;
	status = XST_SUCCESS;

	volatile u32 *ptr;
	u32 words;
	u32 i;

	// Calculate shared DRAM size in 32-bit words
	words = (ARM1_BASEADDR - COMM_BASE_ADDR) / sizeof(u32);
	ptr = (volatile u32 *)COMM_BASE_ADDR;

	for (i = 0; i < words; i++) {
		ptr[i] = 0;
	}

	// Ensure all writes reach DRAM
	barrier_system();
	sync_system();

	// Flush cache
	Xil_DCacheFlushRange(COMM_BASE_ADDR, words * sizeof(u32));

	LOG("[ARM] FRISCV memory cleared.\n");

	return status;
}
