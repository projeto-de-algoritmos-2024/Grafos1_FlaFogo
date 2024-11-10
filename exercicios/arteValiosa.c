#include <stdio.h>
#include <stdlib.h>

int verifica = 0;

/*void teste(int x, int y, int **mapa)
{   
    printf("     ");
    for(int i = 0; i <= x; i++) printf("%d ", i);
    printf("\n");
    for(int j = y; j >= 0 ; j--)
    {
        printf("%.2d = ",j);
        for(int i = 0; i <= x; i++)
        {
            
            printf("%d ", mapa[i][j]);
        }
        printf("\n");
    }  
}*/

typedef struct node no;
struct node
{
    int coluna_atual;
    int linha_atual;
    no  *prox;
};

typedef struct pilha p;
struct pilha
{
    no *topo;
};


no *criar_no(int coluna, int linha)
{
    no *novo_no = malloc(sizeof(no));
    novo_no -> coluna_atual = coluna;
    novo_no -> linha_atual = linha;
    novo_no -> prox = NULL;
    return novo_no;
}

void empilha_no(p *pilha,int coluna, int linha)
{
    if(pilha -> topo == NULL) pilha -> topo = criar_no(coluna, linha);
    else 
    {
        no *novo_no = criar_no(coluna, linha);
        novo_no -> prox = pilha -> topo;
        pilha -> topo = novo_no;
    }
}

no *desempilha_no(p *pilha)
{
    no *aux = pilha -> topo;
    pilha -> topo = pilha -> topo -> prox;
    aux -> prox = NULL;
    return aux; 
}


void dfs(int mona_linha, int mona_coluna, char** mapa)
{   
    p *pilha = malloc(sizeof(p));
    int atual_linha, atual_coluna;
    empilha_no(pilha, 0, 0);
    no *aux;

    while(pilha -> topo != NULL)
    {
        aux = desempilha_no(pilha);
        atual_coluna = aux ->coluna_atual;
        atual_linha = aux ->linha_atual;
        // Se ja foi visitado retorna
        if(mapa[atual_coluna][atual_linha] == 2) continue ;

        // Se estiver no sensor retorna
        if(mapa[atual_coluna][atual_linha] == 1) continue;
        
        // Se achou a obra
        if(atual_coluna == mona_coluna && atual_linha == mona_linha)
        {
            verifica = 1;
            return;
        }

        // marca como visitado
        mapa[atual_coluna][atual_linha] = 2;

        // anda uma aresta para direita
        int desloca_direita = atual_coluna + 1;
        if(!verifica && desloca_direita <= mona_coluna)
            empilha_no(pilha, desloca_direita, atual_linha);
        
        // anda uma aresta para cima
        int desloca_cima = atual_linha + 1;
        if(!verifica && desloca_cima <= mona_linha)
            empilha_no(pilha, atual_coluna, desloca_cima);
            

        // anda uma aresta para esquerda
        int desloca_esquerda = atual_coluna - 1;
        if(!verifica && desloca_esquerda >= 0)
            empilha_no(pilha, desloca_esquerda, atual_linha);
        
        // anda uma aresta para baixo
        int desloca_baixo = atual_linha -1;
        if(!verifica && desloca_baixo >= 0)
            empilha_no(pilha, atual_coluna, desloca_baixo);
            
    }

    return ;
}

int main()
{

    int cordenada_colunas = 0, cordenada_linhas = 0, qtd_sensores = 0;
    int sensor_colunas = 0, sensor_linhas = 0, sensor_metros = 0;

    char **mapa;

    scanf("%d %d %d", &cordenada_colunas, &cordenada_linhas, &qtd_sensores);

    cordenada_linhas++;
    cordenada_colunas++;
    mapa = calloc(cordenada_colunas, sizeof(char *));
    for (int i = 0; i < cordenada_colunas; i++)
        mapa[i] = calloc(cordenada_linhas, sizeof(char));

    for (int i = 0; i < qtd_sensores; i++)
    {
        scanf("%d %d %d", &sensor_colunas, &sensor_linhas, &sensor_metros);

        int limite_superior = 0, limite_inferior = 0, limite_esquerdo = 0, limite_direito = 0;

        limite_superior = (sensor_linhas + sensor_metros >= cordenada_linhas) 
                            ? cordenada_linhas - 1 : sensor_metros + sensor_linhas;

        limite_inferior = (sensor_linhas - sensor_metros <= 0) 
                            ? 0 :  sensor_linhas - sensor_metros;
        
        limite_esquerdo = (sensor_colunas - sensor_metros <=0) 
                            ? 0 : sensor_colunas - sensor_metros;
                            
        limite_direito = (sensor_colunas + sensor_metros >= cordenada_colunas) 
                            ? cordenada_colunas - 1 
                            : sensor_colunas +sensor_metros;
        
        
        // Pinta esquerda e direita
        for(int i = limite_inferior; i <= limite_superior; i++)
            mapa[sensor_colunas][i] = 1;
        

        // Pinta superior e inferioir
        for(int i = limite_esquerdo; i <= limite_direito; i++)
            mapa[i][sensor_linhas] = 1;
        
    }

    verifica = 0;
    dfs(cordenada_linhas - 1, cordenada_colunas -1, mapa);
    if(verifica) printf("S\n");
    else printf("N\n");

    return 0;
}