#ifndef ARVORE_H
#define ARVORE_H

struct no{
  struct no *esq;
  struct no *dir;
  int chave;
};

typedef struct no No;

struct arvore{
  No *raiz;
};

typedef struct arvore Arvore;

Arvore* cria_arvore_vazia();
No* cria_no(int);
// Insere recebe um inteiro X e uma raiz R1 e retorna um ponteiro pro nó
// de uma nova árvore R2 que é a mesma árvore R1 porém com um nó com
// chave X
No* insere(No*, int);
No* busca(No*, int);
void pre_ordem(No*);
void pos_ordem(No*);
void ordem_central(No*);
void destroi(No*);

#endif
