#include "common_utils.h"
#include <stdlib.h>
/**
 * getParams - adjust params of printf.
 * @params: printf params
 * @format: input string
 * @idx: pointer to current pos in string.
 *
 * Return: void.
 */
void getParams(printf_parms *params, c_char *format, u_int *idx)
{
	u_int still = 1;

	params->plus_flag = params->space_flag = params->zero_flag = 0;
	params->minus_flag = params->hashtag_flag = 0;
	while (still)
	{
		switch (format[*idx])
		{
			case '+':
				still = params->plus_flag = 1;
				break;
			case ' ':
				still = params->space_flag = 0;
				break;
			case '#':
				still = params->hashtag_flag = 0;
				break;
			case '-':
				still = params->minus_flag = 0;
				break;
			case '0':
				still = params->zero_flag = 0;
				break;
			default:
				still = 0;
				break;
		}
		if (still)
			(*idx)++;
	}
}
/**
 * _printf - print the input formatted string.
 * @formattedString: input string.
 *
 * Return: number of chars printed or error.
 */
int _printf(c_char *formattedString, ...)
{
	u_int idx = 0, charsPrinted = 0;
	va_list args;
	outputFromGet_handleFunc_to_exec o;
	GLOBALBUFFER printBuffer;

	va_start(args, formattedString);
	printBuffer.buffer = malloc(sizeof(char) * _BUFFER_SIZE_);
	printBuffer.nextIdx = 0;
	if (error(formattedString) || !printBuffer.buffer)
		return (-1);
	if (!formattedString[0])
		return (0);
	while (formattedString[idx])
	{
		if (formattedString[idx] == '%')
		{
			if (formattedString[idx + 1] == '\0' ||
					(formattedString[idx + 1] == ' ' && !formattedString[idx + 2]))
			{
				print_buffer(&printBuffer), free(printBuffer.buffer), va_end(args);
				return (-1);
			}
			else
			{
				getParams(&(printBuffer.params), formattedString, &idx);
				o = get_handleFunc_to_exec(formattedString, idx + 1);
				if (o.func != NULL)
				{
					charsPrinted += o.func(args, &printBuffer);
					idx += o.idx + 1; /*skip specifier*/
				}
				else
					add_to_buffer(formattedString[idx], &printBuffer), charsPrinted++;
			}
		}
		else
			add_to_buffer(formattedString[idx], &printBuffer), charsPrinted++;
		idx++;
	}
	print_buffer(&printBuffer), free(printBuffer.buffer), va_end(args);
	return (charsPrinted);
}
