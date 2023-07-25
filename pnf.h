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

void lerArquivoProcessos(FILE* , Fila*);
ProcessoEncadeado *criarNovoNo(char[], float);
void enfileirar(Fila*, char[], float);
ProcessoEncadeado *desenfileirar(Fila *f);
Fila *criarFila();
void mudarFila(Fila *p1, Fila *p2);
short int filaestavazia(Fila);
void esvaziarFila(Fila *f1);
void imprimirElementos(Fila*, Fila*, Fila*, Fila*);

#endif
