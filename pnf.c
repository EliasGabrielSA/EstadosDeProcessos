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

Fila *criarFila() {
    Fila *novaFila = (Fila*) malloc(sizeof(Fila));
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
        if (f->fim == NULL) { // Verificar se a fila está vazia
            f->ini = f->fim = novo; // Atualizar ini e fim
        } else {
            f->fim->prox = novo;
            f->fim = novo;
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
    while(!filaestavazia(*p1)) {
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