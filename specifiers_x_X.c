#include "common_utils.h"
#include <stdarg.h>
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
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

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
		rem = num % 16;
		if (rem < 10)
			hexDigit = rem + 48;
		else
			hexDigit = rem - 10 + 'a';
		bits[len++] = hexDigit;
		num = num / 16;
	}
	idx = (int)len - 1;
	if (printBuffer->params.hashtag_flag)
	{
		add_to_buffer('0', printBuffer);
		add_to_buffer('x', printBuffer);
		ones = 2;
	}
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len + ones);
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
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

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
		rem = num % 16;
		if (rem < 10)
			hexDigit = rem + 48;
		else
			hexDigit = rem - 10 + 'A';
		bits[len++] = hexDigit;
		num = num / 16;
	}
	if (printBuffer->params.hashtag_flag)
	{
		add_to_buffer('0', printBuffer);
		add_to_buffer('X', printBuffer);
		ones = 2;
	}
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len + ones);
}
