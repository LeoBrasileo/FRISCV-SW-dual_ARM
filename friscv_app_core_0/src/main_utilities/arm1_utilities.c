#include "main_utilities.h"

void start_arm1(void)
{
    // Make shared COMM_VAL region uncached
    Xil_SetTlbAttributes(COMM_BASE_ADDR, 0x14de2);

    //Make sure OCM is visible
    Xil_DCacheFlushRange(ARM1_BASEADDR, ARM1_SIZE);
    Xil_ICacheInvalidateRange(ARM1_BASEADDR, ARM1_SIZE);

    //CPU1 start vector (boot address)
    Xil_Out32(ARM1_STARTADR, ARM1_BASEADDR);
    dmb();

    // Finally wake ARM1
    sev();
}
