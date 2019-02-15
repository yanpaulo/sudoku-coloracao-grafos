#include <stdlib.h>
#include "grafos.h"

#pragma region Ordenação

int compara_cor(vertice *v1, vertice *v2);
int conta_vizinhos_coloridos(vertice* v);
void ordena(vertice **lista, int tamanho, int (*comparador)(vertice *, vertice *));

//Retorna o grau de saturação do vértice v
int grau_saturacao(vertice *v)
{
    int grau = 0;
    vertice **vizinhos = v->vizinhos;
    ordena(vizinhos, v->num_vizinhos, compara_cor);
    for (int i = 0; i < v->num_vizinhos; i++)
    {
        vertice *v = vizinhos[i];
        if (v->cor && (i == 0 || vizinhos[i - 1]->cor != v->cor))
        {
            ++grau;
        }
    }

    return grau;
}

//Retorna 1 se o grau de saturação de v2 for maior que o de v1
int compara_grau_saturacao(vertice *v1, vertice *v2)
{
    int g1 = grau_saturacao(v1),
        g2 = grau_saturacao(v2);
    if (g1 != g2)
    {
        return g2 > g1;
    }
    return conta_vizinhos_coloridos(v2) > conta_vizinhos_coloridos(v1);
}

//Retorna 1 se a cor de v2 for menor que a cor de v1
int compara_cor(vertice *v1, vertice *v2)
{
    return v2->cor < v1->cor;
}

//Ordena a lista de tamanho especificado utilizando a função de comparação especificada
void ordena(vertice **lista, int tamanho, int (*comparador)(vertice *, vertice *))
{
    for (int i = 0; i < tamanho; i++)
    {
        vertice *a = lista[i];
        for (int j = i + 1; j < tamanho; j++)
        {
            vertice *b = lista[j];
            if (comparador(a, b))
            {
                lista[i] = b;
                lista[j] = a;
                a = b;
            }
        }
    }
}

#pragma endregion

#pragma region Operações de Cor

//Retorna os vértices do grafo com a cor especificada,
//ordenados por grau de saturação
vertice **get_vertices_cor(grafo *g, int cor)
{
    vertice **lista = (vertice **)calloc(g->tamanho, sizeof(vertice *) + 1);
    int num_elementos = 0;
    for (int i = 0; i < g->tamanho; i++)
    {
        vertice *elemento = g->vertices[i];
        if (elemento->cor == cor)
        {
            lista[num_elementos++] = elemento;
        }
    }
    lista = realloc(lista, sizeof(vertice *) * num_elementos + 1);
    ordena(lista, num_elementos, compara_grau_saturacao);

    return lista;
}

int conta_vizinhos_coloridos(vertice* v)
{
    int num = 0;
    for(int i = 0; i < v->num_vizinhos; i++)
    {
        vertice* vizinho = v->vizinhos[i];
        if (vizinho->cor) {
            ++num;
        }
    }
    return num;
}

//Retorna os vizinhos de cor igual à especificada
int tem_vizinhos_cor_igual(vertice *v, int cor)
{
    for (int i = 0; i < v->num_vizinhos; i++)
    {
        if (v->vizinhos[i]->cor == cor)
        {
            return 1;
        }
    }
    return 0;
}

//Retorna a menor cor válida para o vértice v
int menor_cor(vertice *v)
{
    int num_cor;
    for (num_cor = 1; tem_vizinhos_cor_igual(v, num_cor); ++num_cor)
        ;
    return num_cor;
}

#pragma endregion

#pragma region Algoritmo
//Resolve as cores do grafo utilizando o algoritmo de Welsh–Powell
//com ordenação por grau de saturação
void resolve_grafo(grafo *g)
{
    vertice **lista = get_vertices_cor(g, 0);
    do
    {
        vertice *v = *lista;
        int num_cor = menor_cor(v);
        ++lista;
        while (v)
        {
            if (!tem_vizinhos_cor_igual(v, num_cor))
            {
                v->cor = num_cor;
            }

            v = *++lista;
        }
        lista = get_vertices_cor(g, 0);
    } while (*lista);

}

#pragma endregion