#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

typedef struct node no;
struct node
{
    struct Node *node;
    no *prox;
};

typedef struct Queue q;
struct Queue
{
   no *first;
   no *last;
};

void enfileira(q *fila, struct Node *s)
{
    no *novo_no = malloc(sizeof(no));
    novo_no -> node = s;
    novo_no -> prox = NULL;

    if(fila -> first == NULL)
    {
        fila -> first = novo_no;
        fila -> last = novo_no;
        return;
    }
    
    fila -> last -> prox = novo_no;
    fila -> last = novo_no;

}

struct Node *desenfileira(q *fila)
{

    no *temp =  fila -> first;
    struct Node *aux = temp ->node;
    fila -> first = fila -> first -> prox;
    free(temp);
    return aux;

}

void bfs(struct Node *clone) 
{
    q *fila = malloc(sizeof(q));
    fila -> first = NULL;
    fila -> last = NULL;
    int *visitados = calloc(101, sizeof(int));
    visitados[clone -> val] = 1;
    enfileira(fila, clone);

    struct Node *aux;
    while(fila -> first != NULL)
    {
        clone = desenfileira(fila);
        
        for(int i = 0; i < clone -> numNeighbors; i++)
        {
            if(!visitados[clone -> neighbors[i] -> val])
            {
                enfileira(fila, clone -> neighbors[i]);
                visitados[clone -> neighbors[i] -> val] = 1; 
            }
            
            struct Node *aux = malloc(sizeof(struct Node));
            aux -> val = aux -> neighbors[i]->val;
            aux -> numNeighbors = aux -> numNeighbors;
            clone -> neighbors[i] = aux;
        }
    }

    
}


struct Node *cloneGraph(struct Node *s) 
{
    struct Node *clone = malloc(sizeof(struct Node));
    clone -> numNeighbors = s -> numNeighbors;
    clone -> neighbors = malloc(sizeof(struct Node*) * s ->numNeighbors);

    bfs(clone);

    return clone;

}
