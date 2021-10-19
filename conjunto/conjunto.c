#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>

// Estruturas de dados
struct conjunto{
  int *conjunto;
  int max_tamanho;
  int num_elementos;
};

// Funções privadas
int busca(int *, int, int);

// Implementações
Conjunto* cria_conjunto_vazio(int max_tamanho){
  Conjunto *x = (Conjunto*)malloc(sizeof(Conjunto));
  x->conjunto = (int*)malloc(max_tamanho*sizeof(int));
  x->max_tamanho = max_tamanho;
  x->num_elementos = 0;
  return x;
}

int busca(int *lista, int n, int tamanho_lista){
  for(int i=0; i<tamanho_lista; i++){
    if(lista[i] == n) return 1;
  }
  return 0;
}

void inserir_inteiro(Conjunto *x, int n){
  if(x->num_elementos == x->max_tamanho){
    printf("Conjunto cheio!\n");
    return;
  }
  if(busca(x->conjunto, n, x->num_elementos) == 1)
    return;
  x->conjunto[x->num_elementos] = n;
  x->num_elementos++;
}

Conjunto* uniao(Conjunto *a, Conjunto *b){
  Conjunto *c = cria_conjunto_vazio(a->num_elementos + b->num_elementos);
  for(int i=0; i<a->num_elementos; i++){
    inserir_inteiro(c, a->conjunto[i]);
  }
  for(int i=0; i<b->num_elementos; i++){
    inserir_inteiro(c, b->conjunto[i]);
  }
  return c;
}

void listar(Conjunto *a){
  for(int i=0; i<a->num_elementos; i++){
    printf("%d ",a->conjunto[i]);
  }
  printf("\n");
}

void destroi_conjunto(Conjunto *a){
  free(a->conjunto);
  free(a);
}


















