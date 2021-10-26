#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

Arvore* cria_arvore_vazia(){
  Arvore *A = (Arvore*)malloc(sizeof(Arvore));
  A->raiz = NULL;
  return A;
}

No* cria_no(int chave){
  No *x = (No*)malloc(sizeof(No));
  x->esq = NULL;
  x->dir = NULL;
  x->chave = chave;
  return x;
}

// Insere recebe um inteiro X e uma raiz R1 e retorna um ponteiro pro nó
// de uma nova árvore com raiz e R2 que é a árvore R1 o nó com nova_chave X
No* insere(No *raiz, int nova_chave){
  if(raiz == NULL){
    No *novo_no = cria_no(nova_chave);
    return novo_no;
  }

  if(raiz->chave == nova_chave){
    printf("Elemento já existe\n");
  }
  if(raiz->chave > nova_chave){
    raiz->esq = insere(raiz->esq, nova_chave);
  }
  if(raiz->chave < nova_chave){
    raiz->dir = insere(raiz->dir, nova_chave);
  }
  return raiz;
}

void pre_ordem(No *no){
  if(no == NULL) return;
  printf("%d\n", no->chave);
  pre_ordem(no->esq);
  pre_ordem(no->dir);
}

void pos_ordem(No *no){
  if(no == NULL) return;
  pos_ordem(no->esq);
  pos_ordem(no->dir);
  printf("%d\n", no->chave);
}

void ordem_central(No *no){
  if(no == NULL) return;
  ordem_central(no->esq);
  printf("%d\n", no->chave);
  ordem_central(no->dir);
}

No* busca(No *raiz, int chave){
  if(raiz == NULL){
    return NULL;
  }

  if(raiz->chave == chave){
    return raiz;
  }
  if(chave < raiz->chave){
    return busca(raiz->esq, chave);
  }
  if(chave > raiz->chave){
    return busca(raiz->dir, chave);
  }
}

void destroi(No *raiz){
  if(raiz == NULL) return;
  destroi(raiz->esq);
  destroi(raiz->dir);
  free(raiz);
}





