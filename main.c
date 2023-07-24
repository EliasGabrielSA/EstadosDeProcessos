#include <stdio.h>
#include <unistd.h>
#include "pnf.h"

void imprimirElementos(Fila *f) {
    ProcessoEncadeado *aux;
    aux = f->ini;
    while(aux != NULL) {
        printf("%s : %f\n", aux->nome, aux->tempo_de_execucao);
        aux = aux->prox;
    }
}

int main() {
    FILE *arq;
    
    char path[100];
    char linha[50];
    
    Fila *pronto = criarFila();
    Fila *espera = criarFila();
    Fila *execucao = criarFila();
    Fila *finalizados = criarFila();
    
    int valorquantum;
    int *pt_valorquantum = &valorquantum;

    scanf("%s", path);
    arq = fopen(path, "rt");

    if (arq == NULL) {
        return -1;
    } 

    fscanf(arq, "%d", pt_valorquantum);
    while(!feof(arq)) {
        if (fgets(linha, 50, arq) != NULL) {
            lerArquivoProcessos(arq, pronto);
        }
    }
    
    //imprimirElementos(pronto);
    printf("valor_quantum : %d\n", valorquantum);
    fclose(arq);
    
    //___________________________________________ 
    
    mudarFila(pronto, execucao);

    while (!filaestavazia(*execucao)) {
        ProcessoEncadeado *aux = desenfileirar(execucao);
        int tempo_restante = aux->tempo_de_execucao;
    
        while (tempo_restante > 0) {
            int tempo_executado = (tempo_restante > valorquantum) ? valorquantum : tempo_restante;
            sleep(tempo_executado);
            tempo_restante -= tempo_executado;
        }
        
        if (tempo_restante > 0) {
            enfileirar(espera, aux->nome, tempo_restante);
        } else {
            enfileirar(finalizados, aux->nome, aux->tempo_de_execucao);
        }
    
        mudarFila(espera, pronto);
        mudarFila(pronto, execucao);
    }
    
    
    imprimirElementos(finalizados);
    
    esvaziarFila(pronto);
    esvaziarFila(execucao);
    esvaziarFila(espera);
    esvaziarFila(finalizados);
    
    
    
    return 0;
}