#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct Node node;
struct Node
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
        return -1;
    }

    node *temp =  fila -> first;
    int aux = temp -> index ;
    fila -> first = fila -> first -> prox;
    free(temp);
    return aux;
}


bool isBipartite(int** graph, int graphSize, int* graphColSize) 
{   
    // Armazena as camdas e se ja foi visitado, 0 = nao visitado
    int *tiers = calloc(graphSize,sizeof(int));
    int current_tier;
    for(int i = 0; i < graphSize; i++)
    {
        if(tiers[i] != 0 )
            continue;

        tiers[i] = 1;
        q *qu = malloc(sizeof(q));
        qu->first = NULL;
        qu->last = NULL;
        enfileira(qu,i);
        int aux; 
        while(qu -> first != NULL)
        {
            aux = desenfileira(qu);
            current_tier = tiers[aux] ;

            for(int j = 0; j < graphColSize[aux]; j++)
            {   
                if(tiers[graph[aux][j]] == 0)
                {
                    enfileira(qu,graph[aux][j]);
                    tiers[graph[aux][j]] = (current_tier == 1) ? 2 : 1;
                    
                }
                else if(tiers[graph[aux][j]] == current_tier)
                {
                    free(tiers);
                    free(qu);
                    return false;
                }
            }
        }
        free(qu);
    }
    free(tiers);
    return true;
}