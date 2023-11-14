#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_short_oct - Adds short integer bytes
 * as oct representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_short_oct(va_list args, GLOBALBUFFER *printBuffer)
{
	s_int num;
	u_char bits[128];
	int idx = 0;
	u_int len = 0;

	num = va_arg(args, int);
	if (num == 0)
	{
		add_to_buffer('0', printBuffer);
		return (1);
	}

	while (num)
	{
		bits[len++] = num % 8 + 48;
		num = num / 8;
	}
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len);
}
