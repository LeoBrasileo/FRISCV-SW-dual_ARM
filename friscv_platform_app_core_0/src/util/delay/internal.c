#include "internal.h"

#include <xscutimer.h>
#include <xscugic.h>
#include "xil_exception.h"

int delay_initialized = 0;
volatile unsigned long usec_passed = 0;

XScuGic gic_driver;
XScuTimer timer_driver;

/* f_cpu = 650 MHz => f_3x2x = 325
 * f_tim = 1 MHz
 * => T = 10e-6 s = (LOAD + 1)(PRESCALER + 1)/f_cpu
 * => LOAD = 313, PRESCALER = 0
 */
#define TIMER_LOAD_REG_VALUE 325
#define TIMER_PRESCALER_VALUE 0

static void timer_isr(void *CallbackRef);

int delay_init(void)
{
	// Done if already initialized
	if (delay_initialized) {
		return XST_SUCCESS;
	}

	// -------------- (1) TIMER INIT ------------------------------------------------------------
	// Initialize timer driver
	XScuTimer_Config *timer_config = XScuTimer_LookupConfig(XPAR_XSCUTIMER_0_DEVICE_ID);
	int status = XScuTimer_CfgInitialize(&timer_driver, timer_config, timer_config->BaseAddr);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Configure timer
	XScuTimer_EnableAutoReload(&timer_driver);
	XScuTimer_LoadTimer(&timer_driver, TIMER_LOAD_REG_VALUE);
	XScuTimer_SetPrescaler(&timer_driver, TIMER_PRESCALER_VALUE);
	XScuTimer_Start(&timer_driver);


	// -------------- (2) XILINX EXCEPTION ENV INIT  --------------------------------------------
	Xil_ExceptionInit();

	// -------------- (3) GET INTERRUPT HANDLER AND REGISTER IT ---------------------------------
	XScuGic_Config *gic_config = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	status = XScuGic_CfgInitialize(&gic_driver, gic_config, gic_config->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Xil_ExceptionRegisterHandler(
		XIL_EXCEPTION_ID_IRQ_INT,
		(Xil_ExceptionHandler)XScuGic_InterruptHandler,
		&gic_driver
	);

	// -------------- (4) CONNECT USER ISR TO GIC ---------------------------------------------
	status = XScuGic_Connect(
		&gic_driver, XPAR_SCUTIMER_INTR,
		(Xil_ExceptionHandler)timer_isr,
		&timer_driver
	);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// -------------- (5) GIC ENABLE INTERRUPTING ------------------------------------------
	XScuGic_Enable(&gic_driver, XPAR_SCUTIMER_INTR);

	// -------------- (6) TIMER ENABLE INTERRUPTING ------------------------------------------
	XScuTimer_EnableInterrupt(&timer_driver);

	// -------------- (7) ENABLE CPU INTERRUPTING ------------------------------------------
	Xil_ExceptionEnable();

	delay_initialized = 1;
	return XST_SUCCESS;
}

// Increments the passed microseconds variable and clears interrupt status
static void timer_isr(void *CallbackRef)
{
	XScuTimer *timer_driver_ptr = (XScuTimer *)CallbackRef;
	++usec_passed;
	XScuTimer_ClearInterruptStatus(timer_driver_ptr);
}
