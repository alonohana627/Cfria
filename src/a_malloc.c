#include "../include/a_stdio.h"
#include <stdio.h>
#include <unistd.h>

/* How does it work:
 * Long takes 8 bytes in the memory. When we have such "header" with size of 8, it also contains a pointer to the next block.
 * The OS and the compiler know how to treat unions, structs, etc. They allocate memory according to the size that the user needs.
 * In our case it will align to 8 bytes. We will not use Align variable.
 * The struct s inside points to the next block, if on the free list.
 * 
 */
typedef long _Align; /*alignment to long boudry*/

union a_header{ /*Block header*/
    struct {
        union a_header *ptr; /*Next block header*/
        unsigned size; /*size of this block*/
    } s;
    _Align x; /*force alignment*/
};

typedef union a_header A_Header; /*Simplify*/

/*Malloc Magic:*/
/* *sbrk(int): a system call to the OS to assign more memory. I will not implement in the library any system calls, it is OS level that are above my current level, but I will use them.
 * *a_morecore(unsigned): Ask the OS for more memory using sbrk.
 */

