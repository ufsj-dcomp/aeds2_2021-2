#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){

  Lista *l = cria_lista();

  inserir(l, cria_item(1,"Cronicas 1", 50, "Joao", 2010));
  inserir(l, cria_item(2,"Cronicas 1", 75, "Jose", 2004));
  inserir(l, cria_item(3,"Cronicas 1", 111, "Joaquim", 1999));
  inserir(l, cria_item(4,"Cronicas 1", 219, "Jonas", 2020));

  imprimir(l);
  remover(l, 1);
  imprimir(l);

  destruir(l);

  return 0;
}
