#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

/* Cria uma fila vazia e a retorna, se falhar retorna NULL. */
fila_t *cria_fila () {
    fila_t *f;
    if (!(f = malloc(sizeof(fila_t))))
        return NULL;
    (*f).tamanho = 0;
    (*f).ini = NULL;
    (*f).fim = NULL;
    return f;
}

/* Remove todos os elementos da fila, libera espaco e devolve NULL. */
fila_t *destroi_fila (fila_t *f) {
    int elemento = 0;
    while ((*f).ini != NULL) {
        retira_fila(f, &elemento);
    }
    free(f);
    return NULL;
}

/* Retorna 1 se a fila esta vazia e 0 caso contrario. */
int vazia_fila (fila_t *f) {
    if (tamanho_fila(f) == 0)
        return 1;
    return 0;
}

/* Retorna o numero de elementos da fila. */
int tamanho_fila (fila_t *f) {
    return (*f).tamanho;
}

/* Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario. */
int insere_fila (fila_t *f, int elemento) {
    nodo_f_t *novo_nodo;
    if (!(novo_nodo = malloc(sizeof(nodo_f_t))))
        return 0;
    (*novo_nodo).elem = elemento;
    (*novo_nodo).prox = NULL;
    ((*f).tamanho)++;
    if (vazia_fila(f)) {
        printf("fila vazia\n");
        return 0;
    }
    if (tamanho_fila(f) == 1) {
        (*f).ini = novo_nodo;
        (*f).fim = novo_nodo;
        return 1;
    }
    (*(*f).fim).prox = novo_nodo;
    (*f).fim = novo_nodo;
    return 1;
}

/* Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro *elemento. Retorna 1 se a operacao foi bem sucedida
 * e 0 caso contrario. */
int retira_fila (fila_t *f, int *elemento) {
    if (vazia_fila(f)) {
        printf("fila vazia\n");
        return 0;
    }
    *elemento = (*(*f).ini).elem;
    nodo_f_t *nodo_aux = (*(*f).ini).prox;
    free((*f).ini);
    (*f).ini = nodo_aux;
    ((*f).tamanho)--;
    return 1;
}

/* para depuracao */
void imprime_fila (fila_t *f) {
    if (vazia_fila(f)) {
        printf("fila vazia\n");
        return;
    }
    nodo_f_t *atual;
    int i;
    for (i = 0; i < tamanho_fila(f)-1; i++) {
        printf("%d ", (*atual).elem);
        atual = (*atual).prox;
    }
    printf("%d\n", (*atual).elem);
}