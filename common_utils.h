#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_
#include "complex_types.h"
u_int handle_from_to(c_char *f, u_int, u_int, u_int, GLOBALBUFFER *p);
void add_to_buffer(char c, GLOBALBUFFER *printBuffer);
u_int print_buffer(GLOBALBUFFER *printBuffer);

outputFromGet_handleFunc_to_exec get_handleFunc_to_exec(c_char*, int);
/*return pointer to function like handle_str, handle_char*/

u_char error(c_char *formattedString);
#endif
