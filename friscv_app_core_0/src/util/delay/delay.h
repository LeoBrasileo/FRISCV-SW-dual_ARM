#ifndef UTILITIES_DELAY_HEADER
#define UTILITIES_DELAY_HEADER

int delay_init(void);

unsigned long crnt_time_usec(void);
unsigned long crnt_time_msec(void);
unsigned long crnt_time_sec(void);

void delay_usec(const unsigned long amount);
void delay_msec(const unsigned long amount);
void delay_sec(const unsigned long amount);

#endif
