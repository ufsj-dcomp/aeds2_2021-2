#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  Conjunto *a = cria_conjunto_vazio(10);
  Conjunto *b = cria_conjunto_vazio(15);
  inserir_inteiro(a,2);
  inserir_inteiro(a,1);
  inserir_inteiro(b,1);
  inserir_inteiro(b,3);
  inserir_inteiro(b,4);
  Conjunto *c = uniao(a,b);
  listar(c);
  destroi_conjunto(a);
  destroi_conjunto(b);
  return 0;
}
