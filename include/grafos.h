#if !defined(GRAFOS_H_)
#define GRAFOS_H_
//Estruturas e funções para a leitura de grafos para o problema de Sudoku

//Vértice de um grafo
typedef struct vertice
{
    int cor;
    struct vertice** vizinhos;
    int num_vizinhos;
} vertice;

//Representação de um grafo para o problema de Sudoku
typedef struct grafo
{
    int lado;
    int tamanho;
    int quadrante;
    vertice** vertices;
} grafo;


//Operações de grafo
grafo* le_grafo(int* vertices, int tamanho);
void imprime_grafo(grafo* g);


//Operações de vértice

vertice* get_vertice(grafo* g, int i, int j);
void imprime_vertice(vertice* v);
void imprime_vizinhos(vertice* v);

#endif // GRAFOS_H_