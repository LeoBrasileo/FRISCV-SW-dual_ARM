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

	u32 addr;
	u32 word;
	u32 data;
	u32 offset;
	u32 size;

	while (1) {
//		cpu_clk_up();
//		delay_usec(delay_cpu_us);
//		cpu_clk_down();
//		delay_usec(delay_cpu_us);

		// Instruction Memory Phase
		if (i_mem_enable_out()) {

			addr = receive_i_mem_address();
			word = addr >> 2;

			/* Make sure we see latest DRAM */
			Xil_DCacheInvalidateRange((UINTPTR)&COMM_MEM[word],sizeof(u32));

			data = COMM_MEM[word];

			/* Drive instruction back to CPU */
			send_i_mem_data(data);

			cpu_clk_half_cycle();

		// Data Memory Phase
		} else if (d_mem_enable_out()) {

			addr = receive_d_mem_address();
			word = addr >> 2;
			offset = addr & 0x3;
			size = d_size_out();

			if (!d_write_out())	{
				// READ

				Xil_DCacheInvalidateRange((UINTPTR)&COMM_MEM[word], sizeof(u32));

				data = COMM_MEM[word];
				send_d_mem_data(data);
			} else {
				// WRITE

				data = receive_d_mem_data();

				switch(size){
					case 0: { //Byte
						u32 tmp = COMM_MEM[word];
						tmp &= ~(0xFF << (offset * 8));
						tmp |=  ((data & 0xFF) << (offset * 8));
						COMM_MEM[word] = tmp;
						break;
					}
					case 1: { //Half Word
						u32 tmp = COMM_MEM[word];
						if ((offset & 0x2) == 0) {
							tmp &= ~0x0000FFFF;
							tmp |=  (data & 0xFFFF);
						} else {
							tmp &= ~0xFFFF0000;
							tmp |=  (data << 16);
						}
						COMM_MEM[word] = tmp;
						break;
					}
					case 2: { //Word
						COMM_MEM[word] = data;
						break;
					}
					default:
						break;
				}

				Xil_DCacheFlushRange((UINTPTR)&COMM_MEM[word], sizeof(u32));
			}

			cpu_clk_half_cycle();
		}

	}

	return status;
}
