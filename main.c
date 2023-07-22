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
    Fila *finalizado = criarFila();
    
    int valorquantum;
    int *pt_valorquantum = &valorquantum;

    scanf("%s", path);
    arq = fopen(path, "rt");

    if (arq == NULL) {
        return -1;
    } 

    while(!feof(arq)) {
        if (fgets(linha, 50, arq) != NULL) {
            lerArquivoProcessos(arq, pronto, &pt_valorquantum);
        }
    }
    
    imprimirElementos(pronto);
    fclose(arq);
    
    printf("%d\n", valorquantum);
    
    
    return 0;
}