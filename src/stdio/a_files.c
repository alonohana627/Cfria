#include "../../include/a_stdio.h"
#include "../../include/a_stdlib.h"
#include <fcntl.h>
#include <unistd.h>

A_FILE *a_fopen(const char* name, const char* mode){
	int fd;
	A_FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a'){
		return A_NULL;
    }
	for (fp = _io_buffer; fp < _io_buffer + A_OPEN_MAX; fp++){
		if ((fp->flag & (F_READ | F_WRITE)) == 0){
			break;
        }
    }
	if (fp >= _io_buffer + A_OPEN_MAX){
		return A_NULL;
    }

	if (*mode == 'w'){
		fd = creat(name, PERMS);
    }
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1){
			fd = creat(name, PERMS);
        }
		lseek(fd, 0L, 2);
	} else{
		fd = open(name, O_RDONLY, 0);
    }
	if (fd == -1){
		return A_NULL;
    }
	fp->fd = fd;
	fp->char_left = 0;
	fp->base = A_NULL;
	fp->flag = (*mode == 'r') ? F_READ : F_WRITE;
	return fp;
}

int a_fclose(A_FILE *fp){
    int fd;
    if (fp == A_NULL){
        return A_EOF;
    }
    if (fp->flag & F_WRITE){
        if (a_fflush(fp)){
            return A_EOF;
        }
    }
    fd = fp->fd;
    fp->fd = A_EOF;
    fp->flag = 0;
    return close(fd);
}

int a_rename_file(const char *oldname, const char *newname){
    int fd;
    if ((fd = open(oldname, O_RDONLY, 0)) == A_EOF) { /*syscall*/
        return A_EOF;
    }
    if (link(oldname, newname) == A_EOF) { /*syscall*/
        return A_EOF;
    }
    if (unlink(oldname) == A_EOF) { /*syscall*/
        return A_EOF;
    }
    return close(fd);
}

int a_remove_file(const char *filename){
    return unlink(filename); /*syscall*/
}

int a_new_dir(const char *name){
    return mkdir(name, 0777); /*syscall*/
}

int a_remove_dir(const char *dirname){
    return rmdir(dirname); /*syscall*/
}
