#include "main_utilities.h"

void send_d_mem_data(u32 data){
	XGpio_DiscreteWrite(&axi_gpio_d_mem_data, 1, data);
	delay_msec(1);
}

u32 receive_d_mem_data(){
	u32 d_data_out;
	d_data_out = XGpio_DiscreteRead(&axi_gpio_d_mem_data, 2);
	delay_msec(1);

	return d_data_out;
}

u32 receive_d_mem_address(){
	u32 d_addr_out;
	d_addr_out = XGpio_DiscreteRead(&axi_gpio_d_mem_addr, 1);
	delay_msec(1);

	return d_addr_out;
}

uint8_t d_write_out(){
	int d_ctrl;
	d_ctrl = XGpio_DiscreteRead(&axi_gpio_d_mem_ctrl, 1);
	delay_msec(1);

	uint8_t write_out = (d_ctrl & DBG_CPU_WRITE_OUT_MSK) != 0;
	return write_out;
}

uint8_t d_mem_enable_out(){
	int d_ctrl;
	d_ctrl = XGpio_DiscreteRead(&axi_gpio_d_mem_ctrl, 1);
	delay_msec(1);

	uint8_t mem_out = (d_ctrl & DBG_CPU_EN_OUT_MSK) != 0;
	return mem_out;
}

int d_size_out(){
	int d_size_out;
	d_size_out = XGpio_DiscreteRead(&axi_gpio_d_mem_ctrl, 2);
	delay_msec(1);

	return d_size_out;
}
