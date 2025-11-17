#ifndef UTILITIES_DELAY_INTERNAL_HEADER
#define UTILITIES_DELAY_INTERNAL_HEADER

extern int delay_initialized;
extern volatile unsigned long usec_passed;
int delay_init(void);

#endif
