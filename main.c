#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

int main()
{
    mymemory_t *memory = mymemory_init(1000);

    // 100 bytes
    int *v = mymemory_alloc(memory, 100);
    for (int i = 0; i < 25; i++){
        v[i] = i + 1;
    } // Preenchemos ate o limite dos 100 bytes

    // Exibe o status apos a primeira alocacao
    printf("\nEstado da memoria apos alocar 'v':\n");
    mymemory_display(memory);
    mymemory_stats(memory);

    // bloco de memoria para um vetor de 16 inteiros
    int *v2 = mymemory_alloc(memory, sizeof(int) * 16);
    if (v2 != NULL)
    {
        for (int i = 0; i < 16; i++)
            v2[i] = (i + 1) * 2;
    }
    else
    {
        printf("Falha na alocacao de memoria para 'v2'.\n");
    }

    printf("\nEstado da memoria apos alocar 'v2':\n");
    mymemory_display(memory);
    mymemory_stats(memory);

    mymemory_free(memory, v);
    printf("\nEstado da memoria apos liberar 'v':\n");
    mymemory_display(memory);
    mymemory_stats(memory);

    char *str = mymemory_alloc(memory, sizeof(char) * 16);
    if (str != NULL)
    {
        sprintf(str, "ola mundo");
        printf("\nConteudo de 'str': %s\n", str);
    }
    else
    {
        printf("Falha na alocacao de memoria para 'str'.\n");
    }

    printf("\nEstado da memoria apos alocar 'str':\n");
    mymemory_display(memory);
    mymemory_stats(memory);

    mymemory_cleanup(memory);
    printf("\nEstado da memoria apos limpeza completa:\n");
    mymemory_display(memory);
    mymemory_stats(memory);

    free(memory);

    return 0;
}