#include "debug_and_test.h"

int Debug(){
	int status;
	status = XST_SUCCESS;

	u32 tmp, i, j, k;
	for (i = 0; i < 1024; i++) {
	    j = i & 127;
	    tmp = ((j + 1) << 24) |
	          ((j + 2) << 16) |
	          ((j + 3) << 8)  |
	          (j + 4);

	    COMM_MEM[i] = tmp;
	}

	// Ensure all writes reach DRAM
	barrier_system();
	sync_system();

	LOG("[INFO] DRAM writing done\n\r");


	for (i = 0; i < 1024; i++) {
	    tmp = COMM_MEM[i];

	    j = i & 127;
	    k = ((j + 1) << 24) |
	        ((j + 2) << 16) |
	        ((j + 3) << 8)  |
	        (j + 4);

	    if (tmp != k) {
	        LOG("[ERROR] Wrong value at i=\n\r");
	        uart_send_int(i);
	        LOG(" Read: ");
	        uart_send_hex(tmp);
	        LOG(" Expected: ");
	        uart_send_hex(k);
	        LOG("\n\r");
	    }
	}

	LOG("[INFO] DRAM read done\n\r");

	// TODO: The read must be the same from core_1,
	// ideally this function should also trigger the read on that core.

	return status;
}
