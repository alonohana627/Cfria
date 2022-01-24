#include "../include/a_stdio.h"
#include <stdio.h>

int main(){
    int *a = (int *)a_malloc(sizeof(int)*10);
    a[0] = 1;
    printf("%d\n", a[0]);
    a_free(a);
    int *b = (int *) a_malloc(sizeof(int)*10);
    printf("%d\n", b[0]);
    return 0;
}
