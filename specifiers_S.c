#include "common_utils.h"
#include <stdarg.h>
/**
 * handle_special_str - Adds string bytes to printf buffer
 * except for non-printable vars (asci < 32 or >= 127),
 * they are printed as \x followed by upper hexa(2 digits)
 *
 * @args: input string
 * @printBuffer: struct for buffer that holds data
 * Return: number of added bytes
 */
u_int handle_special_str(va_list args, GLOBALBUFFER *printBuffer)
{
	char *tmpStr;
	u_int i = 0;
	u_int specialChars = 0;
	u_char bits[10] = {0};
	u_int len = 0, asci = 0, rem = 0, hexDigit = 0;
	int idx = 0;

	tmpStr = va_arg(args, char *);
	for (; tmpStr[i]; i++)
	{
		if (tmpStr[i] < 32 || tmpStr[i] >= 127)
		{
			len = 0;
			add_to_buffer('\\', printBuffer);
			add_to_buffer('x', printBuffer);
			specialChars += 3;
			asci = (int)tmpStr[i];
			len = 0;
			while (asci)
			{
				rem = asci % 16;
				if (rem < 10)
					hexDigit = rem + 48;
				else
					hexDigit = rem - 10 + 'A';
				bits[len++] = hexDigit;
				asci = asci / 16;
			}
			if (len == 1)
				bits[len++] = '0';
			idx  = (int)len - 1;
			while (idx >= 0)
				add_to_buffer(bits[idx--], printBuffer);
			continue;
		}
		add_to_buffer(tmpStr[i], printBuffer);
	}
	return (i + specialChars);
}
