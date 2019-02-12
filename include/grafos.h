#if !defined(GRAFOS_H_)
#define GRAFOS_H_
typedef struct vizinho
{
    struct vertice* vertice;
    struct vizinho* proximo;
} vizinho;


typedef struct vertice
{
    int cor;
    vizinho* vizinhos;
} vertice;

typedef struct grafo
{
    int tamanho;
    int lado;
    int quadrante;
    vertice** vertices;
} grafo;

grafo* le_grafo(int* vertices, int tamanho);
vertice* get_vertice(grafo* g, int i, int j);
void imprime_vertice(vertice* v);
void imprime_vizinhos(vertice* v);

#endif // GRAFOS_H_