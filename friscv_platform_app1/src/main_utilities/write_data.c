#include "main_utilities.h"

int writeData(){
	int status;
	status = XST_SUCCESS;

	u32 adressBegin = uart_receive_4_digit_num();
	u32 adressEnd = uart_receive_4_digit_num();

	// Load Data from host PC
	uint32_t data[PROGRAM_WORD_COUNT] = {0};
	memset(data, 0, 1024 * sizeof(uint32_t));
	load_from_host(data, PROGRAM_WORD_COUNT * 4);
	LOG("[ARM] Loaded data from host\n");
	delay_msec(1);

	turnDebugAndWriteOn();
	lowerDebugClock();

	for (u32 i=adressBegin;i<adressEnd;i++){
		setTargetAdress(i);
		setInputData(data[i]);
		waitDebugClockCycle();
	}
	LOG("[ARM] Loaded data into FRISCV\n");

	turnDebugOn();
	return status;
}
