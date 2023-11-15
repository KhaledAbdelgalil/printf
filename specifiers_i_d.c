#include "common_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
/**
 * getUsedWidth - get used width of number
 * @p: buffer struct
 * @num: num
 * @wOrL: flag
 *
 * Return: used width
 */
u_int getUsedWidth(GLOBALBUFFER *p, l_int num, int wOrL)
{
	char str[128];
	u_int usedWidth = 0;

	snprintf(str, sizeof(str), "%ld", num);
	usedWidth = strlen(str);
	if (num >= 0 && p->params.plus_flag && wOrL)
		usedWidth++;
	else if (wOrL == 0 && num < 0)
		usedWidth--;
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
	ul_int absNum, powers = 1, padding = 0, i = 0;
	u_int one = 0, digits = 0, usedWidth = 0, lenPadding = 0, lenDigits = 0;

	if (printBuffer->params.l_modifier)
		num = va_arg(args, l_int);
	else if (printBuffer->params.h_modifier)
		num = (s_int)va_arg(args, int);
	else
		num = (int)va_arg(args, int);
	usedWidth = getUsedWidth(printBuffer, num, 1);
	lenDigits = getUsedWidth(printBuffer, num, 0);
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (padding + usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), lenPadding++;
	if (num < 0)
		num  = num * -1, add_to_buffer('-', printBuffer), one = 1;
	else
	{
		if (printBuffer->params.plus_flag)
			add_to_buffer('+', printBuffer), one = 1;
		else if (printBuffer->params.space_flag)
			add_to_buffer(' ', printBuffer), one = 1;
	}
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	absNum = num;
	while (absNum > 9)
		powers = powers * 10, absNum = absNum / 10;
	while (powers)
	{
		add_to_buffer((num / powers) % 10 + 48, printBuffer);
		powers = powers / 10, digits++;
	}
	return (digits + one + lenPadding + padding);
}
