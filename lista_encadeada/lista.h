
struct item{
  int isbn;
  char *titulo;
  int paginas;
  char *autor;
  int ano;
  struct item *proximo;
};

struct lista{
  struct item *primeiro;
  struct item *ultimo;
  int tamanho;
};

typedef struct item Item;
typedef struct lista Lista;

Lista* cria_lista();
Item* cria_item(int, char*, int, char*, int);
void inserir(Lista*, Item*);
void remover(Lista*, int);
void destruir(Lista*);
void imprimir(Lista*);
Item* buscar(Lista*, int);
int vazia(Lista*);


