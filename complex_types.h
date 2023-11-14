#ifndef _COMPLEX_TYPES_H_
#define _COMPLEX_TYPES_H_
#include "primitive_types.h"
#include <stdarg.h>
#include <stddef.h>
#define _BUFFER_SIZE_ 1024

/**
 * struct parameters - parameters struct
 *
 * @plus_flag: on if plus_flag specified
 * @space_flag: on if space_flag specified
 * @hashtag_flag: on if hashtag_flag specified
 * @zero_flag: on if zero_flag specified
 * @minus_flag: on if minus_flag specified
 * @h_modifier: for short
 * @l_modifier: for long
 *
 * Description: printf params
 */
typedef struct parameters
{
	u_int plus_flag;
	u_int space_flag;
	u_int hashtag_flag;
	u_int zero_flag;
	u_int minus_flag;

	u_int h_modifier;
	u_int l_modifier;

} printf_parms;
/**
 * struct GLOBALBUFFER - struct for printf Buffer
 * used across program
 *
 * @buffer: buffer in memory
 * @nextIdx: pointer to place of insertion new bytes
 * @params: like flags, width,...
 * Description: printf buffer struct
 */
typedef struct GLOBALBUFFER
{
	char *buffer;
	u_int nextIdx;/*could be used as length*/
	printf_parms params;
} GLOBALBUFFER;

/**
 * struct printSpecifierToCorrespondingFunc - struct to map specifier to
 * handling specifier function pointer
 *
 * @specifier: like d,i,s,c...
 * @func: pointer to the handling functions
 *
 * Description: struct that stores pointers to
 * the handling functions.
 */
typedef struct printSpecifierToCorrespondingFunc
{
/*specifier like d,i,s,c ... ,func pointer to add to buffer*/
	c_char *specifier;
	u_int (*func)(va_list, GLOBALBUFFER*);
} SpecifierToFunc;



/**
 * struct outputFromGet_handleFunc_to_exec - struct for storing output
 * from get_handleFunc_to_exec
 *
 * @idx: length to skip specifiers in formatted string
 * @func: pointer to handling function
 *
 * Description: struct for output of get_handleFunc_to_exec
 */
typedef struct outputFromGet_handleFunc_to_exec
{
	int idx;
	u_int (*func)(va_list, GLOBALBUFFER*);
} outputFromGet_handleFunc_to_exec;
#endif
