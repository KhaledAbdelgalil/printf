#include "common_utils.h"
#include <stdlib.h>
/**
 * getWidth - adjust width in params of printf.
 * @params: printf params
 * @format: input string
 * @idx: pointer to current pos in string.
 * @args: args
 * Return: void.
 */
void getWidth(printf_parms *params, c_char *format, u_int *idx, va_list args)
{
	u_int w = 0;

	params->width = 0;
	if (format[*idx] == '*')
	{
		w = va_arg(args, int);
		(*idx)++;
	}
	else
	{
		while (format[*idx] >= '0' && format[*idx] <= '9')
			w = w * 10 + (format[*idx] - '0'), (*idx)++;
	}
	params->width = w;
}
/**
 * getModifier - adjust modifiers in params of printf.
 * @params: printf params
 * @format: input string
 * @idx: pointer to current pos in string.
 *
 * Return: void.
 */
void getModifier(printf_parms *params, c_char *format, u_int *idx)
{
	u_int still = 0; /*check for modifier*/

	params->h_modifier = params->l_modifier = 0;
	switch (format[*idx])
	{
		case 'h':
			still = params->h_modifier = 1;
			break;
		case 'l':
			still = params->l_modifier = 1;
			break;
	}
	if (still)
		(*idx)++;
}

/**
 * getParams - adjust params of printf.
 * @params: printf params
 * @format: input string
 * @idx: pointer to current pos in string.
 * @args: args
 * Return: void.
 */
void getParams(printf_parms *params, c_char *format, u_int *idx, va_list args)
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
				still = params->space_flag = 1;
				break;
			case '#':
				still = params->hashtag_flag = 1;
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
	getWidth(params, format, idx, args);
	getModifier(params, format, idx);
}
/**
 * _printf - print the input formatted string.
 * @format: input string.
 *
 * Return: number of chars printed or error.
 */
int _printf(c_char *format, ...)
{
	u_int idx = 0, chars = 0, initialIdx = 0;
	va_list args;
	outputFromGet_handleFunc_to_exec o;
	GLOBALBUFFER printBuffer;

	va_start(args, format), printBuffer.buffer = malloc(_BUFFER_SIZE_);
	printBuffer.nextIdx = 0;
	if (error(format) || !printBuffer.buffer)
		return (-1);
	if (!format[0])
		return (0);
	while (format[idx])
	{
		if (format[idx] == '%')
		{
			if (format[idx + 1] == '\0' || (format[idx + 1] == ' ' && !format[idx + 2]))
			{
				print_buffer(&printBuffer), free(printBuffer.buffer), va_end(args);
				return (-1);
			}
			else
			{
				initialIdx = idx++, getParams(&(printBuffer.params), format, &idx, args);
				o = get_handleFunc_to_exec(format, idx);
				if (o.func != NULL)
					chars += o.func(args, &printBuffer);
				else
				{
					idx = initialIdx, add_to_buffer(format[idx], &printBuffer), chars++;
					idx = printBuffer.params.h_modifier || printBuffer.params.l_modifier ?
						idx + 1 : idx;
				}
			}
		}
		else
			add_to_buffer(format[idx], &printBuffer), chars++;
		idx++;
	}
	print_buffer(&printBuffer), free(printBuffer.buffer), va_end(args);
	return (chars);
}
