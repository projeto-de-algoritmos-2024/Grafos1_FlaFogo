#include <stdio.h>
#include <stdlib.h>

typedef struct Node no;
struct Node {
    int num;
    no* next;
};

typedef struct Queue qu;
struct Queue {
    no *first;
    no *last;
};

void inserir_no(no **grafo, int indice, int num) {   
    no *novo = malloc(sizeof(no));
    novo->num = num;
    novo->next = NULL;

    if(grafo[indice] != NULL) {
        novo->next = grafo[indice];
    }
    grafo[indice] = novo;
}

void inqueue(qu *queue, int num) {
    no *new = malloc(sizeof(no));
    new->num = num;
    new->next = NULL;

    if(queue->first == NULL) {
        queue->first = new;
        queue->last = new;
        return;
    }
    
    queue->last->next = new;
    queue->last = new;
}

int dequeue(qu *queue) {
    if (queue->first == NULL) {
        return -1;  // Retorno -1 para indicar que a fila está vazia
    }

    no *temp = queue->first;
    int num = temp->num; // Armazena o valor do nó
    queue->first = queue->first->next;

    // Se a fila estiver agora vazia, atualize last para NULL
    if (queue->first == NULL) {
        queue->last = NULL;
    }

    free(temp);  // Libera a memória do nó removido
    return num;
}

void print_adj_list(no **grafo, int n) {
    printf("Lista de Adjacência:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d:", i);
        no *temp = grafo[i];
        while (temp != NULL) {
            printf(" -> %d", temp->num);
            temp = temp->next;
        }
        printf("\n");
    }
}

double bfs(no **graph, qu *queue, int t, double *prob, int *visit, int *qtdNeigh, int target, int n) {
    inqueue(queue, 1);
    int control = 0;
    int *auxTiers = calloc(n + 1, sizeof(int));
    int tiers = 1;
    double curretProb = 1.0;
    auxTiers[1] = 1;

    
    while(tiers <= t && queue->first != NULL) {   
        int current = dequeue(queue);
        printf("\nChama: %d \n", current);
        if (current == -1) break;  // Fila vazia

        visit[current] = 1;
        if(qtdNeigh[current] == 0)
            curretProb = 0;
        else
            curretProb = prob[current] / qtdNeigh[current];
        // printf("prob: %lf", curretProb);
        auxTiers[tiers]--;
        auxTiers[tiers + 1] += qtdNeigh[current];

        no *aux = graph[current];
        while(aux != NULL) {   
            
            if(!visit[aux->num] && aux->num == target && (tiers == t || qtdNeigh[aux->num] == 0)) {
                prob[aux->num] = curretProb;
                free(auxTiers);
                printf("\n achou");
                return curretProb;
            }
            if(!visit[aux->num]) {
                printf("%d ",aux->num);
                prob[aux->num] = curretProb;
                inqueue(queue, aux->num);
                visit[aux->num] = 1;
            }
            aux = aux->next;
        }

        if(!auxTiers[tiers]) {
            tiers++;
        }
        printf("\n");
    }
    free(auxTiers); // Libera a memória alocada para auxTiers
    return 0;
}

// int dfs(no **graph, int atual, int **prob, int t, int index_prob, int target)
// {
//     if(t == 0) return 0; 
//     if(graph[atual] -> num == target )
//     {

//     }
// }

double frogPosition(int n, int** edges, int edgesSize, int* edgesColSize, int t, int target) {

    if(t == 1 && target == 1 && edgesSize == 0)
        return 1;
    
    no **graph = malloc(sizeof(no*) * (n + 1));

    for (int i = 0; i <= n; i++) {
        graph[i] = NULL;
    }

    int *qtdNeigh = calloc(n + 1, sizeof(int));

    for(int i = 0; i < edgesSize; i++) {
        inserir_no(graph, edges[i][0], edges[i][1]);
        inserir_no(graph, edges[i][1], edges[i][0]);
        qtdNeigh[edges[i][0]]++;
        qtdNeigh[edges[i][1]]++;
    }

    for(int i = 2; i <= n; i++) {
        qtdNeigh[i]--;
    }

    double *prob = calloc(n + 1, sizeof(double));
    prob[1] = 1;
    int *visit = calloc(n + 1, sizeof(int));

    qu *queue = malloc(sizeof(qu));
    queue->first = NULL;
    queue->last = NULL;

    double answer = bfs(graph, queue, t, prob, visit, qtdNeigh, target, n);
    
    // print_adj_list(graph,n);
    free(visit);
    free(prob);
    free(qtdNeigh);

    for (int i = 0; i <= n; i++) {
        no *temp = graph[i];
        while (temp != NULL) {
            no *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
    free(queue);
    
    return answer;
}