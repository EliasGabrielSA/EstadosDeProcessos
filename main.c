#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

ProcessoEncadeado *criarNovoNo(char nome[], float tempo_de_execucao) {
    ProcessoEncadeado *novoNo = (ProcessoEncadeado*) malloc(sizeof(ProcessoEncadeado));
    if (novoNo != NULL) {
        strcpy(novoNo->nome, nome);
        novoNo->tempo_de_execucao = tempo_de_execucao;
        novoNo->prox = NULL;
    }
    return novoNo;
}

void enfileirar(Fila *f, ProcessoEncadeado* novo) {
    if (novo != NULL) {
        if (f->ini == NULL) {
            f->ini = f->fim = novo;
        } else {
            f->fim = f->fim->prox = novo;
        }
    }
}

ProcessoEncadeado *desenfileirar(Fila *f) {
    if (f->ini == NULL)
        return NULL;

    ProcessoEncadeado *aux = f->ini;
    f->ini = f->ini->prox;
    return aux;
}

void lerArquivoProcessos(FILE *arq, Fila *f1) {
    char nome[20];
    float tempo_de_execucao;

    while (fscanf(arq, "%s %f\n", nome, &tempo_de_execucao) == 2) {
        ProcessoEncadeado *novo = criarNovoNo(nome, tempo_de_execucao);
        enfileirar(f1, novo);
    }
}

Fila *criarFila(char nome[]) {
    Fila *novaFila = (Fila*) malloc(sizeof(Fila));
    strcpy(novaFila->nome, nome);
    novaFila->ini = novaFila->fim = NULL;
    return novaFila;
}

short int filaestavazia(Fila f1) {
    return f1.ini == NULL;
}

void mudarFila(Fila *p1, Fila *p2) {
    while (!filaestavazia(*p1)) {
        ProcessoEncadeado *aux = desenfileirar(p1);
        enfileirar(p2, aux);
    }
}

void esvaziarFila(Fila *f1) {
    while (!filaestavazia(*f1)) {
        ProcessoEncadeado *aux = desenfileirar(f1);
        free(aux);
    }
    free(f1);
}

void imprimirElementos(Fila *f1, Fila *f2, Fila *f3, Fila *f4) {
    ProcessoEncadeado *aux;

    printf("Estado atual das filas de processos:\n");

    aux = f1->ini;
    printf("%s: ", f1->nome);
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%s = %.f\n", aux->nome, aux->tempo_de_execucao);
        } else {
            printf("%s = %.f ← ", aux->nome, aux->tempo_de_execucao);
        }
        aux = aux->prox;
    }

    aux = f2->ini;
    printf("%s: ", f2->nome);
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%s = %.f\n", aux->nome, aux->tempo_de_execucao);
        } else {
            printf("%s = %.f ← ", aux->nome, aux->tempo_de_execucao);
        }
        aux = aux->prox;
    }

    aux = f3->ini;
    printf("%s: ", f3->nome);
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%s = %.f\n", aux->nome, aux->tempo_de_execucao);
        } else {
            printf("%s = %.f ← ", aux->nome, aux->tempo_de_execucao);
        }
        aux = aux->prox;
    }

    aux = f4->ini;
    printf("%s: ", f4->nome);
    while (aux != NULL) {
        if (aux->prox == NULL) {
            printf("%s = %.f\n", aux->nome, aux->tempo_de_execucao);
        } else {
            printf("%s = %.f ← ", aux->nome, aux->tempo_de_execucao);
        }
        aux = aux->prox;
    }
}

int main() {
    FILE *arq;

    char path[100];

    scanf("%s", path);

    arq = fopen(path, "rt");

    if (arq != NULL) {
        int valorquantum;
        fscanf(arq, "%d", &valorquantum);

        Fila *pronto = criarFila("Pronto");
        Fila *espera = criarFila("Espera");
        Fila *execucao = criarFila("Execucao");
        Fila *finalizados = criarFila("Finalizados");

        lerArquivoProcessos(arq, pronto);

        fclose(arq);

        imprimirElementos(pronto, espera, execucao, finalizados);
        printf("\nQuantum: %d\n\n", valorquantum);
        printf("−−−−−−−−−− > Iniciando execucao\n");

        while (!filaestavazia(*pronto)) {
            mudarFila(pronto, execucao);
            printf("Processos foram adicionados a fila de execucao\n");

            while (!filaestavazia(*execucao)) {
                imprimirElementos(pronto, espera, execucao, finalizados);

                ProcessoEncadeado *aux = desenfileirar(execucao);

                aux->tempo_de_execucao -= valorquantum;
                printf("%s esta executando...\n", aux->nome);

                usleep(valorquantum * 1000); // Convert milliseconds to microseconds

                if (aux->tempo_de_execucao > 0) {
                    printf("Quantum expirou, %s sofreu preempcao\n\n", aux->nome);
                    enfileirar(espera, aux);
                    printf("%s foi adicionado a fila de espera\n", aux->nome);
                    printf("\n−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
                } else {
                    aux->tempo_de_execucao = 0;
                    enfileirar(finalizados, aux);
                    printf("%s terminou a execucao, %s foi adicionado a fila de finalizados\n\n", aux->nome, aux->nome);
                    printf("\n−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
                }
            }

            if (!filaestavazia(*espera)) {
                printf("A fila de execucao esta vazia, movendo processos para a fila de prontos\n");
                mudarFila(espera, pronto);
            }
        }

        imprimirElementos(pronto, espera, execucao, finalizados);
        printf("Nao ha mais processos a serem executados\n");
        printf("−−−−−−−−−− > Simulacao finalizada\n");

        esvaziarFila(pronto);
        esvaziarFila(execucao);
        esvaziarFila(espera);
        esvaziarFila(finalizados);

        return 0;
    } else {
        printf("Arquivo nao encontrado.\n");
        return -1;
    }
}