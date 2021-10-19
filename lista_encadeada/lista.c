#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <assert.h>
#include <string.h>

// O(1)
Lista* cria_lista(){
  Lista* l = (Lista*)malloc(sizeof(Lista));
  Item* cabeca = cria_item(-1, "", -1, "", -1);
  l->primeiro = cabeca;
  l->ultimo = cabeca;
  l->tamanho = 0;
  l->primeiro->proximo = NULL;
  return l;
}

// O(1)
Item* cria_item(int isbn, char* titulo, int paginas,\
        char* autor, int ano){
  Item* item = (Item*)malloc(sizeof(Item));
  item->isbn = isbn;
  item->titulo = strdup(titulo);
  item->paginas = paginas;
  item->autor = strdup(autor);
  item->ano = ano;
  item->proximo = NULL;
  return item;
}

// O(1)
void inserir(Lista *l, Item *x){
  l->ultimo->proximo = x;
  x->proximo = NULL;
  l->ultimo = x;
  l->tamanho++;
}

// O(1)
int vazia(Lista *l){
  if(l->primeiro == l->ultimo){
    assert(l->tamanho == 0);
    return 1;
  }
  return 0;
}

// Tamanho da lista é n -- pior caso é O(n)
void remover(Lista *l, int isbn){
  if(vazia(l) == 1) return;
  Item *corrente = l->primeiro;
  Item *aux;

  while(corrente->proximo != NULL){
    if(corrente->proximo->isbn == isbn){
      aux = corrente->proximo;
      corrente->proximo = corrente->proximo->proximo;
      if(aux->proximo == NULL) l->ultimo = corrente;
      free(aux->titulo);
      free(aux->autor);
      free(aux);
      l->tamanho--;
      return;
    }
    corrente = corrente->proximo;
  }
}

// O(n²)
void destruir(Lista *l){
  int tamanho = l->tamanho;
  for(int i=0; i<tamanho; i++){
    remover(l, l->ultimo->isbn);
  }
  Item *cabeca = l->primeiro;
  free(cabeca->titulo);
  free(cabeca->autor);
  free(cabeca);
  free(l);
}

// O(n) tanto pior caso quanto pro melhor caso
void imprimir(Lista *l){
  if(vazia(l) == 1){
    printf("Lista vazia\n");
    return;
  }
  Item *corrente = l->primeiro->proximo;
  while(corrente != NULL){
    printf("%d ", corrente->isbn);
    corrente = corrente->proximo;
  }
  printf("\n");
}

// O(n) no pior caso -- O(1) no melhor caso
Item* buscar(Lista *l, int isbn){
  if(vazia(l) == 1) return NULL;
  Item *corrente = l->primeiro->proximo;
  while(corrente != NULL){
    if(corrente->isbn == isbn) return corrente;
    corrente = corrente->proximo;
  }
  return NULL;
}

