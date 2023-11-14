#include "common_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/**
 * getUsedWidth - get used width of number
 * @p: buffer struct
 * @num: num
 *
 * Return: used width
 */
u_int getUsedWidth(GLOBALBUFFER *p, l_int num)
{
	char str[128];
	u_int usedWidth = 0;

	snprintf(str, sizeof(str), "%ld", num);
	usedWidth = strlen(str);
	if (num >= 0 && p->params.plus_flag)
		usedWidth++;
	return (usedWidth);
}
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
	ul_int absNum, powers = 1;
	u_int one = 0, digits = 0, usedWidth = 0, len = 0;

	if (printBuffer->params.l_modifier)
		num = va_arg(args, l_int);
	else if (printBuffer->params.h_modifier)
		num = (s_int)va_arg(args, int);
	else
		num = (int)va_arg(args, int);
	usedWidth = getUsedWidth(printBuffer, num);
	while (usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), len++;
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
	return (digits + one + len);
}
