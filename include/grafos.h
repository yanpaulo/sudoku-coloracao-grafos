#if !defined(GRAFOS_H_)
#define GRAFOS_H_
/* Estruturas e funções para a leitura de grafos para o problema de Sudoku */

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


/* Operações de grafo */

//Lê um mapa a partir do arquivo especificado
int* le_arquivo(char* filename);

//Lê o grafo a partir da lista unidimentional com tamanho especificado.
//O tamanho deve ter raíz quadrada inteira
grafo* le_grafo(int* vertices, int tamanho);

//Imprime o grafo g bem bonitinho
void imprime_grafo(grafo* g);


/* Operações de vértice */


//Retorna o vértice i,j do grafo g
vertice* get_vertice(grafo* g, int i, int j);
//Imprime o vértico especificado (com vizinhos)
void imprime_vertice(vertice* v);
//Imprime os vizinhos do vértice especificado
void imprime_vizinhos(vertice* v);

#endif // GRAFOS_H_