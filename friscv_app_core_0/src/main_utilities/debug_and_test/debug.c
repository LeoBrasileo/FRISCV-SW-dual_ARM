#include "debug_and_test.h"

int Debug(){
	int status;
	status = XST_SUCCESS;

	u32 tmp, i, j, k;
	for (i = 0; i < COMM_DEBUG_WORDS; i++) {
	    j = i & 127;
	    tmp = ((j + 1) << 24) |
	          ((j + 2) << 16) |
	          ((j + 3) << 8)  |
	          (j + 4);

	    COMM_DEBUG_MEM[i] = tmp;
	}

	// Ensure all writes reach DRAM
	barrier_system();
	sync_system();

	COMM_CTRL.debug = 1;

	LOG("[INFO] DRAM writing done\n\r");

	return status;
}
