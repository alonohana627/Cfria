#include "../include/a_stdlib.h"
#include "../include/a_stdio.h"
#include "../include/a_ctype.h"
#include <stdio.h>

int main(){
    printf("hey\n");
    int a = a_isgraph('!');
    char z = a_toupper('z');
    printf("%d\n",a);
    printf("%c\n",z);
    int k = a_putc('a', a_stdout);
    k = a_putc('a', a_stdout);
    k = a_putc('a', a_stdout);
    k = a_putc('a', a_stdout);
    a_putc('a', a_stdout);
    return 0;
}
