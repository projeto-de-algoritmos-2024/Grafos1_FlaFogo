#include<stdio.h>
#include <stdlib.h>

typedef struct Node no;
struct Node {
    int num;
    no* prox;
};

typedef struct Item item;
struct Item {
    int num;
    int indice;
};

void inserir_no(no **grafo, int indice, int num)
{   
    no *novo = malloc(sizeof(no));
    novo -> num = num;
    novo -> prox = NULL;

    if(grafo[indice] != NULL)
    {
        novo -> prox = grafo[indice];
    }

    grafo[indice] = novo;
}

void merge(item *vet, int l, int r, int m, int tamanho)
{
    item *vetAux = malloc(sizeof(item) * tamanho);
    int i = l, j = m + 1, indiceAux = 0;

    while(i < m + 1  && j < r + 1)
    {   
        if(vet[i].num > vet[j].num)
            vetAux[indiceAux++] = vet[i++];
        else
            vetAux[indiceAux++] = vet[j++];
    }

    while(i < m + 1)
        vetAux[indiceAux++] = vet[i++];

    while(j < r + 1)
        vetAux[indiceAux++] = vet[j++];

    indiceAux=0;
    while(l < r + 1)
        vet[l++] = vetAux[indiceAux++];
    
    free(vetAux);
}

void mergeSort(item *vet, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;
        mergeSort(vet, l , m);
        mergeSort(vet, m + 1, r);
        merge(vet,l, r, m, (r - l) + 1);
    }
}

void dfs_goodPath()
{

}

int numberOfGoodPaths(int* vals, int valsSize, int** edges, int edgesSize, int* edgesColSize)
{
    no **grafo = malloc(sizeof(no*) * valsSize);

    // Cria grafo
    for(int i = 0; i < edgesSize; i++)
    {
        inserir_no(grafo, edges[i][0], edges[i][1]);
        inserir_no(grafo, edges[i][1], edges[i][0]);
    }

    item *vet_item = malloc(sizeof(item) * valsSize);
    for(int i = 0; i < valsSize; i++)
    {
       vet_item[i].num = vals[i];
       vet_item[i].indice = i;
    }

    mergeSort(vet_item,0, valsSize - 1);

}