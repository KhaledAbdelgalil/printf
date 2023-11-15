#include "common_utils.h"
#include <stdarg.h>
#include <limits.h>

/**
 * handle_zero - handleZeroCase in hexa
 * @printBuffer: printf Buffer
 * Return: number of added bytes
 */
u_int handle_zero(GLOBALBUFFER *printBuffer)
{
	u_int lenDigits = 1, usedWidth = 1, lenPadding = 0;
	u_int padding = 0, i = 0;

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
 * handle_hexaSmall - Adds integer bytes as hexaSmall
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_hexaSmall(va_list args, GLOBALBUFFER *printBuffer)
{
	ul_int num;
	u_char bits[128], ones = 0;
	u_int len = 0, usedWidth = 0, lenPadding = 0, lenDigits = 0;
	u_int padding = 0, i = 0;
	int idx = 0, hexDigit = 0, rem = 0;

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
	if (num == 0)
		return (handle_zero(printBuffer));

	while (num)
	{
		rem = num % 16;
		if (rem < 10)
			hexDigit = rem + 48;
		else
			hexDigit = rem - 10 + 'a';
		bits[len++] = hexDigit, num = num / 16;
	}
	lenDigits = len;
	idx = (int)len - 1, usedWidth = len + 2 * (printBuffer->params.hashtag_flag);
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (padding + usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), lenPadding++;
	if (printBuffer->params.hashtag_flag)
		add_to_buffer('0', printBuffer), add_to_buffer('x', printBuffer), ones = 2;
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	while (idx >= 0)
		add_to_buffer(bits[idx--], printBuffer);
	return (padding + lenPadding + len + ones);
}

/**
 * handle_hexaCapital - Adds integer bytes as hexaCapital
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_hexaCapital(va_list args, GLOBALBUFFER *printBuffer)
{
	ul_int num;
	u_char bits[128], ones = 0;
	u_int len = 0, lenPadding = 0, usedWidth = 0, lenDigits = 0;
	u_int padding = 0, i = 0;
	int hexDigit = 0, rem = 0, idx = 0;

	if (printBuffer->params.l_modifier)
		num = (ul_int)va_arg(args, ul_int);
	else if (printBuffer->params.h_modifier)
		num = (us_int)va_arg(args, u_int);
	else
		num = (u_int)va_arg(args, u_int);
	if (num == 0)
		return (handle_zero(printBuffer));

	while (num)
	{
		rem = num % 16;
		if (rem < 10)
			hexDigit = rem + 48;
		else
			hexDigit = rem - 10 + 'A';
		bits[len++] = hexDigit;
		num = num / 16;
	}
	lenDigits = len;
	usedWidth = len + 2 * (printBuffer->params.hashtag_flag);
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (padding + usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), lenPadding++;
	if (printBuffer->params.hashtag_flag)
		add_to_buffer('0', printBuffer), add_to_buffer('X', printBuffer), ones = 2;
	idx = (int)len - 1;
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	while (idx >= 0)
		add_to_buffer(bits[idx--], printBuffer);
	return (padding + lenPadding + len + ones);
}
