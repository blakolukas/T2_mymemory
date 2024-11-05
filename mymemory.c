// implementação
#include "mymemory.h"
#include <stdlib.h>
#include <stdio.h>

unsigned static char memory_pool[1024];
static mymemory_t *memory;

mymemory_t *mymemory_init(size_t size) {
    if (size > 1024) {
        return NULL;
    }

    memory = (mymemory_t *)malloc(sizeof(mymemory_t));
    if (memory == NULL) {
        return NULL;
    }

    memory->pool = memory_pool;
    memory->total_size = size;
    memory->head = NULL;

    printf("pool inicializado em %p, head em %p, e tamanho eh %zu\n\n", memory->pool, memory->head, size);

    return memory;
}

void *mymemory_alloc(mymemory_t *memory, size_t size) {
    if (!memory || size <= 0 || size > memory->total_size) {
        return NULL;
    }

    allocation_t *current = memory->head;
    allocation_t *prev = NULL;
    size_t offset = 0;

    while (current) {
        size_t espaco_livre = (char *)current->start - ((char *)memory->pool + offset);
        if (espaco_livre >= size) {
            break;
        }

        offset = ((char *)current->start + current->size) - (char *)memory->pool;
        prev = current;
        current = current->next;
    }

    if (memory->total_size - offset < size + sizeof(allocation_t)) {
        return NULL;
    }

    allocation_t *new_alloc = (allocation_t *)(memory->pool + offset);
    new_alloc->start = memory->pool + offset + sizeof(allocation_t);
    new_alloc->size = size;
    new_alloc->next = NULL;

    if (prev) {
        prev->next = new_alloc;
    } else {
        memory->head = new_alloc;
    }

    printf("alloc em %p\n\n", new_alloc->start);
    return new_alloc->start;
}

void mymemory_free(mymemory_t *memory, void *ptr) {
    allocation_t *current = memory->head;
    allocation_t *prev = NULL;

    while (current) {
        if (current->start == ptr) {
            if (prev) {
                prev->next = current->next;
            } else {
                memory->head = current->next;
            }
            return;
        }
        prev = current;
        current = current->next;
    }
}

void mymemory_display(mymemory_t *memory) {
    allocation_t *current = memory->head;
    if (!current) {
        printf("Nenhuma alocacao realizada.\n");
        return;
    }

    printf("Alocacoes atuais:\n");
    while (current) {
        printf("Inicio: %p, Tamanho: %zu bytes\n", current->start, current->size);
        current = current->next;
    }
}

void mymemory_stats(mymemory_t *memory) {
    int total_aloc = 0;
    size_t memoria_alocada = 0;
    size_t maior_bloco_livre = 0;
    int fragmentos_livres = 0;

    allocation_t *current = memory->head;
    size_t offset = 0;

    while (current) {
        total_aloc++;
        memoria_alocada += current->size;
        size_t espaco_livre = (char *)current->start - ((char *)memory->pool + offset);
        if (espaco_livre > 0) {
            fragmentos_livres++;
            if (espaco_livre > maior_bloco_livre) {
                maior_bloco_livre = espaco_livre;
            }
        }
        offset = ((char *)current->start + current->size) - (char *)memory->pool;
        current = current->next;
    }

    size_t espaco_livre_final = memory->total_size - offset;
    if (espaco_livre_final > 0) {
        fragmentos_livres++;
        if (espaco_livre_final > maior_bloco_livre) {
            maior_bloco_livre = espaco_livre_final;
        }
    }

    printf("Numero total de alocacoes: %d\n", total_aloc);
    printf("Memoria total alocada: %zu bytes\n", memoria_alocada);
    printf("Memoria total livre: %zu bytes\n", memory->total_size - memoria_alocada);
    printf("Maior bloco contiguo de memoria livre: %zu bytes\n", maior_bloco_livre);
    printf("Numero de fragmentos de memoria livre: %d\n", fragmentos_livres);
}

void mymemory_cleanup(mymemory_t *memory) {
    memory->head = NULL;
    printf("Memoria foi limpa.\n");
}