#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"

int comparador(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

Controlador *cria_controlador(int tamanho_memoria){
    Controlador *c = (Controlador*)malloc(sizeof(Controlador));
    c->mem_principal = (int*)malloc(tamanho_memoria*sizeof(int));
    c->fitas = (Fita*)malloc(2*tamanho_memoria*sizeof(Fita));
    c->num_fitas = 2*tamanho_memoria;
    for(int i=0; i<c->num_fitas; i++){
        sprintf(c->fitas[i].nome, OUTDIR"fita.%d", i);
        FILE *f = fopen(c->fitas[i].nome, "w");
        fclose(f);
        c->fitas[i].pos = 0;
        c->fitas[i].espera = 0;
    }
    c->fita_atual = 0;
    c->tamanho_memoria = tamanho_memoria;
    c->num_elementos = -1;
    return c;
}

void limpa_fitas(Controlador *c){
    for(int i=0; i < c->num_fitas; i++){
        FILE *f = fopen(c->fitas[i].nome, "w");
        fclose(f);
        c->fitas[i].pos = 0;
    }
}

void zera_pos_fitas(Controlador *c){
    for(int i=0; i < c->num_fitas; i++)
        c->fitas[i].pos = 0;
}

void atualiza_fita_atual(Controlador *c){
    c->fita_atual = (c->fita_atual+1) % (c->tamanho_memoria);
}

void ordenacao_inicial(char *arquivo_entrada, Controlador *c){
    FILE *arquivo_principal = fopen(arquivo_entrada,"r");

    int aux, fita_atual;
    limpa_fitas(c);

    int contador = 0;
    while(1){

        fscanf(arquivo_principal, "%d", &aux);

        if(!feof(arquivo_principal)){
            c->mem_principal[contador] = aux;
            contador++;
        }

        // Memoria principal cheia
        if(contador == c->tamanho_memoria || \
            (feof(arquivo_principal) && contador > 0)){
            
            qsort(c->mem_principal, contador, sizeof(int), comparador);

            // Abre fita atual e salta para a posição corrente
            fita_atual = c->fita_atual;
            FILE *f = fopen(c->fitas[fita_atual].nome, "r+");
            fseek(f, c->fitas[fita_atual].pos, SEEK_SET);

            // Imprime elementos na fita
            for(int i=0; i< contador; i++){
                if(i == contador-1){
                    fprintf(f,"%d ", c->mem_principal[i]);
                } else {
                    fprintf(f,"%d,", c->mem_principal[i]);
                }
            }

            // Salva posição corrente e fecha arquivo
            c->fitas[fita_atual].pos = ftell(f);
            fclose(f);
            contador = 0;
            atualiza_fita_atual(c);
        }
        if(feof(arquivo_principal)){
            break;
        } 
    }
}

int recupera_proximo_elemento(Fita *fita){

    if(fita->espera == 1) return -1;

    FILE *arquivo = fopen(fita->nome, "r");
    fseek(arquivo, fita->pos, SEEK_SET);

    int elemento;
    char proximo_caractere;;
    fscanf(arquivo, "%d%c", &elemento, &proximo_caractere);

    if(feof(arquivo)) return -1;
    if(proximo_caractere == ' ') fita->espera = 1;

    fita->pos = ftell(arquivo);
    fclose(arquivo);
    return elemento;
}

int encontra_indice_menor(Controlador *c){
    int indice_menor = -1;
    for(int i=0; i < c->tamanho_memoria; i++){
        if(indice_menor == -1 && c->mem_principal[i] >= 0){
            indice_menor = i;
            continue;
        }
        if(indice_menor == -1) continue;
        if(c->mem_principal[i] == -1) continue;
        if(c->mem_principal[i] < c->mem_principal[indice_menor])
            indice_menor = i;
    }
    return indice_menor;
}

void intercalacao(Controlador *c){

    int elemento;
    zera_pos_fitas(c);

    for (int i=0; i < c->tamanho_memoria; i++){
        elemento = recupera_proximo_elemento(&c->fitas[i]);
        c->mem_principal[i] = elemento;
    }

    Fita *fita = &c->fitas[c->tamanho_memoria];
    FILE *arquivo_escrita = fopen(fita->nome,"r+");

    int indice_menor = -2;
    while (indice_menor != -1){
        indice_menor = encontra_indice_menor(c);
        if(indice_menor != -1){
            fprintf(arquivo_escrita, ",%d", c->mem_principal[indice_menor]);
            elemento = recupera_proximo_elemento(&c->fitas[indice_menor]);
            c->mem_principal[indice_menor] = elemento;
        } else {
            fprintf(arquivo_escrita, " ");
            fita->pos = ftell(arquivo_escrita);
            fclose(arquivo_escrita);
        }
    }
}





















