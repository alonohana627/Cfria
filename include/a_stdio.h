#ifndef A_STDIO
#define A_STDIO

#define A_NULL ((void*)0)
#define A_EOF (-1)
#define A_BUFSIZE 1024
#define A_OPEN_MAX 20 /*Max files one can open*/
#define A_TRUE 1
#define A_FALSE 0

typedef struct _iobuffer{
    int char_left; /*Characters Left*/
    char *ptr; /*Pointer to the next character*/
    char *base; /*Location of the buffer*/
    int flag; /*Access mode*/
    int fd; /*File descriptor*/
} A_FILE;

extern A_FILE _io_buffer[A_OPEN_MAX];

/* stdin/stdout/stderr is actually a dynamic struct that lets us to ignore the overhead of getting input*/
#define a_stdin (&_io_buffer[0]) 
#define a_stdout (&_io_buffer[1])
#define a_stderr (&_io_buffer[2])

enum a_flags{
    F_READ = 01, /*File opens for reading*/
    F_WRITE = 02, /*File opens for writing*/
    F_UNBUF = 04, /*File is unbuffered*/
    F_EOF = 010, /*End of file*/
    F_ERR = 020 /*Error*/
};

int a_fillbuf(A_FILE *);
int a_flushbuf(int, A_FILE *);

#define a_feof(p) (((p)->flag & F_EOF) != 0)
#define a_ferror(p) (((p)->flag & F_ERR) != 0)
#define a_fileno(p) ((p)->fd)

/*TODO: explain*/
#define a_getc(p) (--(p)->char_left >=0 \
    ? (unsigned char) *(p)->ptr++:a_fillbuf(p))

/*TODO: explain*/
#define a_putc(x,p) (--(p)->char_left>=0\
    ? *(p)->ptr++ = (x) : a_flushbuf((x), p))

#define a_getchar() a_getc(stding)
#define a_putchar(x) a_putc((x), stdout)

/*File IO*/

/*printf, scanf*/
void a_printf(char *fmt, ...);

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

#endif
