#include <stdio.h>
#include "main.h"

int main() {
    int num = 42;


    _printf("Without precision: %d\n", num);
    _printf("With precision 5: %+.5d\n", num);
    _printf("With precision 8: %.8d\n", num);

    return 0;
}

