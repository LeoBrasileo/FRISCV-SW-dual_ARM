#include "host_loader.h"

#include "../uart/uart.h"

#include <stdint.h>


/**
 * Loads the binary program file from the host device (PC) into a
 * buffer 'buff' of a given length 'len' in bytes.
 * Will block if less than 'len' bytes are provided.
 */
void load_from_host(void *buff, const unsigned int len)
{
	for (u8 *wbuff = (u8 *)buff; wbuff - (u8 *)buff != len; ++wbuff)
	{
		*wbuff = uart_recv_byte();
	}
}
