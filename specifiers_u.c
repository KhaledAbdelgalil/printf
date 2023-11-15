#include "common_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/**
 * getUsedWidth - get used width of number
 * @num: num
 *
 * Return: used width
 */
u_int getUsedWidth(ul_int num)
{
	char str[128];
	u_int usedWidth = 0;

	snprintf(str, sizeof(str), "%ld", num);
	usedWidth = strlen(str);
	return (usedWidth);
}
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
	u_int digits = 0, usedWidth = 0, len;

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
	absNum = num;
	usedWidth = getUsedWidth(num);
	while (usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), len++;
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
	return (digits + len);
}
