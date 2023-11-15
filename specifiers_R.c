#include "common_utils.h"
#include <stdarg.h>
#include <string.h>
/**
 * handle_rot - writes the str in ROT13
 * @args: input string
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes
 */

u_int handle_rot(va_list args, GLOBALBUFFER *printBuffer)
{
	char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char rot[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	char *tmpStr;
	u_int i, j, taken;
	char nill[] = "(avyy)";

	tmpStr = va_arg(args, char *);
	if (tmpStr == NULL)
	{
		for (i = 0; i <= 5; i++)
			add_to_buffer(nill[i], printBuffer);
		return (6);
	}
	for (i = 0; tmpStr[i]; i++)
	{
		taken = 0;
		for (j = 0; chars[j]; j++)
		{
			if (tmpStr[i] == chars[j])
			{
				taken = 1;
				add_to_buffer(rot[j], printBuffer);
				break;
			}
		}
		if (taken == 0)
		{
			add_to_buffer(tmpStr[i], printBuffer);
		}
	}
	return (i);
}
