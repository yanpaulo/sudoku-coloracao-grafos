#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "grafos.h"

int compara_cor(vertice *v1, vertice *v2)
{
    return v2->cor < v1->cor;
}

int grau_saturado(vertice *v)
{
    int grau = 0;
    vertice** vizinhos = v->vizinhos;
    ordena(v->vizinhos, v->num_vizinhos, compara_cor);
    for (int i = 0; i < v->num_vizinhos; i++)
    {
        vertice *v = vizinhos[0];
        if (i == 0 || vizinhos[i - 1]->cor != v->cor)
        {
            ++grau;
        }
    }

    return grau;
}
int compara_grau_saturado(vertice *v1, vertice *v2)
{
    return grau_saturado(v2) > grau_saturado(v1);
}

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

void ordena_2(vertice **lista, int (*comparador)(vertice *, vertice *))
{
    int tamanho = 0;
    vertice **head = lista;
    while (*lista++)
    {
        ++tamanho;
    }

    ordena(head, tamanho, comparador);
}

vertice *get_vertice(grafo *g, int i, int j)
{
    return g->vertices[i * g->lado + j];
}

//O(3n)
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

    ordena(lista, num_elementos, compara_grau_saturado);

    return lista;
}

int tem_vizinhos_cor(vertice *v, int cor)
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

void colore_grafo(grafo *g)
{
    int num_cor = 0;
    vertice **lista = get_vertices_cor(g, 0);
    do
    {
        vertice *v = *lista;
        while (v)
        {
            if (!tem_vizinhos_cor(v, num_cor))
            {
                v->cor = num_cor;
            }
            v = *(++lista);
        }
        ++num_cor;
        lista = get_vertices_cor(g, 0);
    } while (*lista);

    for (int i = 0; i < g->tamanho; i++)
    {
        g->vertices[i]->cor--;
    }

#ifdef OUTRO_ALGORITMO
    for (int i = 0; i < g->tamanho; i++)
    {
        if (g->vertices[i]->cor)
        {
            continue;
        }

        vertice *item = g->vertices[i];
        ordena(item->vizinhos, item->num_vizinhos, compara_cor);
        imprime_vizinhos(item);
        int cor = 1;
        for (int j = 0; j < item->num_vizinhos; j++)
        {
            vertice *viz = item->vizinhos[j];
            if (cor < viz->cor)
            {
                break;
            }
            cor = item->vizinhos[j]->cor + 1;
        }
        item->cor = cor;
        printf("Pick %d\n", cor);
    }

    for (int i = 0; i < g->tamanho; i++)
    {
        g->vertices[i]->cor--;
    }
#endif
}

void imprime_grafo(grafo *g)
{
    for (int i = 0; i < g->lado; i++)
    {
        for (int j = 0; j < g->lado; j++)
        {
            printf("%d", get_vertice(g, i, j)->cor);
            if (j < g->lado - 1)
            {
                printf(",");
            }
            printf(" ");
        }
        printf("\n");
    }
}