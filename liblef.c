#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "liblef.h"


/* A  LEF é uma lista que armazena eventos ordenados pelo membro tempo 
 * do tipo evento_t. Cada evento pode ter um tipo e armazenar em dados 
 * diferentes estruturas de dados que permitem descrever cada evento. */

/* 
 * Cria uma LEF vazia 
 */
lef_t *cria_lef () {
    lef_t *l;
    if (!(l = malloc(sizeof(lef_t))))
        return NULL;
    (*l).Primeiro = NULL;
    return l;
}

/* 
 * Destroi a LEF e retorna NULL. 
 */ 
lef_t *destroi_lef (lef_t *l) {
    nodo_lef_t *aux;
    while ((*l).Primeiro != NULL) {
        aux = (*l).Primeiro;
        (*l).Primeiro = (*(*l).Primeiro).prox;
        free((*aux).evento);
        free(aux);
    }
    free(l);
    return NULL;
}

/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita. 
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo_aux;
    if(!(nodo_aux = malloc(sizeof(nodo_lef_t))))
        return 0;
    evento_t *novo_evento;
    if(!(novo_evento = malloc(sizeof(evento_t)))) {
        free(nodo_aux);
        return 0;
    }
    memcpy(novo_evento, evento, sizeof(evento_t));
    (*nodo_aux).evento = novo_evento;
    (*nodo_aux).prox = (*l).Primeiro;
    (*l).Primeiro = nodo_aux;
    return 1;
}

/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
 * Retorna 1 em caso de sucesso, 0 caso contrario.
 */
int adiciona_ordem_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo_aux;
    if (!(nodo_aux = malloc(sizeof(nodo_lef_t))))
        return 0;
    evento_t *novo_evento;
    if (!(novo_evento = malloc(sizeof(evento_t)))) {
        free(nodo_aux);
        return 0;
    }
    memcpy(novo_evento, evento, sizeof(evento_t));
    (*nodo_aux).prox = (*l).Primeiro;
    (*nodo_aux).evento = novo_evento;
    if ((*l).Primeiro == NULL || (*(*(*l).Primeiro).evento).tempo > (*(*nodo_aux).evento).tempo) {
        (*l).Primeiro = nodo_aux;
        return 1;
    }
    nodo_lef_t *atual = (*l).Primeiro;
    while ((*atual).prox && (*(*(*atual).prox).evento).tempo < (*(*nodo_aux).evento).tempo) {
        atual = (*atual).prox;
    }
    (*nodo_aux).prox = (*atual).prox;
    (*atual).prox = nodo_aux;
    return 1;
}

/* 
 * Retorna e retira o primeiro evento da LEF. 
 * A responsabilidade por desalocar
 * a memoria associada eh de quem chama essa funcao.
 */
evento_t *obtem_primeiro_lef (lef_t *l) {
    if ((*l).Primeiro == NULL)
        return NULL;
    nodo_lef_t *aux = (*l).Primeiro;
    evento_t *e = (*(*l).Primeiro).evento;
    (*l).Primeiro = (*(*l).Primeiro).prox;
    free(aux);
    return e;
}