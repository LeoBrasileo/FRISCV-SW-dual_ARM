#include "main_utilities.h"

int writeData(){
	int status;
	status = XST_SUCCESS;

	u32 addressBegin = uart_receive_4_digit_num();
	u32 addressEnd = uart_receive_4_digit_num();

	if (addressEnd <= addressBegin) {
		LOG("[ERROR] Invalid address range\n\r");
		return XST_FAILURE;
	}

	// Load Data from host PC
	uint32_t data[PROGRAM_WORD_COUNT] = {0};
	memset(data, 0, 1024 * sizeof(uint32_t));
	load_from_host(data, PROGRAM_WORD_COUNT * 4);
	LOG("[ARM] Loaded data from host\n");
	delay_msec(1);

	for (u32 i = addressBegin; i < addressEnd; i++) {
		COMM_MEM[i] = data[i];
	}

	barrier_system();
	sync_system();
	Xil_DCacheFlushRange((UINTPTR)&COMM_MEM[addressBegin], (addressEnd - addressBegin) * sizeof(u32));

	LOG("[ARM] Loaded data into DRAM\n");

	return status;
}
