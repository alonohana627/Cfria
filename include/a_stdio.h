#ifndef A_STDIO_H
#define A_STDIO_H

#define A_EOF (-1)
#define A_BUFSIZE 1024
#define A_OPEN_MAX 20 /*Max files one can open*/

/* FILE structure in C/UNIX */
typedef struct _iobuffer{
    int char_left;  /*Characters Left*/
    char *ptr;      /*Pointer to the next character*/
    char *base;     /*Location of the buffer*/
    int flag;       /*Access mode*/
    int fd;         /*File descriptor*/
} A_FILE;

extern A_FILE _io_buffer[A_OPEN_MAX];

/* stdin/stdout/stderr is actually a dynamic struct that lets us to ignore the overhead of getting input*/
#define a_stdin (&_io_buffer[0]) 
#define a_stdout (&_io_buffer[1])
#define a_stderr (&_io_buffer[2])

enum a_flags{
    F_READ = 01,    /*File opens for reading*/
    F_WRITE = 02,   /*File opens for writing*/
    F_UNBUF = 04,   /*File is unbuffered*/
    F_EOF = 010,    /*End of file*/
    F_ERR = 020     /*Error*/
};

/*basic buffers*/
/*TODO: explain*/
int a_fillbuf(A_FILE *);
int a_fflush(A_FILE *);
int a_flushbuf(int, A_FILE *);

#define a_feof(p) (((p)->flag & F_EOF) != 0)
#define a_ferror(p) (((p)->flag & F_ERR) != 0)
#define a_fileno(p) ((p)->fd)

/*TODO: explain*/
#define a_getc(p) (--(p)->char_left >= 0 ? (unsigned char) *(p)->ptr++ : a_fillbuf(p))

/*TODO: explain*/
#define a_putc(x,p) a_flushbuf((x), p)

#define a_getchar() a_getc(a_stdin)
#define a_putchar(x) a_putc((x), a_stdout)

/*File IO*/
#define A_SEEK_SET 0
#define A_SEEK_CUR 1
#define A_SEEK_END 2
#define NOT_FOUNE -1
#define PERMS 0666

/*file operations*/
A_FILE *a_fopen(const char* name, const char* mode); /*Will implement r, w, a*/
int a_fclose(A_FILE *fp);
int a_remove_file(const char *filename); /*use syscall*/
int a_rename_file(const char *oldname, const char *newname); /*find&change*/
int a_new_dir(const char *name); /*use syscall*/
int a_remove_dir(const char *dirname); /*use syscall*/

/*File Positioning Functions*/
int a_fseek(A_FILE *stream, long offset, int origin);
long a_ftell(A_FILE *stream);
void a_rewind(A_FILE *stream);

/*printf, scanf*/
int a_fprintf(A_FILE *stream, const char *format, ...);
int a_printf(char *fmt, ...);

#endif
