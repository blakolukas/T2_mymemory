// implementação

#include "mymemory.h"
#include <stdlib.h>
#include <stdio.h>

unsigned static char memory_pool[1024];
static mymemory_t *memory;

mymemory_t* mymemory_init(size_t size) {
    if (size > 1024) { 
        return NULL;
    }

    memory = (mymemory_t*)malloc(sizeof(mymemory_t));
    if (memory == NULL) { 
        return NULL;
    }

    memory->pool = memory_pool;
    memory->total_size = size;
    memory->head = memory->pool;

    printf("pool inicializado em %p, head em %p, e tamanho é %zu\n\n", memory->pool, memory->head, size);

    return memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size){ //first fit

    printf("--------------------------------------\n");

    if(!memory || size <= 0 || size > memory->total_size){ //verifica
        return NULL;
    }

    allocation_t *current= memory->pool;

    printf("current: %p\n", current);

    size_t offset= 0;


    while(current!=memory->head) {
        if(offset>=size){
            break;
        }
        current+= sizeof(allocation_t);
        offset= offset + sizeof(allocation_t);
    }


    allocation_t *new_alloc = (allocation_t*)(memory->head);
    new_alloc->start = memory->head;
    printf("start em: %p\n", new_alloc->start);
    new_alloc->size = size;
    new_alloc->next = new_alloc->start + size;
    printf("next em: %p\n", new_alloc->next);


    memory->head = new_alloc->next;


    printf("alloc em %p\n", new_alloc);

    return new_alloc->start;

}

void mymemory_free(mymemory_t *memory, void *ptr)
{
    allocation_t *current = memory->head;
    allocation_t *prev = NULL;

    while (current != NULL) {
        if (current->start == ptr) {
            if (prev == NULL) {
                memory->head = current->next;
            } else {
                prev->next = current->next;
            }
            memory->total_size -= current->size;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void mymemory_display(mymemory_t *memory)
{
}

void mymemory_stats(mymemory_t *memory)
{
}

void mymemory_cleanup(mymemory_t *memory){
    memory->head = NULL; 
}