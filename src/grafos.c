#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"

//Define os vizinhos do vértice v - O(3n)
void define_vizinhos(vertice *v, int linha, int coluna, grafo *g)
{
    v->vizinhos = calloc(sizeof(vertice **), (g->lado - 1) * 3);

    //O(n)
    for (int i = 0; i < g->lado; i++)
    {
        if (i != linha)
        {
            vertice *vizinho = get_vertice(g, i, coluna);
            v->vizinhos[v->num_vizinhos++] = vizinho;
        }
    }

    //O(n)
    for (int j = 0; j < g->lado; j++)
    {
        if (j != coluna)
        {
            vertice *vizinho = get_vertice(g, linha, j);
            v->vizinhos[v->num_vizinhos++] = vizinho;
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
                v->vizinhos[v->num_vizinhos++] = vizinho;
            }
        }
    }
}

vertice *get_vertice(grafo *g, int i, int j)
{
    return g->vertices[i * g->lado + j];
}

grafo *le_grafo(int *vertices, int tamanho)
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

void imprime_vertice(vertice *v)
{
    printf("%d: ", v->cor);
    imprime_vizinhos(v);
}

void imprime_vizinhos(vertice *v)
{
    printf("[");
    for (int i = 0; i < v->num_vizinhos; i++)
    {
        vertice *viz = v->vizinhos[i];
        printf(" %d ", viz->cor);
        if (i < v->num_vizinhos - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void imprime_grafo(grafo *g)
{
    for (int i = 0; i < g->lado; i++)
    {
        for (int j = 0; j < g->lado; j++)
        {
            printf("%2d", get_vertice(g, i, j)->cor);
            if (j < g->lado - 1)
            {
                printf(",");
            }
            printf(" ");
        }
        printf("\n");
    }
}

int* le_arquivo(char* filename)
{
    FILE* f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int* buffer = calloc(size, sizeof(int));
    size = 0;

    while(!feof(f)){
        int n;
        fscanf(f, "%d", &n);
        buffer[size++] = n;
    }
    buffer[size] = -1;
    buffer = realloc(buffer, size * sizeof(int) + 1);

    return buffer;
}