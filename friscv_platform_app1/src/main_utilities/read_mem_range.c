#include "main_utilities.h"

int readMemRange(){
	int status;
	status = XST_SUCCESS;
	u32 adressBegin = uart_receive_4_digit_num();
	u32 adressEnd = uart_receive_4_digit_num();
	//uint8_t format = uart_recv_byte();

	turnDebugOn();

	uint32_t readMem[PROGRAM_WORD_COUNT] = {0};
	memset(readMem, 0, 1024 * sizeof(uint32_t));

	lowerDebugClock();

	for (u32 i = adressBegin;i < adressEnd;i++){
		setTargetAdress(i);
		waitDebugClockCycle();
		readMem[i] = XGpio_DiscreteRead(&axi_gpio_debug_mem_data, 1);
		delay_msec(1);
	}


	for (u32 i = adressBegin;i < adressEnd;i++){
		uart_send_u32(readMem[i]);
		delay_msec(10);
	}
	LOG("[ARM] Read Memory\n");
	return status;
}
