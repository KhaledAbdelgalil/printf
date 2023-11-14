#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_int - Adds integer bytes to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_int(va_list args, GLOBALBUFFER *printBuffer)
{
	l_int num;
	ul_int absNum;
	u_char one = 0;
	ul_int powers = 1;
	u_int digits = 0;

	if (printBuffer->params.l_modifier)
		num = va_arg(args, l_int);
	else if (printBuffer->params.h_modifier)
		num = (s_int)va_arg(args, int);
	else
		num = (int)va_arg(args, int);
	if (num < 0)
	{
		num  = num * -1;
		add_to_buffer('-', printBuffer);
		one = 1;
	}
	else
	{
		if (printBuffer->params.plus_flag)
			add_to_buffer('+', printBuffer), one = 1;
		else if (printBuffer->params.space_flag)
			add_to_buffer(' ', printBuffer), one = 1;
	}
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
	return (digits + one);
}
