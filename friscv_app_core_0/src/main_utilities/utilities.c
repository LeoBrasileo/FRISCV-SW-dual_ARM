#include "main_utilities.h"

void turnDebugOn(){
	//XGpio_DiscreteWrite(&axi_gpio_debug, 2, DEBUG_MODE_ON);

	XGpio_DiscreteWrite(&axi_gpio_clk_gen_n_debug, 2, DEBUG_MODE_ON);
	delay_msec(1);
}

void turnDebugOff(){
	//XGpio_DiscreteWrite(&axi_gpio_debug, 2, DEBUG_MODE_OFF);

	XGpio_DiscreteWrite(&axi_gpio_clk_gen_n_debug, 2, DEBUG_MODE_OFF);
	delay_msec(1);
}

//void setTargetAdress(u32 adress){
//	XGpio_DiscreteWrite(&axi_gpio_debug_mem_addr, 1, adress * 4);
//	delay_msec(1);
//}
//
//void setInputData(u32 inputData){
//	XGpio_DiscreteWrite(&axi_gpio_debug_mem_data, 2, inputData);
//	delay_msec(1);
//}

//void raiseDebugClock(){
//	XGpio_DiscreteWrite(&axi_gpio_debug, 1, 1);
//	delay_msec(1);
//}
//
//void lowerDebugClock(){
//	XGpio_DiscreteWrite(&axi_gpio_debug, 1, 0);
//	delay_msec(1);
//}
//
//void waitDebugClockCycle(){
//	raiseDebugClock();
//	lowerDebugClock();
//}

//void turnDebugAndWriteOn(){
//	XGpio_DiscreteWrite(&axi_gpio_debug, 2, DEBUG_MODE_ON | DEBUG_MEM_WR);
//	delay_msec(1);
//}

