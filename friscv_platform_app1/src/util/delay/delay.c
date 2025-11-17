#include "delay.h"

#include "internal.h"

unsigned long crnt_time_usec(void)
{
	if (!delay_initialized) {
		delay_init();
	}
	return usec_passed;
}
unsigned long crnt_time_msec(void)
{
	if (!delay_initialized) {
		delay_init();
	}
	return crnt_time_usec() / 1e3;
}
unsigned long crnt_time_sec(void)
{
	if (!delay_initialized) {
		delay_init();
	}
	return crnt_time_usec() / 1e6;
}

void delay_usec(const unsigned long amount)
{
	if (!delay_initialized) {
		delay_init();
	}
	const unsigned start_time = crnt_time_usec();
	while (crnt_time_usec() - start_time < amount);
}
void delay_msec(const unsigned long amount)
{
	if (!delay_initialized) {
		delay_init();
	}
	const unsigned start_time = crnt_time_msec();
	while (crnt_time_msec() - start_time < amount);
}
void delay_sec(const unsigned long amount)
{
	if (!delay_initialized) {
		delay_init();
	}
	const unsigned start_time = crnt_time_sec();
	while (crnt_time_sec() - start_time < amount);
}
