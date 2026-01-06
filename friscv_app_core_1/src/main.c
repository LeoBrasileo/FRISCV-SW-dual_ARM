#include "main.h"

int main(void)
{
	int status;

	status = main_init();
	if (status == XST_FAILURE) {
		return XST_FAILURE;
	}

	delay_msec(20);
	LOG("[ARM-1] ARM-1 activated\n");
	delay_msec(20);

	//Disable cache on OCM
	Xil_SetTlbAttributes(0x0DB91000,0x14de2); // S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0

	u32 delay_cpu_us = clk_compute_delay_us(CLK_CPU_FREQ_KHZ);
	u32 delay_mem_us = clk_compute_delay_us(CLK_MEM_FREQ_KHZ);

	while (1) {

		cpu_clk_up();
		//mem_clk_up();

		delay_usec(delay_mem_us);

		//mem_clk_down();

		delay_usec(delay_mem_us);

		cpu_clk_down();
		//mem_clk_up();

		delay_usec(delay_mem_us);

		//mem_clk_down();

		delay_usec(delay_mem_us);
	}

	return status;
}
