#include "main_utilities.h"

int clearMem(){
	int status;
	status = XST_SUCCESS;

	turnDebugAndWriteOn();
	lowerDebugClock();

	for (u32 i=0;i<1024;i++){
		setTargetAdress(i);
		setInputData(0);
		waitDebugClockCycle();
	}

	turnDebugOn();
	LOG("[ARM] FRISCV memory cleared.\n");

	return status;
}
