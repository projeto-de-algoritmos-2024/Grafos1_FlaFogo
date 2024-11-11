#include <stdio.h>
#include <stdlib.h>
   
typedef struct Node no;
struct Node {
    int num;
    no* next;
};

typedef struct Queue qu;
struct Queue
{
    no *first;
    no *last;
};

void inserir_no(no **grafo, int indice, int num)
{   
    no *novo = malloc(sizeof(no));
    novo -> num = num;
    novo -> next = NULL;

    if(grafo[indice] != NULL)
    {
        novo -> next = grafo[indice];
    }

    grafo[indice] = novo;
}

void inqueue (qu *queue, int num)
{
    no *new = malloc(sizeof(no));
    new -> num = num;
    new -> next = NULL;

    if(queue -> first == NULL)
    {
        queue -> first = new;
        queue -> last = new;
        return;
    }
    
    queue -> last -> next = new;
    queue -> last = new;
}

no * dequeue (qu *queue)
{
    if (queue->first == NULL)
    {
        return -1;
    }

    no *temp =  queue -> first;
    no* aux = temp;
    queue -> first = queue -> first -> next;
    free(temp);
    return aux; 
}

#include <stdio.h>
#include <stdlib.h>
   
typedef struct Node no;
struct Node {
    int num;
    no* next;
};

typedef struct Queue qu;
struct Queue
{
    no *first;
    no *last;
};

void inserir_no(no **grafo, int indice, int num)
{   
    no *novo = malloc(sizeof(no));
    novo -> num = num;
    novo -> next = NULL;

    if(grafo[indice] != NULL)
    {
        novo -> next = grafo[indice];
    }

    grafo[indice] = novo;
}

void inqueue (qu *queue, int num)
{
    no *new = malloc(sizeof(no));
    new -> num = num;
    new -> next = NULL;

    if(queue -> first == NULL)
    {
        queue -> first = new;
        queue -> last = new;
        return;
    }
    
    queue -> last -> next = new;
    queue -> last = new;
}

no * dequeue (qu *queue)
{
    if (queue->first == NULL)
    {
        return -1;
    }

    no *temp =  queue -> first;
    no* aux = temp;
    queue -> first = queue -> first -> next;
    free(temp);
    return aux; 
}

void bfs(no **graph, qu *queue, int t, int *prob, int *visit, int * qtdNeigh, int target, int n)
{   
    
    inqueue(queue, 1);
    int control = 0;

    int *auxTiers = calloc(n + 1, sizeof(int));

    int tiers = 1;
    int curretProb = 1;
    auxTiers[1] = qtdNeigh[1];

    while(tiers <= t && queue -> first != NULL)
    {   
        no * current = dequeue(queue);
        visit[current -> num] = 1;
        no *aux = current;
        curretProb = prob[current -> num]/qtdNeigh[current -> num];

        // Subtrai da cama que eu estou
        auxTiers[tiers]--;

        // Soma na proxima camada
        auxTiers[tiers + 1] = qtdNeigh[current -> num];

        while(aux != NULL)
        {   
            if(aux -> num == target)
            {
                // finded = 1;
                prob[aux -> num] = curretProb;
                return;
            }
            if(!visit[aux -> num])
            {
                prob[aux -> num] = curretProb;
                inqueue(queue, aux -> num);
                visit[aux -> num] = 1;
            }
            aux = aux -> next;
        }

        if(!auxTiers[tiers]) tiers++;
    }
}

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    
    no **graph = malloc(sizeof(no*) * (n + 1));

    for (int i = 0; i < n + 1; i++)
    {
        graph[i] = NULL;  // Inicializa todas as posições com NULL
    }

    // Quantidade de filhos para cada no
    int * qtdNeigh = calloc( n + 1, sizeof(int));

    // Cria o grafo
    for(int i = 0; i < edgesSize; i++)
    {
        inserir_no(graph, edges[i][0], edges[i][1]);
        inserir_no(graph, edges[i][1], edges[i][0]);

        qtdNeigh[edges[i][0]]++;
        qtdNeigh[edges[i][1]]++;
        
    }

    // Para não contar o pai
    for(int i = 2; i < n + 1; i++)
    {
        qtdNeigh[i]--;
    }

    // Vetor das probabilidades
    double *prob = calloc(n + 1, sizeof(double));
    prob[1] = 1;
    
    // Vetor de visitados
    int *visit = calloc(n + 1, sizeof(int));

    qu *queue = malloc(sizeof(qu));
    queue -> first == NULL;
    queue -> last == NULL;

    bfs(edges, queue, t, prob, visit, qtdNeigh, target,n);
    int answer = prob[target];

    free(visit);
    free(prob);
    return target;
}

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {
    
    no **graph = malloc(sizeof(no*) * (n + 1));

    for (int i = 0; i < n + 1; i++)
    {
        graph[i] = NULL;  // Inicializa todas as posições com NULL
    }

    // Quantidade de filhos para cada no
    int * qtdNeigh = calloc( n + 1, sizeof(int));

    // Cria o grafo
    for(int i = 0; i < edgesSize; i++)
    {
        inserir_no(graph, edges[i][0], edges[i][1]);
        inserir_no(graph, edges[i][1], edges[i][0]);

        qtdNeigh[edges[i][0]]++;
        qtdNeigh[edges[i][1]]++;
        
    }

    // Para não contar o pai
    for(int i = 2; i < n + 1; i++)
    {
        qtdNeigh[i]--;
    }

    // Vetor das probabilidades
    double *prob = calloc(n + 1, sizeof(double));
    prob[1] = 1;
    
    // Vetor de visitados
    int *visit = calloc(n + 1, sizeof(int));

    qu *queue = malloc(sizeof(qu));
    queue -> first == NULL;
    queue -> last == NULL;

    bfs(edges, queue, t, prob, visit, qtdNeigh, target,n);
    int answer = prob[target];

    free(visit);
    free(prob);
    return target;