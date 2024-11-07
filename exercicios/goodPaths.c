#include<stdio.h>
#include <stdlib.h>

typedef struct Node no;
struct Node {
    int num;
    no* prox;
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

void dfs(no ** graph, int index_begin, int *paths, int num_limit, int *vals, int *analyzed, int *visitors)
{   
    if(graph[index_begin] != NULL )
    {
        no *current = graph[index_begin];
        visitors[index_begin] = 1;

        while(current != NULL && !visitors[graph[index_begin] -> num])
        {   
            printf("%d ", current -> num);    
            if(vals[current -> num] == num_limit)
            {   
                if(!analyzed[current -> num])
                    (*paths)++;
                
                dfs(graph, current -> num, paths, num_limit, vals, analyzed, visitors);
            }
            else if(vals[current -> num ] < num_limit)
            {
                
                dfs(graph, current -> num, paths, num_limit, vals, analyzed, visitors);                
            }
            current = current -> prox;
            
        }
    }
}

int numberOfGoodPaths(int* vals, int valsSize, int edges[][2], int edgesSize, int* edgesColSize)
{
    no **graph = malloc(sizeof(no*) * valsSize);

    // Cria o grafo
    for(int i = 0; i < edgesSize; i++)
    {
        inserir_no(graph, edges[i][0], edges[i][1]);
        inserir_no(graph, edges[i][1], edges[i][0]);
    }

    int *analyzed = calloc(valsSize, sizeof(int));
    int *paths = malloc(sizeof(int));
    *paths = 0;

    for(int i = 0; i < valsSize ; i++)
    {   
        int *visitors = calloc(valsSize, sizeof(int));
        printf("\n");
        dfs(graph,i, paths, vals[i], vals, analyzed, visitors);
        analyzed[i] = 1;
        free(visitors);
    }

    return (*paths) + valsSize;
}

int main()
{
    int *num = malloc(sizeof(int));
    *num = 2;
    int vals[] = {1,3,2,1,3};
    int edges[][2] = {{0,1},{0,2},{2,3},{2,4}};

    int numero = numberOfGoodPaths(vals,5,edges,4,num);
    printf("\n%d\n",numero);
}