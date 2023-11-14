#include "common_utils.h"
#include <unistd.h>
/*foward decalarations*/
u_int handle_str(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_percentage(va_list args, GLOBALBUFFER  *printBuffer);
u_int handle_char(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_int(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_binary(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_hexaCapital(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_hexaSmall(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_oct(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_uint(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_special_str(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_address(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_plus_int(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_space_int(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_hexaCapital_hashtag(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_hexaSmall_hashtag(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_oct_hashtag(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_long_int(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_short_int(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_long_uint(va_list args, GLOBALBUFFER *printBuffer);
u_int handle_short_uint(va_list args, GLOBALBUFFER *printBuffer);
/**
 * add_to_buffer - writes the character c to the buffer
 * @c: input char to be written to the buffer
 * @printBuffer: struct for buffer that holds data
 * Return: void.
 */
void add_to_buffer(char c, GLOBALBUFFER *printBuffer)
{
	if (printBuffer->nextIdx == _BUFFER_SIZE_)
	{
		print_buffer(printBuffer);
		printBuffer->nextIdx = 0;
	}
	(printBuffer->buffer)[printBuffer->nextIdx] = c;
	(printBuffer->nextIdx)++;
}

/**
 * get_handleFunc_to_exec - select the correct handling funcion
 * according to the input specifier
 * @formattedString: formatted string
 * @idx: idx of specifier in formatted string
 * Return: struct
 */
outputFromGet_handleFunc_to_exec
	get_handleFunc_to_exec(c_char *formattedString, int idx)
{
	SpecifierToFunc mapSpecifierToFuncPointer[] = {
	{"c", handle_char}, {"s", handle_str}, {"%", handle_percentage},
	{" %", handle_percentage}, {"d", handle_int}, {"i", handle_int},
	{"li", handle_long_int}, {"ld", handle_long_int},
	{"hi", handle_short_int}, {"hd", handle_short_int},
	{"b", handle_binary}, {"x", handle_hexaSmall},
	{"X", handle_hexaCapital}, {"o", handle_oct},
	{"u", handle_uint}, {"lu", handle_long_uint}, {"S", handle_special_str},
	{"p", handle_address}, {"+x", handle_hexaSmall}, {"hu", handle_short_uint},
	{"+X", handle_hexaCapital}, {"+o", handle_oct},
	{" X", handle_hexaCapital}, {" x", handle_hexaSmall},
	{" o", handle_oct}, {"+i", handle_plus_int}, {"+d", handle_plus_int},
	{" i", handle_space_int}, {" d", handle_space_int},
	{"#x", handle_hexaSmall_hashtag}, {"#X", handle_hexaCapital_hashtag},
	{"#d", handle_int}, {"#i", handle_int}, {"#o", handle_oct_hashtag},
	{"+u", handle_uint}, {"#u", handle_uint}, {" u", handle_uint},
	{" +i", handle_plus_int}, {" +d", handle_plus_int},
	{"+ i", handle_plus_int}, {"+ d", handle_plus_int}, {NULL, NULL} };
	int i = 0, j = 0, reset_idx = idx;
	outputFromGet_handleFunc_to_exec output;

	while (mapSpecifierToFuncPointer[i].specifier != NULL)
	{
		if (formattedString[idx] == mapSpecifierToFuncPointer[i].specifier[j])
		{
			if (mapSpecifierToFuncPointer[i].specifier[j + 1] != '\0')
			{
				idx++; /*advance to next char in specifier*/
				j++;
			}
			else
			{
				break;
			}
		}
		else
		{
			j = 0; /*start from starting of specifier in map*/
			i++; /*advance in map*/
			/* reset to check from starting of specifier in formattedString*/
			idx = reset_idx;
		}
	}
	output.func  = mapSpecifierToFuncPointer[i].func;
	output.idx = j;
	return (output);
}
/**
 * print_buffer - prints the printf buffer
 * @printBuffer: struct for buffer that holds data
 * Return: number of printed bytes
 */
u_int print_buffer(GLOBALBUFFER *printBuffer)
{
	return (write(1, printBuffer->buffer, printBuffer->nextIdx));
}
/**
 * error - checks for errors in formated string
 * @formattedString: input string
 * Return: 0(no error) or 1(error)
 */
u_char error(c_char *formattedString)
{
	return (!formattedString ||
			(formattedString[0] == '%' && !formattedString[1]));
}
