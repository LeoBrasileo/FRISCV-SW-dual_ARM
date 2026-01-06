#include "main_utilities.h"

int run(){
	int status;
	status = XST_SUCCESS;

	turnDebugOff();

	LOG("[ARM] FRISCV started.\n");
	return status;
}

int pause(){
	int status;
	status = XST_SUCCESS;

	turnDebugOn();

	LOG("[ARM] FRISCV stopped.\n");
	return status;
}
