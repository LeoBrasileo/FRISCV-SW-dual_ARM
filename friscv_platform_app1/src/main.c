#include "main.h"

int main(void)
{
	int status;
	char byte;
	int test;

	status = main_init();
	if (status == XST_FAILURE) {
		//LOG("[ERROR] Failed to initialize AXI GPIOs\n");
		return XST_FAILURE;
	}

	delay_msec(20);
	LOG("[INFO] UART driver and AXI GPIOs init success\n");
	delay_msec(20);
	while(1){
		test = uart_recv_byte();
		byte = (char)test;
		switch (byte){
		case '1':
			LOG("[ARM]Reset!\n");
			delay_msec(20);
			status = reset_processor();
			break;
		case '2':
			LOG("[ARM]Run!\n");
			delay_msec(20);
			status = run();
			break;
		case '3':
			LOG("[ARM]Pause!\n");
			delay_msec(20);
			status = pause();
			break;
		case '4':
			LOG("[ARM]Clear memory!\n");
			delay_msec(20);
			status = clearMem();
			break;
		case '5':
			LOG("[ARM]Write program!\n");
			delay_msec(20);
			status = writeProgram();
			break;
		case '6':
			LOG("[ARM]Write data!\n");
			delay_msec(20);
			status = writeData();
			break;
		case '7':
			LOG("[ARM]Read memory(range)!\n");
			delay_msec(20);
			status = readMemRange();
			break;
		case '8':
			LOG("[ARM]Read memory(single)!\n");
			delay_msec(20);
			status = readMemSingle();
			break;
		case '9':
			LOG("[ARM]Debug!\n");
			delay_msec(20);
			status = Debug();
			break;
		default:
			LOG("[ARM]Default(so skip)!\n");
		}
		if (status == XST_FAILURE){
			return XST_FAILURE;
		}
	}
	return status;
}
