#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_oct - Adds integer bytes as oct representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_oct(va_list args, GLOBALBUFFER *printBuffer)
{
	ul_int num;
	u_char bits[128], one = 0;
	int idx = 0;
	u_int len = 0;

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
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
	if (printBuffer->params.hashtag_flag)
		add_to_buffer('0', printBuffer), one = 1;
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len + one);
}
