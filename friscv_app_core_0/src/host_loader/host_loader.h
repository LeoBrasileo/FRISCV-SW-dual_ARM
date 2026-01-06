#ifndef DEBUG_PROGRAMMER_HEADER
#define DEBUG_PROGRAMMER_HEADER

#include <xstatus.h>

/**
 * Loads the binary program file from the host device (PC) into a
 * buffer 'buff' of a given length 'len' in bytes.
 * Will block if less than 'len' bytes are provided.
 */
void load_from_host(void *buff, const unsigned int len);

#endif
