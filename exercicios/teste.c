#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

typedef struct node no;
struct node {
    struct Node *node;
    no *prox;
};

typedef struct Queue q;
struct Queue {
    no *first;
    no *last;
};

void enfileira(q *fila, struct Node *s) {
    no *novo_no = malloc(sizeof(no));
    novo_no->node = s;
    novo_no->prox = NULL;

    if (fila->first == NULL) {
        fila->first = novo_no;
        fila->last = novo_no;
        return;
    }
    
    fila->last->prox = novo_no;
    fila->last = novo_no;
}

struct Node* desenfileira(q *fila) {
    if (fila->first == NULL) {
        return NULL;
    }

    no *temp = fila->first;
    struct Node *aux = temp->node;
    fila->first = fila->first->prox;
    free(temp);
    return aux;
}

void bfs(struct Node *original, struct Node *clone, struct Node **clones, int *visitados) {

    q *fila = malloc(sizeof(q));
    fila->first = NULL;
    fila->last = NULL;

    enfileira(fila, original);
    clones[original->val] = clone;
    visitados[original->val] = 1;

    while (fila->first != NULL) {
        struct Node *temp = desenfileira(fila);
        struct Node *tempClone = clones[temp->val];

        // Allocate neighbors array for tempClone if not done already
        tempClone->neighbors = malloc(temp->numNeighbors * sizeof(struct Node*));

        for (int i = 0; i < temp->numNeighbors; i++) {
            struct Node *neighbor = temp->neighbors[i];

            // Clone the neighbor if it hasn't been cloned yet
            if (!visitados[neighbor->val]) {
                struct Node *neighborClone = malloc(sizeof(struct Node));
                neighborClone->val = neighbor->val;
                neighborClone->numNeighbors = neighbor->numNeighbors;
                clones[neighbor->val] = neighborClone;
                visitados[neighbor->val] = 1;

                // Enqueue the original and cloned neighbors
                enfileira(fila, neighbor);
            }

            // Set the clone's neighbor
            tempClone->neighbors[i] = clones[neighbor->val];
        }
    }

    // Free the queue
    free(fila);
}

struct Node* cloneGraph(struct Node *s) {
    if (s == NULL) {
        return NULL;
    }

    // Allocate memory for tracking clones and visited nodes
    struct Node **clones = calloc(101, sizeof(struct Node*));
    int *visitados = calloc(101, sizeof(int));

    // Create initial clone for the starting node
    struct Node *clone = malloc(sizeof(struct Node));
    clone->val = s->val;
    clone->numNeighbors = s->numNeighbors;

    // Start BFS to clone the graph
    bfs(s, clone, clones, visitados);

    // Free allocated memory for tracking structures
    // free(clones);
    // free(visitados);

    return clone;
}

void ligaNo(struct Node *no1, struct Node *no2)
{   
    no1 -> neighbors[no1 -> numNeighbors] = no2;
    no1 -> numNeighbors++;

    no2 -> neighbors[no2 -> numNeighbors] = no1;
    no2 -> numNeighbors++;
}

void teste(struct Node *no)
{
    for(int i = 0; i < no -> numNeighbors; i++)
    {
        printf("%d ",no -> neighbors[i]-> val);
    }
    printf("\n");
}

int main()
{

    struct Node *no1 = malloc(sizeof(struct Node));
    no1 -> neighbors = malloc(sizeof(struct Node*) * 2);
    no1 -> val = 1;
    no1->numNeighbors = 0;

    struct Node *no2 = malloc(sizeof(struct Node));
    no2 -> neighbors = malloc(sizeof(struct Node*) * 2);
    no2 -> val = 2;
    no2->numNeighbors = 0;

    struct Node *no3 = malloc(sizeof(struct Node));
    no3 -> neighbors = malloc(sizeof(struct Node*) * 2);
    no3 -> val = 3;
    no3->numNeighbors = 0;

    struct Node *no4 = malloc(sizeof(struct Node));
    no4 -> neighbors = malloc(sizeof(struct Node*) * 2);
    no4 -> val = 4;
    no4->numNeighbors = 0;

    ligaNo(no1,no2);
    ligaNo(no1,no4);
    ligaNo(no4,no3);
    ligaNo(no3,no2);

    // teste(no1);
    // teste(no2);
    // teste(no3);
    // teste(no4);

    teste(cloneGraph(no1));

    return 0;
}
