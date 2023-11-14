#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_uint - Adds unsigned integer bytes to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_uint(va_list args, GLOBALBUFFER *printBuffer)
{
	ul_int num;
	ul_int absNum;
	ul_int powers = 1;
	u_int digits = 0;

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
	absNum = num;

	while (absNum > 9)
	{
		powers = powers * 10;
		absNum = absNum / 10;
	}

	while (powers)
	{
		add_to_buffer((num / powers) % 10 + 48, printBuffer);
		powers = powers / 10;
		digits++;
	}
	return (digits);
}
