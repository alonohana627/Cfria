#include "../../include/a_stdio.h"
#include "../../include/a_stdlib.h"
#include <sys/types.h>
#include <unistd.h> /*for syscalls*/
#include <stdio.h>

A_FILE _io_buffer[A_OPEN_MAX] = {
    {0, (char *) 0, (char *) 0 ,F_READ, 0},
    {0, (char *) 0, (char *) 0 ,F_WRITE, 1},
    {0, (char *) 0, (char *) 0 ,F_WRITE | F_UNBUF, 2},
};
/*
 Buffers are the source for the rest of the IO components.
 We abstract them to the user, so the user won't have to deal with syscalls.
*/
int a_fillbuf(A_FILE *fp){
    int bufsize;

    if((fp->flag&(F_READ|F_EOF|F_ERR)) != F_READ){
        return A_EOF;
    }
    bufsize = (fp->flag & F_UNBUF)?1:A_BUFSIZE;
    if(fp->base == A_NULL){ /*Buffer not exists yet*/
        if((fp->base=(char*)a_malloc(bufsize))==A_NULL){
            return A_EOF; /*Can't get to buffer*/
        }
    }
    
    fp->ptr = fp->base;
    fp->char_left = read(fp->fd, fp->ptr, bufsize); /*syscall*/

    if(--fp->char_left<0){
        if(--fp->char_left==-1){
        fp->flag|=F_EOF;
        } else {
            fp->flag |= F_ERR;
        }

        fp->char_left = 0;
        return A_EOF;
    }

    return (unsigned char) *fp->ptr++;
}

int a_flushbuf(int c, A_FILE *fp) {
    if (fp == NULL ){ /*Bad pointer*/
        return EOF;
    }
    else if (a_fflush(fp) == EOF) {/*fflush problem*/
        return EOF;
    }
    *fp->ptr++ = (char) c;
    fp->char_left--;
    return a_fflush(fp);
}

int a_fflush(A_FILE *fp) {
    int i;
    if (fp == NULL) {
        int result = 0;
        for (i = 0; i < A_OPEN_MAX; i++) {
            if (((&_io_buffer[i])->flag & F_WRITE) == F_WRITE && a_fflush(&_io_buffer[i]) == EOF){
                result = A_EOF;
            }
        }
        return result;
    }
    else if (fp < _io_buffer || fp >= _io_buffer + A_OPEN_MAX){
        return A_EOF;
    }
    else if ((fp->flag & (F_WRITE | F_ERR | F_READ)) != F_WRITE){
        return A_EOF;
    }

    int bufsize = (fp->flag & F_UNBUF) ? 1 : A_BUFSIZE;

    if (fp->base == NULL) {
        if ((fp->base = (char *) a_malloc(bufsize)) == NULL) {
            fp->flag |= F_ERR;
            return A_EOF;
        }
    }
    else {
        int n = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= F_ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->char_left = bufsize;
    return 0;
}
