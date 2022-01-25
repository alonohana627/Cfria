#ifndef A_STDLIB_H
#define A_STDLIB_H

#define A_NULL ((void*)0)
#define A_TRUE 1
#define A_FALSE 0

/*Memory allocation*/

/* How does it work:
 * Long takes 8 bytes in the memory. When we have such "header" with size of 8, it also contains a pointer to the next block.
 * The OS and the compiler know how to treat unions, structs, etc. They allocate memory according to the size that the user needs.
 * In our case it will align to 8 bytes. We will not use Align variable.
 * The struct s inside points to the next block, if on the free list.
 */
#define ALLOC_UNITS 1024

typedef long _Align; /*alignment to long boudry*/

union a_header{ /*Block header*/
    struct {
        union a_header *ptr; /*Next block header*/
        unsigned size; /*size of this block*/
    } s;
    _Align x; /*force alignment*/
};

typedef union a_header A_Header; /*Simplify*/

void a_free(void*);
void *a_malloc(unsigned);

/*Conversions*/
double a_atof(const char *s); /*Converts s to double*/
int a_atoi(const char *s); /*Converts s to int*/
long a_atol(const char *s); /*Converts s to long*/
double a_strtod(const char *s, char **endp);
long a_strtol(const char *s, char **endp, int base);
unsigned long a_strtoul(const char *s, char **endp, int base);
/*Random((&_io_buffer[i])->flag & F_WRITE)*/

#endif
