#include <stdio.h>
#include "grafos.h"

int main() {
    int map[] = {
        0, 0, 2, 3,
        0, 1, 0, 0,
        8, 9, 4, 5,
        0, 0, 0, 0
    };
    grafo* g = le_grafo(map, sizeof(map) / sizeof(int));
    vertice* v = get_vertice(g, 1, 2);
    imprime_vertice(v);
}