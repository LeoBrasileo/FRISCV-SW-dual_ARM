#include "debug_and_test.h"

int Debug(){
	int status;
	status = XST_SUCCESS;

	u32 tmp, i, j, k;

	for (i = 0; i < COMM_DEBUG_WORDS; i++) {
	    tmp = COMM_DEBUG_MEM[i];

	    j = i & 127;
	    k = ((j + 1) << 24) |
	        ((j + 2) << 16) |
	        ((j + 3) << 8)  |
	        (j + 4);

	    if (tmp != k) {
	        LOG("[ERROR] Wrong value at i=");
	        uart_send_int(i);
	        LOG(" Read: ");
	        uart_send_hex(tmp);
	        LOG(" Expected: ");
	        uart_send_hex(k);
	        LOG("\n\r");
	    }
	}

	LOG("[INFO] DRAM reading done\n\r");

	return status;
}
