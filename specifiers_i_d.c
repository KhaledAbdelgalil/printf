#include "common_utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
/**
 * handle_not_print - handle not printing any chars.
 * @buffer: print buffer
 * Return: number of bytes
 *
 */
u_int handle_not_print(GLOBALBUFFER *buffer)
{
	u_int count = buffer->params.width, i = 0;

	while (i < count)
		add_to_buffer(' ', buffer), i++;
	return (count);
}
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
 * @pB: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_int(va_list args, GLOBALBUFFER *pB)
{
	l_int num;
	ul_int absNum, powers = 1, padding = 0, i = 0, notprint = 0;
	u_int one = 0, digits = 0, usedWidth = 0, lenPadding = 0, lenDigits = 0;
	char pad = pB->params.zero_flag && !pB->params.minus_flag ? '0' : ' ';

	if (pB->params.l_modifier)
		num = va_arg(args, l_int);
	else if (pB->params.h_modifier)
		num = (s_int)va_arg(args, int);
	else
		num = (int)va_arg(args, int);
	usedWidth = getUsedWidth(pB, num, 1);
	lenDigits = getUsedWidth(pB, num, 0);
	notprint = (pB->params.percision == 0 && num == 0);
	if (notprint)
		return (handle_not_print(pB));
	if (pB->params.percision != UINT_MAX && pB->params.percision > lenDigits)
		padding = pB->params.percision - lenDigits;
	while (padding + usedWidth++ < pB->params.width)
		add_to_buffer(pad, pB), lenPadding++;
	if (num < 0)
		num  = num * -1, add_to_buffer('-', pB), one = 1;
	else
	{
		if (pB->params.plus_flag)
			add_to_buffer('+', pB), one = 1;
		else if (pB->params.space_flag)
			add_to_buffer(' ', pB), one = 1;
	}
	absNum = num;
	while (i < padding)
		add_to_buffer('0', pB), i++;
	while (absNum > 9)
		powers = powers * 10, absNum = absNum / 10;
	while (powers)
	{
		add_to_buffer((num / powers) % 10 + 48, pB);
		powers = powers / 10, digits++;
	}
	return (digits + one + lenPadding + padding);
}
