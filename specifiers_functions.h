#ifndef _SPECIFIERS_FUNCTIONS_H_
#define _SPECIFIERS_FUNCTIONS_H_
#include "complex_types.h"
#include <stdarg.h>
u_int handle_str(va_list, GLOBALBUFFER*);
u_int handle_percentage(va_list, GLOBALBUFFER*);
u_int handle_char(va_list, GLOBALBUFFER*);
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
u_int handle_short_oct(va_list args, GLOBALBUFFER *printBuffer);
#endif
