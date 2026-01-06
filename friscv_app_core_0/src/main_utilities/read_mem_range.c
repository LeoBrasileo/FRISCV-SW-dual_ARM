#include "main_utilities.h"

int readMemRange(){
	int status;
	status = XST_SUCCESS;
	u32 addressBegin = uart_receive_4_digit_num();
	u32 addressEnd = uart_receive_4_digit_num();

	if (addressEnd <= addressBegin) {
		LOG("[ERROR] Invalid address range\n\r");
		return XST_FAILURE;
	}

	// we need to invalidate cache to see latest data
	Xil_DCacheInvalidateRange((UINTPTR)&COMM_MEM[addressBegin],(addressEnd - addressBegin) * sizeof(u32));

	sync_system();

	for (u32 i = addressBegin; i < addressEnd; i++) {
		uart_send_u32(COMM_MEM[i]);
		delay_msec(50);
	}

	LOG("[ARM] Read Memory\n");

	return status;
}
