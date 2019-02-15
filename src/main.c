#include <stdio.h>
#include "algoritmo.h"

int main(int argc, char** argv) {
    int* map;
    int tamanho;

    if (argc > 1)
    {
        map = le_arquivo(argv[1]);
        for(tamanho = 0; map[tamanho] >= 0; tamanho++);
    }
    else
    {
        int matriz[] = 
        {
        0, 2, 0, 5, 0, 1, 0, 9, 0,
        8, 0, 0, 2, 0, 3, 0, 0, 6,
        0, 3, 0, 0, 6, 0, 0, 7, 0,
        0, 0, 1, 0, 0, 0, 6, 0, 0,
        5, 4, 0, 0, 0, 0, 0, 1, 9,
        0, 0, 2, 0, 0, 0, 7, 0, 0,
        0, 9, 0, 0, 3, 0, 0, 8, 0,
        2, 0, 0, 8, 0, 4, 0, 0, 7,
        0, 1, 0, 9, 0, 7, 0, 6, 0
        };
        map = matriz;
        tamanho = sizeof(matriz) / sizeof(int);
    }
    
    grafo* g = le_grafo(map, tamanho);
    printf("---------------\n");
    imprime_grafo(g);
    printf("---------------\n");
    resolve_grafo(g);
    imprime_grafo(g);
}