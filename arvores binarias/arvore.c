
Arvore* cria_arvore_vazia(){
  Arvore *A = (Arvore*)malloc(sizeof(Arvore));
  A->raiz = NULL;
  return A;
}

No* cria_no(int nova_chave){
  No *x = (No*)malloc(sizeof(No));
  x->esq = NULL;
  x->dir = NULL;
  x->nova_chave = nova_chave;
  return x;
}

// Insere recebe um inteiro X e uma raiz R1 e retorna um ponteiro pro nó
// de uma nova árvore com raiz e R2 que é a árvore R1 o nó com nova_chave X
No* insere(No *no, int nova_chave){
  if(no == NULL){
    No *novo = cria_no(nova_chave);
    return novo;
  }

  if(no->chave == nova_chave){
    printf("Elemento já existe\n");
  }
  if(no->chave > nova_chave){
    no->esq = insere(no->esq, nova_chave);
  }
  if(no->chave < nova_chave){
    no->dir = insere(no->dir, nova_chave);
  }
  return no;
}

void pre_ordem(No *no){
  if(no == NULL) return;
  printf("%d\n", no->chave);
  pre_ordem(no->esq);
  pre_ordem(no->dir);
}






No* busca(No*, int)
void pre_ordem(No*);
void pos_ordem(No*);
void ordem_central(No*);
void destroi(No*);
