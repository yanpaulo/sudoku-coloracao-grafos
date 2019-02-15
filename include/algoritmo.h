#if !defined(ALGORITMO_H_)
#define ALGORITMO_H_
#include "grafos.h"
/* Funções para a resolução do problema de Sudoku */

//Resolve as cores do grafo utilizando o algoritmo de Welsh–Powell
//com ordenação por grau de saturação
void resolve_grafo(grafo *g);

#endif // ALGORITMO_H_
