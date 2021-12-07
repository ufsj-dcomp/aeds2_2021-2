#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    Controlador *c = cria_controlador(3);
    ordenacao_inicial("entrada.txt", c);
    intercalacao(c);
    return 0;
}