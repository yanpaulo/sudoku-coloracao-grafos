#include <stdio.h>
#include "grafos.h"

int main() {
    int map[] = {
        0, 2, 0, 5, 0, 1, 0, 9, 0,
        8, 0, 0, 2, 0, 3, 2, 0, 6,
        0, 3, 0, 0, 6, 0, 0, 7, 0,
        0, 0, 1, 0, 0, 0, 6, 0, 0,
        5, 4, 0, 0, 0, 0, 0, 1, 9,
        0, 0, 2, 0, 0, 0, 7, 0, 0,
        0, 9, 0, 0, 3, 0, 0, 8, 0,
        2, 0, 0, 8, 0, 4, 0, 0, 7,
        0, 1, 0, 9, 0, 7, 0, 6, 0
    };
    grafo* g = le_grafo(map, sizeof(map) / sizeof(int));
    printf("---------------\n");
    imprime_grafo(g);
    printf("---------------\n");
    colore_grafo(g);
    imprime_grafo(g);
}