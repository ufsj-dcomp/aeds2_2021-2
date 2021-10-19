#ifndef _CONJUNTO_H
#define _CONJUNTO_H

#include "tad_ilusoria.h"
typedef struct conjunto Conjunto;

/* Parâmetro 1: tamanho do conjunto*/
Conjunto* cria_conjunto_vazio(int);
void inserir_inteiro(Conjunto*, int);
Conjunto* uniao(Conjunto*, Conjunto*);
void listar(Conjunto*);
void destroi_conjunto(Conjunto*);
#endif
