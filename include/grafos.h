#if !defined(GRAFOS_H_)
#define GRAFOS_H_

typedef struct vertice
{
    int cor;
    struct vertice** vizinhos;
    int num_vizinhos;
} vertice;

typedef struct grafo
{
    int tamanho;
    int lado;
    int quadrante;
    vertice** vertices;
} grafo;

void ordena(vertice **lista, int tamanho, int (*comparador)(vertice *, vertice *));


vertice **get_vertices_cor(grafo *g, int cor);

grafo* le_grafo(int* vertices, int tamanho);
vertice* get_vertice(grafo* g, int i, int j);
void colore_grafo(grafo *g);
void imprime_grafo(grafo* g);
void imprime_vertice(vertice* v);
void imprime_vizinhos(vertice* v);



#endif // GRAFOS_H_