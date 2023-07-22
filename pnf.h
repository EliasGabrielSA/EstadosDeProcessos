#ifndef FILA_H
#define FILA_H

#define MAX 30

typedef struct _processoencadeado {
    char nome[MAX];
    float tempo_de_execucao;
    struct _processoencadeado *prox;
} ProcessoEncadeado;

typedef struct _fila {
    char nome[MAX];
    ProcessoEncadeado *ini;
    ProcessoEncadeado *fim;
} Fila;

void lerArquivoProcessos(FILE* , Fila*, int*);
ProcessoEncadeado *criarNovoNo(char[], float);
void enfileirar(Fila*, char[], float);
ProcessoEncadeado *desenfileirar(Fila *f);
Fila *criarFila();

#endif
