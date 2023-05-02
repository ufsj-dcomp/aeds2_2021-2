#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ordenacao.h"

int comparador(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

Controlador *cria_controlador(int tamanho_memoria)
{
    Controlador *c = (Controlador *)malloc(sizeof(Controlador));
    c->mem_principal = (int *)malloc(tamanho_memoria * sizeof(int));
    c->fitas = (Fita *)malloc(2 * tamanho_memoria * sizeof(Fita));
    c->num_fitas = 2 * tamanho_memoria;
    for (int i = 0; i < c->num_fitas; i++)
    {
        sprintf(c->fitas[i].nome, OUTDIR "fita.%d", i);
        FILE *f = fopen(c->fitas[i].nome, "w");
        fclose(f);
        c->fitas[i].pos = 0;
        c->fitas[i].espera = 0;
    }
    c->fita_parte1 = 0;
    c->fita_parte2 = 3;
    c->tamanho_memoria = tamanho_memoria;
    c->num_elementos = 1;
    return c;
}

void limpa_fitas(Controlador *c, int num)
{
    for (int i = num; i < c->tamanho_memoria + num; i++)
    {
        FILE *f = fopen(c->fitas[i].nome, "w");
        fclose(f);
        c->fitas[i].pos = 0;
    }
}

//A quantidade de passadas na parte da intercalacao
//É calculada com base na definicao logaritmica pra essa quantia. 
int quantas_passadas(Controlador *c){

    int passadas=0;
    double numerador;
    float n = c->num_elementos;
    float f = c->tamanho_memoria;
    
    numerador = log(n)/log(f);
    passadas = ceil(numerador) -1;

    return passadas;

}


void zera_pos_fitas(Controlador *c)
{
    for (int i = 0; i < c->num_fitas; i++)
        c->fitas[i].pos = 0;
}

void atualiza_parte1(Controlador *c)
{
    c->fita_parte1 = (c->fita_parte1 + 1) % (c->tamanho_memoria);
}
//Atualiza o indicador da segunda metade das fitas
void atualiza_parte2(Controlador *c)
{
    c->fita_parte2 = ((c->fita_parte2 + 1 ) % (c->tamanho_memoria)) + c->tamanho_memoria;
}

void ordenacao_inicial(char *arquivo_entrada, Controlador *c)
{
    FILE *arquivo_principal = fopen(arquivo_entrada, "r");

    int aux, fita_atual;
    limpa_fitas(c,c->tamanho_memoria);

    int contador = 0;
    while (1)
    {

        fscanf(arquivo_principal, "%d", &aux);

        c->mem_principal[contador] = aux;
        contador++;
        c->num_elementos++;

        // Memoria principal cheia
        if (contador == c->tamanho_memoria ||
            (feof(arquivo_principal) && contador > 0))
        {

            qsort(c->mem_principal, contador, sizeof(int), comparador);

            // Abre fita atual e salta para a posição corrente
            fita_atual = c->fita_parte1;
            FILE *f = fopen(c->fitas[fita_atual].nome, "r+");
            fseek(f, c->fitas[fita_atual].pos, SEEK_SET);

            // Imprime elementos na fita
            for (int i = 0; i < contador; i++)
            {
                if (i == contador - 1)
                {
                    fprintf(f, "%d ", c->mem_principal[i]);
                }
                else
                {
                    fprintf(f, "%d,", c->mem_principal[i]);
                }
            }

            // Salva posição corrente e fecha arquivo
            c->fitas[fita_atual].pos = ftell(f);
            fclose(f);
            contador = 0;
            atualiza_parte1(c);
        }
        if (feof(arquivo_principal))
        {
            break;
        }
    }
}

int recupera_proximo_elemento(Fita *fita)
{
    
    if (fita->espera == 1)
        return -1;

    FILE *arquivo = fopen(fita->nome, "r");
    fseek(arquivo, fita->pos, SEEK_SET);

    int elemento;
    char proximo_caractere;
    
    fscanf(arquivo, "%d%c", &elemento, &proximo_caractere);

    if (feof(arquivo)){

        return -1;
    }
    if (proximo_caractere == ' ')
        fita->espera = 1;

    fita->pos = ftell(arquivo);
    fclose(arquivo);
    return elemento;
}

int encontra_indice_menor(Controlador *c)
{
    int indice_menor = -1;
    for (int i = 0; i < c->tamanho_memoria; i++)
    {
        if (indice_menor == -1 && c->mem_principal[i] >= 0)
        {
            indice_menor = i;
            continue;
        }
        if (indice_menor == -1)
            continue;
        if (c->mem_principal[i] == -1)
            continue;
        if (c->mem_principal[i] < c->mem_principal[indice_menor])
            indice_menor = i;
    }
    return indice_menor;
}

int primeiros_elementos(Controlador* c, int pagina){

    int soma_esperas = 0;
    //Preenche a mem_principal com os primeiros elementos das  fitas
    //Pagina indica se estamos na primeira ou segunda metade das fitas
    //Retorna a soma dos primeiros elementos
    for (int i = pagina; i < c->tamanho_memoria + pagina; i++){
            c->fitas[i].espera = 0;
            c->mem_principal[i-pagina] = recupera_proximo_elemento(&c->fitas[i]);
            soma_esperas = soma_esperas + c->mem_principal[i-pagina];
        }
    return soma_esperas;
}

void inverte_intercalacao(Controlador* c, int* pagina){

    //Faz com que a intercalação vá para a outra metade das fitas
    limpa_fitas(c,*pagina);
    zera_pos_fitas(c);

    if(*pagina == 0)
        *pagina = 3;
    else
        *pagina = 0;

    c->fita_parte1 = 0;
    c->fita_parte2 = 3;

}

void intercala_elemento(Controlador* c, FILE* arquivo_escrita,int pagina, int virgula){

    //Dado o indice menor, intercala um elemnto na fita correspondente
    int indice_menor;
    indice_menor = encontra_indice_menor(c);
    if(virgula == 0)
        fprintf(arquivo_escrita, "%d", c->mem_principal[indice_menor]);
    else
        fprintf(arquivo_escrita, ",%d", c->mem_principal[indice_menor]);
    c->mem_principal[indice_menor]  = recupera_proximo_elemento(&c->fitas[indice_menor+pagina]);

}

void intercalacao(Controlador *c)
{
    int passada= quantas_passadas(c);
    int virgula = 0, pagina = 0;
    int indice_menor, soma_espera;
    FILE *arquivo_escrita;
    Fita *fita;
    zera_pos_fitas(c);

    while (1){
        
        if(passada == 0)return;
        
        //Seleciona os primeiros elementos de cada grupo
        soma_espera = primeiros_elementos(c,pagina);
        indice_menor = -2;
        
        //Entra nessa condição quando já tiverem acabado os grupos pra intercalar nessa passada
        //Inverte a intercalacao, e intercala os novos grupos 
        if (soma_espera == -3){
            inverte_intercalacao(c,&pagina);
            passada--;           
            continue;
        }

        //Seleciona o arquivo que vai ser escrito
        //Pagina = 0; estamos intercalando grupos na primeira metade de fitas
        //Pagina = 3; estamos intercalando grupos na segunda metade de fitas
        if(pagina == 0)
            fita = &c->fitas[c->fita_parte2];
        if(pagina == 3)
            fita = &c->fitas[c->fita_parte1];
        arquivo_escrita = fopen(fita->nome, "r+");
        fseek(arquivo_escrita, fita->pos, SEEK_SET);

        virgula = 0;
        intercala_elemento(c,arquivo_escrita,pagina,virgula);
        
        virgula = 1;
        while (indice_menor != -1)
        {
            indice_menor = encontra_indice_menor(c);
            if (indice_menor != -1)
            {
                intercala_elemento(c,arquivo_escrita,pagina,virgula);   
            }
            else
            {
                fprintf(arquivo_escrita, " ");
                fita->pos = ftell(arquivo_escrita);
                fclose(arquivo_escrita);
                if(pagina == 0)
                    atualiza_parte2(c);
                if(pagina == 3)
                    atualiza_parte1(c);
                
            }
        }
    }
}
