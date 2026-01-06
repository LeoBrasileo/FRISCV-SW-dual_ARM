#include "main_utilities.h"

int readMemSingle(){
	int status;
	status = XST_SUCCESS;
	u32 read;

	u32 address = uart_receive_4_digit_num();

	Xil_DCacheInvalidateRange((UINTPTR)&COMM_MEM[address],1 * sizeof(u32));
	sync_system();

	read = COMM_MEM[address];
	delay_msec(1);

	uart_send_u32(read);
	LOG("[ARM] Read.\n");

	return status;
}
