#include "main_utilities.h"

int writeProgram(){
	int status;
	status = XST_SUCCESS;

	uint32_t program[PROGRAM_WORD_COUNT] = {0};
	memset(program, 0, 1024 * sizeof(uint32_t));
	load_from_host(program, PROGRAM_WORD_COUNT * 4);
	LOG("[ARM] Loaded program from host\n");
	delay_msec(1);

	turnDebugAndWriteOn();
	lowerDebugClock();

	for (u32 i = 0;i < PROGRAM_WORD_COUNT;i++){
		setTargetAdress(i);
		setInputData(program[i]);
		waitDebugClockCycle();
	}
	LOG("[ARM] Loaded program into FRISCV\n");

	turnDebugOn();
	return status;
}
