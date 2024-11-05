#include <stdio.h>
#include <stdlib.h>

#define TAM 101

// struct Node {
//     int val;
//     int numNeighbors;
//     struct Node** neighbors;
// };

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
    if (fila->first == NULL)
    {
        return NULL;
    }

    no *temp =  fila -> first;
    struct Node *aux = temp ->node;
    fila -> first = fila -> first -> prox;
    free(temp);
    return aux;
}

void bfs(struct Node *original, struct Node *clone, struct Node **clones) 
{   
    // Fila para executar a bfs
    q *fila = malloc(sizeof(q)); 
    fila -> first = NULL;
    fila -> last = NULL;

    int *visitados = calloc(TAM, sizeof(int));
    visitados[original -> val] = 1;
    enfileira(fila, original);

    struct Node *aux;
    struct Node *temp;
    while(fila -> first != NULL)
    {
        temp = desenfileira(fila);
        clones[temp->val] ->neighbors = malloc(temp->numNeighbors * sizeof(struct Node*));

        for(int i = 0; i < temp -> numNeighbors; i++)
        {   
            if(!visitados[temp -> neighbors[i] -> val])
            {
                // Clona o no
                aux = malloc(sizeof(struct Node));
                aux -> val = temp -> neighbors[i]-> val;
                aux -> numNeighbors = temp -> neighbors[i] -> numNeighbors;
                aux -> neighbors = malloc(sizeof(struct Node *)* aux -> numNeighbors);
                enfileira(fila, temp -> neighbors[i]);
                visitados[temp -> neighbors[i] -> val] = 1; 
                clones[aux -> val] = aux;
                clones[temp->val] -> neighbors[i] = aux;
            }
            else
            {
                clones[temp->val] -> neighbors[i] = clones[temp -> neighbors[i]-> val];
            }
        }
    }
    free(visitados);
    free(fila);
}

struct Node *cloneGraph(struct Node *s) 
{   
    if (s == NULL)
        return NULL;

    struct Node *clone = malloc(sizeof(struct Node));
    clone -> numNeighbors = s -> numNeighbors;
    clone -> val = s -> val;
    struct Node **clones = malloc(sizeof(struct Node*) * TAM);
    clones[s->val] = clone;

    bfs(s,clone,clones);

    free(clones);
    return clone;
}