//implementação

#include "mymemory.h"
#include <studio.h>

mymemory_t* mymemory_init(size_t size){
    mymemory_t *memory;
    unsigned char memory_pool= [size*size];

    memory.pool= memory_pool;
    memory.total_size= size;
    memory.head= NULL;

    return &memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size){ //first fit
    if(!memory || size <= 0){
        return NULL;
    }
    allocation_t *current= memory->head;
    allocation_t *prev= NULL;
    size_t count = 0;

    while(current){
        size_t gap = (size_t)((char*)current->start - (char*)memory->pool - count);
        if (gap >= size) {
            break;
        }
        count = (size_t)((char*)current->start - (char*)memory->pool) + current->size;
        previous = current;
        current = current->next;
    }

    if (memory->total_size - count < size) {
        return NULL;
    }

    // Aloca o bloco e cria uma nova entrada na lista de alocações
    allocation_t *new_allocation = (allocation_t*)(memory->pool + count);
    new_allocation->start = (void*)(memory->pool + count);
    new_allocation->size = size;
    new_allocation->next = current;

    if (previous) {
        previous->next = new_allocation;
    } else {
        memory->head = new_allocation;
    }

    return new_allocation->start;


}
void mymemory_free(mymemory_t *memory, void *ptr){

}

void mymemory_display(mymemory_t *memory){

}

void mymemory_stats(mymemory_t *memory){

}

void mymemory_cleanup(mymemory_t *memory){

}