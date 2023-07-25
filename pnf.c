#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnf.h"

void lerArquivoProcessos(FILE *arq, Fila *f1) {
    for (int i = 0; !feof(arq); i++) {
        char nome[20];
        float tempo_de_execucao;

        fscanf(arq, "%s %f\n", nome, &tempo_de_execucao);
        enfileirar(f1, nome, tempo_de_execucao);
	}
}

Fila *criarFila(char nome[]) {
    Fila *novaFila = (Fila*) malloc(sizeof(Fila));
    strcpy(novaFila->nome, nome);
    novaFila->ini = novaFila->fim = NULL;
    return novaFila; 
}

ProcessoEncadeado *criarNovoNo(char nome[], float tempo_de_execucao) {
    ProcessoEncadeado *novoNo = (ProcessoEncadeado*) malloc(sizeof(ProcessoEncadeado));
    if (novoNo != NULL) {
        strcpy(novoNo->nome, nome);
        novoNo->tempo_de_execucao = tempo_de_execucao;
        novoNo->prox = NULL;
    }
    return novoNo;
}

void enfileirar(Fila *f, char nome[], float tempo_de_execucao) {
    ProcessoEncadeado *novo = criarNovoNo(nome, tempo_de_execucao);
    if (novo != NULL) {
        if (f->ini == NULL) { // Verificar se a fila está vazia
            f->ini = f->fim = novo; // Atualizar ini e fim
        } else {
            f->fim = f->fim->prox = novo;
        }
    }
}

ProcessoEncadeado *desenfileirar(Fila *f) {
    ProcessoEncadeado *aux = f->ini;
    f->ini = aux->prox;
    return aux;
}

short int filaestavazia(Fila f1) {
    if(f1.ini == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void mudarFila(Fila *p1, Fila *p2) {
    while (!filaestavazia(*p1)) {
        ProcessoEncadeado *aux = desenfileirar(p1);
        enfileirar(p2, aux->nome, aux->tempo_de_execucao);
    }
}


void esvaziarFila(Fila *f1) {
    ProcessoEncadeado *aux = f1->ini;
    while(!filaestavazia(*f1)) {
        ProcessoEncadeado *aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    free(f1);
}

void imprimirElementos(Fila *f1, Fila *f2, Fila *f3, Fila *f4) {
    ProcessoEncadeado *aux;
    
    printf("Estado atual da fila de processos:\n");
    
    aux = f1->ini;
    if(aux != NULL) {
        printf("%s: ", f1->nome);
        while(aux != NULL) {
            if (aux->prox == NULL) {
                printf(" %s = %.f\n", aux->nome, aux->tempo_de_execucao);
            } else {
                printf(" %s = %.f ← ", aux->nome, aux->tempo_de_execucao);
            }
            aux = aux->prox;
        }
    } else {
        printf("%s: vazia\n", f1->nome);
    }
    
    aux = f2->ini;
    if(aux != NULL) {
        printf("%s: ", f2->nome);
        while(aux != NULL) {
            if (aux->prox == NULL) {
                printf(" %s = %.f\n", aux->nome, aux->tempo_de_execucao);
            } else {
                printf(" %s = %.f ← ", aux->nome, aux->tempo_de_execucao);
            }
            aux = aux->prox;
        }
    } else {
        printf("%s: vazia\n", f2->nome);
    }
    
    aux = f3->ini;
    if(aux != NULL) {
        printf("%s: ", f3->nome);
        while(aux != NULL) {
            if (aux->prox == NULL) {
                printf(" %s = %.f\n", aux->nome, aux->tempo_de_execucao);
            } else {
                printf(" %s = %.f ← ", aux->nome, aux->tempo_de_execucao);
            }
            aux = aux->prox;
        }
    } else {
        printf("%s: vazia\n", f3->nome);
    }
    
    aux = f4->ini;
    if(aux != NULL) {
        printf("%s: ", f4->nome);
        while(aux != NULL) {
            if (aux->prox == NULL) {
                printf(" %s = %.f\n", aux->nome, aux->tempo_de_execucao);
            } else {
                printf(" %s = %.f ← ", aux->nome, aux->tempo_de_execucao);
            }
            aux = aux->prox;
        }
    } else {
        printf("%s: vazia\n", f4->nome);
    }
}