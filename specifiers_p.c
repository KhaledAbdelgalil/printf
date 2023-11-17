#include "common_utils.h"
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
/**
 * handle_address - Adds address bytes as hexaSmall
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_address(va_list args, GLOBALBUFFER *printBuffer)
{
	ul_int num;
	void *address;
	u_char bits[128];
	int idx = 0;
	u_int len = 0, padding = 0, lenDigits = 0, i = 0;
	int hexDigit = 0, rem = 0;

	address = va_arg(args, void *);
	if (address == NULL)
	{
		add_to_buffer('(', printBuffer), add_to_buffer('n', printBuffer);
		add_to_buffer('i', printBuffer), add_to_buffer('l', printBuffer);
		add_to_buffer(')', printBuffer);
		return (5);
	}
	num = (intptr_t)address;
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
	add_to_buffer('0', printBuffer);
	add_to_buffer('x', printBuffer);
	lenDigits = len;
	if (printBuffer->params.percision != UINT_MAX
			&& printBuffer->params.percision > lenDigits)
		padding = printBuffer->params.percision - lenDigits;
	while (i < padding)
		add_to_buffer('0', printBuffer), i++;
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (padding + len + 2);
}
