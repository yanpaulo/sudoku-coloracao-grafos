#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"

void add_vizinho(vertice *v, vertice *novo)
{
    vizinho *viz = (vizinho *)malloc(sizeof(vizinho));
    viz->vertice = novo;

    if (!v->vizinhos)
    {
        v->vizinhos = viz;
        return;
    }

    vizinho *a = v->vizinhos;
    while (a->proximo)
    {
        a = a->proximo;
    }
    a->proximo = viz;
}

vertice *get_vertice(grafo *g, int i, int j)
{
    return g->vertices[i * g->lado + j];
}

//O(3n)
void define_vizinhos(vertice *v, int linha, int coluna, grafo *g)
{
    //O(n)
    for (int i = 0; i < g->lado; i++)
    {
        if (i != linha)
        {
            vertice *vizinho = get_vertice(g, i, coluna);
            add_vizinho(v, vizinho);
        }
    }

    //O(n)
    for (int j = 0; j < g->lado; j++)
    {
        if (j != coluna)
        {
            vertice *vizinho = get_vertice(g, linha, j);
            add_vizinho(v, vizinho);
        }
    }

    int quadrante_i = (linha / g->quadrante) * g->quadrante;
    int quadrante_j = (coluna / g->quadrante) * g->quadrante;

    //O(n)
    for (int i = quadrante_i; i < quadrante_i + g->quadrante; i++)
    {
        for (int j = quadrante_j; j < quadrante_j + g->quadrante; j++)
        {
            if (i != linha && j != coluna)
            {
                vertice *vizinho = get_vertice(g, i, j);
                add_vizinho(v, vizinho);
            }
        }
    }
}

grafo *le_grafo(int* vertices, int tamanho)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->tamanho = tamanho;
    g->lado = sqrt(g->tamanho);
    g->quadrante = sqrt(g->lado);
    g->vertices = (vertice **)malloc(sizeof(vertice *) * g->tamanho);

    for (int i = 0; i < g->tamanho; i++)
    {
        vertice *v = (vertice *)malloc(sizeof(vertice));
        v->cor = vertices[i];
        g->vertices[i] = v;
    }

    for (int i = 0; i < g->tamanho; i++)
    {
        int linha = i / g->lado, coluna = i % g->lado;
        vertice *v = get_vertice(g, linha, coluna);
        define_vizinhos(v, linha, coluna, g);
    }

    return g;
}

void imprime_vertice(vertice* v)
{
    printf("%d: ", v->cor);
    imprime_vizinhos(v);
}

void imprime_vizinhos(vertice *v)
{
    printf("[");
    vizinho *viz = v->vizinhos;
    while (viz)
    {
        printf(" %d ", viz->vertice->cor);
        viz = viz->proximo;
        if (viz) {
            printf(", ");
        }
    }
    printf("]\n");
}