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
	u_int num;
	u_int absNum;
	u_int powers = 1;
	u_int digits = 0;

	num = va_arg(args, int);
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
