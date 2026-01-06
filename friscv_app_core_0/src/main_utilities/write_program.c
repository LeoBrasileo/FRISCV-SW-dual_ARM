#include "main_utilities.h"

int writeProgram(){
	int status;
	status = XST_SUCCESS;

	uint32_t program[PROGRAM_WORD_COUNT] = {0};
	memset(program, 0, 1024 * sizeof(uint32_t));
	load_from_host(program, PROGRAM_WORD_COUNT * 4);
	LOG("[ARM] Loaded program from host\n");
	delay_msec(1);

	for (u32 i = 0; i < PROGRAM_WORD_COUNT; i++){
		COMM_MEM[i] = program[i];
	}

	// visibility to ARM1
	barrier_system();
	sync_system();
	Xil_DCacheFlushRange(COMM_BASE_ADDR, PROGRAM_WORD_COUNT * sizeof(u32));

	// sanity check just in case
	if (COMM_MEM[0] != program[0]) {
	    LOG("[ERROR] Program load failed!\n\r");
	    status = XST_FAILURE;
	} else {
		LOG("[ARM] Loaded program into DRAM\n");
	}

	return status;
}
