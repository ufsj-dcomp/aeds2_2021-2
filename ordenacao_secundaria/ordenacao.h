#define OUTDIR "temp/"

struct fita{
    char nome[30];
    long int pos;
    int espera;
};

struct controlador{
    int *mem_principal;
    struct fita *fitas;
    int fita_parte1;
    int fita_parte2;
    int tamanho_memoria;
    int num_elementos;
    int num_fitas;
};

typedef struct fita Fita;
typedef struct controlador Controlador;
Controlador* cria_controlador(int tam);
void ordenacao_inicial(char *arquivo_entrada, Controlador *c);
void intercalacao(Controlador* c);

