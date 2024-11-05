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
    memory->head = NULL;

    printf("pool inicializado em %p, head em %p, e tamanho é %zu\n\n", memory->pool, memory->head, size);

    return memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size){ //first fit


    if(!memory || size <= 0 || size > memory->total_size){ //verifica
        return NULL;
    }

    allocation_t *current= memory->head; // atual
    printf("current: %p\n", current);
    allocation_t *prev = NULL;
    size_t offset = 0; // onde esta o final do bloco


    while(current) {
        printf("dentro\n");
         // espaço livre entre blocos
        size_t esp= (char*)current->start - ((char*)memory->pool + offset);

        if(esp >= size){
            break; // pq já tem espaço suficiente
        }

        // atualiza o tamanho do deslocamento em relaçao ao ultimo bloco colocado
        offset= (char*)current->start + current->size - (char*)memory->pool;

        prev = current;
        //printf("prev: %p\n", prev);
        current= current->start + current->size; // passa para o proximo

        //printf("current em %p\n", current);
    }

    // se o tamanho total - offset 
    if(memory->total_size - offset < size + sizeof(allocation_t)){
        printf("vish");
        return NULL;
    }


    allocation_t *new_alloc = (allocation_t*)(memory->pool + offset);
    new_alloc->start = (memory->pool + offset);
    printf("\nstart em: %p\n\n", new_alloc->start);
    new_alloc->size = size;
    new_alloc->next = NULL;
    printf("\nnext em: %p\n\n", new_alloc->next);

    if (prev) {
        prev->next = new_alloc;
    } else {
        memory->head = new_alloc;
    }


    printf("alloc em %p\n\n", new_alloc);

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