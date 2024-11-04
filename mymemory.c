//implementação

#include "mymemory.h"
#include <studio.h>

mymemory_t* mymemory_init(size_t size){
    if(size > 1024){
        return NULL;
    }

    mymemory_t *memory;
    unsigned char memory_pool[1024];

    memory.pool= memory_pool;
    memory.total_size= size;
    memory.head= NULL;

    return &memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size){ //first fit
    if(!memory || size <= 0 || size > memory->total_size){
        return NULL;
    }

    allocation_t *current= memory->head;
    allocation_t *prev= NULL;
    size_t count = 0;

    while(current) {
        size_t disp= (char*)current->start - ((char*)memory->memory_pool + count)
        if(disp >= size){
            break;
        }
        count= (char*)current->start + current->size - (char*)memory_pool;
        prev= current;
        current= current->next;
    }
    

}

void mymemory_free(mymemory_t *memory, void *ptr){

}

void mymemory_display(mymemory_t *memory){

}

void mymemory_stats(mymemory_t *memory){

}

void mymemory_cleanup(mymemory_t *memory){

}