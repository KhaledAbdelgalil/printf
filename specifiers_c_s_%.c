#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_str - Adds string bytes to printf buffer
 * @args: input string
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes
 */
u_int handle_str(va_list args, GLOBALBUFFER *printBuffer)
{
	char *tmpStr;
	u_int i = 0;
	char nullStr[] = "(null)";

	tmpStr = va_arg(args, char *);
	if (tmpStr == NULL)
	{
		for (; i <= 5; i++)
			add_to_buffer(nullStr[i], printBuffer);
		return (6);
	}
	for (; tmpStr[i]; i++)
		add_to_buffer(tmpStr[i], printBuffer);
	return (i);
}

/**
 * handle_char - Adds input char  byte to printf buffer
 * @args: input char
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes i.e 1
 */
u_int handle_char(va_list args, GLOBALBUFFER  *printBuffer)
{
	char c;

	c = va_arg(args, int);
	add_to_buffer(c, printBuffer);
	return (1);
}

/**
 * handle_percentage - Adds input %  byte to printf buffer
 * @args: not used here
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes i.e 1
 */
u_int handle_percentage(va_list args, GLOBALBUFFER  *printBuffer)
{
	(void)args;

	add_to_buffer('%', printBuffer);
	return (1);
}
