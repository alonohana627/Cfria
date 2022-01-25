#include "../../include/a_stdio.h"
#include "../../include/a_stdlib.h"
#include <unistd.h>

int a_fseek(A_FILE *stream, long offset, int origin){
    
    int result;

    if ((stream->flag & F_UNBUF) == 0 && stream->base != NULL) {
        /* deal with buffering */
        if (stream->flag & F_WRITE) {
            if (a_fflush(stream)){
                return A_EOF;
            }
        } else if (stream->flag & F_READ) {
            if (origin == A_SEEK_CUR) {
                if (offset >= 0 && offset <= stream->char_left) {
                    stream->char_left -= offset;
                    stream->ptr += offset;
                    stream->flag &= ~F_EOF;
                    return 0;
                } else{
                    offset -= stream->char_left;
                }
            }
            stream->char_left = 0;
            stream->ptr = stream->base;
        }
    }
    result = (lseek(stream->fd, offset, origin) < 0); /*syscall*/
    if (result == 0) {
        stream->flag &= ~F_EOF; 
    }
    return result;
}
