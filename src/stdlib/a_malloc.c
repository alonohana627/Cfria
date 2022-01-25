#include "../../include/a_stdlib.h"

static A_Header base; /*Empty list*/
static A_Header *free_list = A_NULL; /*Free list*/

/*Malloc Magic:*/
/* *sbrk(int): a system call to the OS to assign more memory. 
 *  I will not implement in the library any system calls, it is OS level that are above my current level, but I will use them. 
 *  sbrk can be used without imports
 * *a_morecore(unsigned): Ask the OS for more memory using sbrk.
 * *a_malloc(unsigned): general-purpose storage allocator that throws the memory to the heap.
 * a_free(pointer): free the memory we used (put the block on the free list)
 */

 /*Puts BLK @ the free list*/
void a_free(void *blk){
    A_Header *block_start, *pointer;
    
    block_start = (A_Header *)blk-1; /*Pointer to the block*/

    for(pointer=free_list;
        !(block_start > pointer && block_start < pointer->s.ptr);
        pointer = pointer->s.ptr){ /*Travels on the free list until reaching a free block to insert. */
        if(pointer >= pointer->s.ptr && (block_start>pointer || block_start < pointer->s.ptr)){
            break; /*Free a block at the start or at the end.*/
        }
    }

    /*Try to remember Linked List and you will see amazing equivalence. 
    But it is a little different: here we are merging blocks */
    if(block_start + block_start->s.size == pointer->s.ptr){
        block_start->s.size += pointer->s.ptr->s.size;
        block_start->s.ptr = pointer->s.ptr->s.ptr;
    } else {
        block_start->s.ptr = pointer->s.ptr;
    }

    if(pointer + pointer->s.size == block_start){
        pointer->s.size += block_start->s.size;
        pointer->s.ptr = block_start->s.ptr;
    } else {
        pointer->s.ptr = block_start;
    }

    free_list = pointer;
}

/*Asks for more memory*/
static A_Header *a_morecore(unsigned num){
    char *cp, *sbrk(int);
    A_Header *up;

    if(num<ALLOC_UNITS) {
        num = ALLOC_UNITS; /*Allocates at least ALLOC_UNITS memory*/
    }

    /* sbrk is where the OS allocates our program memory. 
     * How sbrk works?
     * I have now idea. I mean, it is heap, but this kind of things are managed in the kernel level.
     * You can see this implementation: https://github.com/intel/linux-sgx/blob/master/sdk/tlibc/gen/sbrk.c
     * sbrk returns a pointer to the new space.
    */
    cp = sbrk(num*sizeof(A_Header)); 

    if(cp==(char *)-1){ /*Out of space or the OS simply doesn't like us*/
        return A_NULL;
    }

    up = (A_Header*) cp; /*Casts the block into header block*/
    up->s.size = num;

    a_free((void *)(up+1)); /*Adds the new block to our free list*/
    return free_list;
}

/*k&r malloc*/
void *a_malloc(unsigned num){
    A_Header *p, *prevp;
    unsigned nunits;

    nunits = (num + sizeof(A_Header) - 1)/sizeof(A_Header) + 1;

    if((prevp=free_list)==A_NULL) { /*init free list if a freelist doesn't exists*/
        base.s.ptr = free_list = prevp = &base;
        base.s.size = 0;
    }
    for(p = prevp->s.ptr;;prevp=p, p=p->s.ptr){
        if(p->s.size >= nunits){ /*If a block is big enough*/
            if(p->s.size == nunits){
                prevp->s.ptr = p->s.ptr;
            } else { /*Allocates tail end*/
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            free_list = prevp;
            return (void *)(p+1);
        }
        if(p==free_list){
            if((p=a_morecore(nunits))==A_NULL){ /*OS Cannot */
                return A_NULL;
            }
        }
    }
}
