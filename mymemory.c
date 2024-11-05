// implementação

#include "mymemory.h"
#include <studio.h>

mymemory_t* mymemory_init(size_t size){
    if(size > 1024){ // 1MB
        return NULL;
    }

    mymemory_t *memory;
    unsigned char memory_pool[1024];

    memory.pool = memory_pool;
    memory.total_size = size;
    memory.head = NULL;

    return &memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size){ //first fit
    if(!memory || size <= 0 || size > memory->total_size){ //verifica
        return NULL;
    }

    allocation_t *current= memory->head; // atual
    allocation_t *prev= NULL; // anterior
    size_t offset = 0; // onde esta o final do bloco

    while(current) {
        // espaço entre o inicio e o fim (memory_pool aponta para o primeiro elemento de pool)
        // compara o final do ultimo bloco colocado com o proximo
        size_t esp= (char*)current->start - ((char*)memory->memory_pool + offset)
        if(esp >= size){
            break; // pq já tem espaço suficiente
        }
        // atualiza o tamanho do deslocamento em relaçao ao ultimo bloco colocado
        offset= (char*)current->start + current->size - (char*)memory_pool;
        prev= current; // atualiza anterior
        current= current->next; // passa para o proximo
    }

    // se o tamanho total - offset 
    if(memory->total_size - offset < size + sizeof(allocation_t)){
        return NULL;
    }




}

void mymemory_free(mymemory_t *memory, void *ptr)
{
    allocation_t *current = memory->head;
    allocation_t *prev = NULL;

    while (current != NULL)
    {
        if (current->start == ptr)
        {
            if (prev == NULL)
            {
                memory->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            memory->total_size -= current->size;
            free(current);
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