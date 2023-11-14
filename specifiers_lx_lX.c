#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_long_hexaSmall - Adds long integer bytes as hexaSmall
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_long_hexaSmall(va_list args, GLOBALBUFFER *printBuffer)
{
	l_int num;
	u_char bits[128];
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

	num = va_arg(args, l_int);
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
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len);
}

/**
 * handle_long_hexaCapital - Adds long integer bytes as hexaCapital
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_long_hexaCapital(va_list args, GLOBALBUFFER *printBuffer)
{
	l_int num;
	u_char bits[128];
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

	num = va_arg(args, l_int);
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
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len);
}
