#define OUTDIR "temp/"

struct fita{
    char nome[30];
    long int pos;
    int espera;
};

struct controlador{
    int *mem_principal;
    struct fita *fitas;
    int fita_atual;
    int tamanho_memoria;
    int num_elementos;
    int num_fitas;
};

typedef struct fita Fita;
typedef struct controlador Controlador;

Controlador *cria_controlador(int tamanho_memoria);
void ordenacao_inicial(char *arquivo_entrada, Controlador *c);
void intercalacao(Controlador *c);