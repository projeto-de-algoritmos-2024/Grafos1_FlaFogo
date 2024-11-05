#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node node;

typedef struct Node
{
    int index;
    node *prox;
};

typedef struct Queue q;
struct Queue
{
    node *first;
    node *last;
};

void enfileira(q *fila, int index)
{
    node *new_node = malloc(sizeof(node));
    new_node -> index = index;
    new_node -> prox = NULL;

    if(fila -> first == NULL)
    {
        fila -> first = new_node;
        fila -> last = new_node;
        return;
    }
    
    fila -> last -> prox = new_node;
    fila -> last = new_node;
}

int desenfileira(q *fila)
{
    if (fila->first == NULL)
    {
        return NULL;
    }

    node *temp =  fila -> first;
    int *aux = temp -> index ;
    fila -> first = fila -> first -> prox;
    free(temp);
    return aux;
}


bool isBipartite(int** graph, int graphSize, int* graphColSize) 
{   
    // Armazena as camdas e se ja foi visitado, 0 = nao visitado
    int *tiers = calloc(graphSize,sizeof(int));
    
    int current_tier = 1;
    q *q = malloc(sizeof(q));
    enfileira(q,0);

    for(int i = 0; i < graphSize; i++)
    {
        if(tiers[i] != 0)
            continue;

        current_tier = 1;
        int aux; 
        while(q -> first != NULL)
        {
            aux = desenfileira(q);
            current_tier = tiers[aux] + 1;

            for(int j = 0; j < graphColSize[aux]; j++)
            {   
                if(!tiers[graph[aux][j]])
                {
                    enfileira(q,j);
                    tiers[j] = current_tier;
                    
                }
                else if(tiers[graph[aux][j]] == current_tier)
                {
                    return false;
                }
            }
        }
    }
    
    return true;
}