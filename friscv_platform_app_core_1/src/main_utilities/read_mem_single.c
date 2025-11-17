#include "main_utilities.h"

int readMemSingle(){
	int status;
	status = XST_SUCCESS;
	u32  procitano;

	u32 adress = uart_receive_4_digit_num();
	//uint8_t format = uart_recv_byte();

	turnDebugOn();

	lowerDebugClock();
	setTargetAdress(adress);
	waitDebugClockCycle();
	procitano = XGpio_DiscreteRead(&axi_gpio_debug_mem_data, 1);
	delay_msec(1);

	uart_send_u32(procitano);
	LOG("[ARM] Read.\n");
	return status;
}
