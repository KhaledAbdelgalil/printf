#include "common_utils.h"
#include <stdarg.h>
#include <limits.h>
/**
 * handle_zero_o - handleZeroCase octal
 * @printBuffer: printf Buffer
 * Return: number of added bytes
 */
u_int handle_zero_o(GLOBALBUFFER *printBuffer)
{
	u_int lenDigits = 1, usedWidth = 1, lenPadding = 0;
	u_int padding = 0, i = 0;

	if (printBuffer->params.percision == 0)
	{
		usedWidth = 0;
		while (usedWidth++ < printBuffer->params.width)
			add_to_buffer(' ', printBuffer), lenPadding++;
		return (lenPadding);
	}
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (padding + usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), lenPadding++;
	add_to_buffer('0', printBuffer);
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	return (1 + lenPadding + padding);
}

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
	u_int len = 0, usedWidth = 0, lenPadding = 0;
	u_int lenDigits = 0, padding  = 0, i = 0;
	char pad = printBuffer->params.zero_flag
		&& !printBuffer->params.minus_flag ? '0' : ' ';

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
	if (num == 0)
	{
		return (handle_zero_o(printBuffer));
	}

	while (num)
	{
		bits[len++] = num % 8 + 48;
		num = num / 8;
	}
	lenDigits = len;
	usedWidth = len + printBuffer->params.hashtag_flag;
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (padding + usedWidth++ < printBuffer->params.width)
		add_to_buffer(pad, printBuffer), lenPadding++;
	if (printBuffer->params.hashtag_flag)
		add_to_buffer('0', printBuffer), one = 1;
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (padding + lenPadding + len + one);
}
