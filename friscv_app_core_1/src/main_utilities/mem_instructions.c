#include "main_utilities.h"

void send_i_mem_data(u32 data){
	XGpio_DiscreteWrite(&axi_gpio_i_mem_data, 1, data);
	delay_msec(1);
}

u32 receive_i_mem_address(){
	u32 i_addr_out;
	i_addr_out = XGpio_DiscreteRead(&axi_gpio_i_mem_data, 2);
	delay_msec(1);

	return i_addr_out;
}

int i_mem_enable_out(){
	int i_mem_en_out;
	i_mem_en_out = XGpio_DiscreteRead(&axi_gpio_i_mem_ctrl, 1);
	delay_msec(1);

	return i_mem_en_out;
}
