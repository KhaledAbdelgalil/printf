#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_hexaSmall_hashtag - Adds 0x + integer bytes as hexaSmall
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_hexaSmall_hashtag(va_list args, GLOBALBUFFER *printBuffer)
{
	u_int num;
	u_char bits[128];
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

	num = va_arg(args, int);
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
	add_to_buffer('0', printBuffer);
	add_to_buffer('x', printBuffer);
	idx = (int)len - 1;
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len);
}

/**
 * handle_hexaCapital_hashtag - Adds 0x + integer bytes as hexaCapital
 * representation to printf buffer
 * @args: input integer
 * @printBuffer: struct for buffer that holds data
 *
 * Return: number of added bytes
 */
u_int handle_hexaCapital_hashtag(va_list args, GLOBALBUFFER *printBuffer)
{
	u_int num;
	u_char bits[128];
	int idx = 0;
	u_int len = 0;
	int hexDigit = 0, rem = 0;

	num = va_arg(args, int);
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
	add_to_buffer('0', printBuffer);
	add_to_buffer('x', printBuffer);
	while (idx >= 0)
	{
		add_to_buffer(bits[idx--], printBuffer);
	}
	return (len);
}
