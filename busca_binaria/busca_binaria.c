#include <stdio.h>

int pesquisa_binaria(int *v, int esq, int dir, int x){

  if(dir < esq)
    return -1;

  int meio = esq + (dir-esq)/2;

  if(v[meio] == x)
    return meio;

  if(x > v[meio])
    return pesquisa_binaria(v, meio+1, dir, x);
  else
    return pesquisa_binaria(v, esq, meio-1, x);
}

int main(){
  int v[] = {1,2,3,4,5};
  int tamanho = 5;
  printf("pos=%d\n",pesquisa_binaria(v, 0, tamanho-1, 4));
  return 0;
}
