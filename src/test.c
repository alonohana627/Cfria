#include "../include/a_stdlib.h"
#include "../include/a_stdio.h"
#include "../include/a_ctype.h"
#include <stdio.h>

int main() {
    A_FILE *fp = a_fopen("test.txt", "w");
    a_putc('a', fp);
    a_putc('b', fp);
    a_putc('c', fp);
    a_putc('d', fp);
    a_putc('e', fp);
    a_putc('f', fp);
    a_putc('g', fp);
    a_putc('h', fp);
    a_putc('i', fp);
    a_putc('j', fp);
    a_putc('k', fp);
    a_putc('l', fp);
    a_putc('m', fp);
    a_putchar('a');
    a_putchar('\n');
	return 0;
}
