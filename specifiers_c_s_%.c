#include "common_utils.h"
#include <stdarg.h>
#include <string.h>
#include <limits.h>
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
	u_int outchars, usedWidth = 0, lenPadding = 0, len = 0;

	tmpStr = va_arg(args, char *);
	if (tmpStr == NULL)
	{
		tmpStr = nullStr;
	}
	outchars = len = usedWidth = strlen(tmpStr);
	if (printBuffer->params.percision != UINT_MAX &&
			printBuffer->params.percision < len)
		outchars = usedWidth = printBuffer->params.percision;

	while (usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), lenPadding++;
	for (; i < outchars; i++)
		add_to_buffer(tmpStr[i], printBuffer);
	return (outchars + lenPadding);
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
	u_int usedWidth = 1;
	u_int len = 0;

	while (usedWidth++ < printBuffer->params.width)
		add_to_buffer(' ', printBuffer), len++;
	c = va_arg(args, int);
	add_to_buffer(c, printBuffer);
	return (1 + len);
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
