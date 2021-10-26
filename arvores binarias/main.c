#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(){
  Arvore *A = cria_arvore_vazia();
  A->raiz = insere(A->raiz, 4);
  A->raiz = insere(A->raiz, 5);
  A->raiz = insere(A->raiz, 2);
  A->raiz = insere(A->raiz, 3);
  A->raiz = insere(A->raiz, 8);
  A->raiz = insere(A->raiz, 9);
  pre_ordem(A->raiz);
}
