#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafos.h"

int compara_cor(vertice *v1, vertice *v2);

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

int compara_grau_saturacao(vertice *v1, vertice *v2)
{
    return grau_saturacao(v2) > grau_saturacao(v1);
}

int compara_cor(vertice *v1, vertice *v2)
{
    return v2->cor < v1->cor;
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

vertice **vizinhos_cor_diferente(vertice *v, int cor)
{
    int num = 0;
    vertice **list = calloc(v->num_vizinhos, sizeof(vertice *) + 1);
    for (int i = 0; i < v->num_vizinhos; i++)
    {
        vertice *vizinho = v->vizinhos[i];
        if (vizinho->cor != cor)
        {
            list[num++] = vizinho;
        }
    }
    ordena(list, num, compara_cor);
    return list;
}

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

int menor_cor(vertice **list)
{
    int cor = 1;
    while (1)
    {
        vertice **head = list;
        while (*head)
        {
            vertice *item = *head;
            vertice *proximo = *(head + 1);
            if (item->cor == cor)
            {
                break;
            }
            else if (!proximo || proximo->cor > cor)
            {
                return cor;
            }
            ++head;
        }
        ++cor;
    }
}

int is_vizinho(vertice *v1, vertice *v2)
{
    for (int i = 0; i < v1->num_vizinhos; i++)
    {
        if (v1->vizinhos[i] == v2)
        {
            return 1;
        }
    }
    return 0;
}

void colore_grafo(grafo *g)
{
    vertice **lista = get_vertices_cor(g, 0);

    while (*lista)
    {
        vertice *v = *lista;
        int num_cor = 1;
        for(num_cor = 1; tem_vizinhos_cor_igual(v, num_cor); ++num_cor);
        v->cor = num_cor;
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
    }
}

#pragma region Grafos

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

#pragma endregion