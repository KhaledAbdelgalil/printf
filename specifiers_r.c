#include "common_utils.h"
#include <stdarg.h>
#include <string.h>
/**
 * handle_rev_str - Adds string bytes in reverse order to printf buffer
 * @args: input string
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes
 */
u_int handle_rev_str(va_list args, GLOBALBUFFER *printBuffer)
{
	char *tmpStr;
	int i = 0, len = 0;
	char nullStr[] = "(null)";

	tmpStr = va_arg(args, char *);
	if (tmpStr == NULL)
	{
		for (i = 5; i >= 0; i--)
			add_to_buffer(nullStr[i], printBuffer);
		return (6);
	}
	len = strlen(tmpStr);
	i = len - 1;
	for (; i >= 0; i--)
		add_to_buffer(tmpStr[i], printBuffer);
	return (len);
}

