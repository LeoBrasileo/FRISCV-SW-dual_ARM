#include "debug_and_test.h"

int Debug(){
	int status;
	status = XST_SUCCESS;
	u32  tmp, i,j,k;

	lowerDebugClock();
	turnDebugAndWriteOn();

	for (i=0;i<1024;i++){
		setTargetAdress(i);
		j=i&127;
		tmp=((j+1)<<24)+((j+2)<<16)+((j+3)<<8)+(j+4);
		setInputData(tmp);
		waitDebugClockCycle();
	}
	LOG("[INFO] Pisanje gotovo\n\r");
	turnDebugOn();

	for (i=0;i<1024;i++){
		setTargetAdress(i);
		waitDebugClockCycle();

		tmp = XGpio_DiscreteRead(&axi_gpio_debug_mem_data, 1);
		delay_msec(1);
		j=i&127;
		k=((j+1)<<24)+((j+2)<<16)+((j+3)<<8)+(j+4);

		if (tmp!=k){
			LOG("[INFO] Krivo: za i=\n\r");
			uart_send_int(i);
		}
	}
	LOG("[INFO] Procitano\n\r");

	turnDebugOff();
	return status;
}
