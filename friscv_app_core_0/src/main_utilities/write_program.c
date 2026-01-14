#include "main_utilities.h"

int writeProgram(){
	int status;
	status = XST_SUCCESS;

	u32 program_size = uart_recv_u32();
	if (program_size == 0 || program_size > ARM1_SIZE) {
		LOG("[ERROR] Invalid program size!\n");
		return XST_FAILURE;
	}

	// load directly the program into shared DRAM
	load_from_host((void *)COMM_BASE_ADDR, program_size);

	// visibility to ARM1
	barrier_system();
	sync_system();
	Xil_DCacheFlushRange(COMM_BASE_ADDR, program_size);

	// sanity check just in case
	volatile u32 *mem = (volatile u32 *)COMM_BASE_ADDR;
	Xil_DCacheInvalidateRange((UINTPTR)mem, 4);
	if (mem[0] == 0) {
		LOG("[WARN] First instruction is zero\n");
	}

	LOG("[ARM] Program loaded into DRAM\n");

	return status;
}
