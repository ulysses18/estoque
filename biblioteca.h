#define NOME_ARQUIVO             "cadastro.dat"
#define CODIGO_NAO_ENCONTRADO    -7
#define CODIGO_VALIDO            -1
#define CODIGO_INVALIDO          -5
#define PEDIDO_FEITO             -3

typedef struct
{
    int material;
    char nome[50];
    float valor_unitario;
    int estoque_inicial;
    int estoque_minimo;
    int n_saida;
    int n_entrada;

    float valor_pedido;
    int valor_total_pedido;
    float qtd_total_saida;
    int n_mair_pedido;
    int maior_saida;
    int qtd_abaixo;
    int saida_recusada;

    int valor_total_compra;
    int valor_total_entrada;
    float qtd_total_entrada;
    int menor_entrada;
    int entrada_recusada;

}tp_produto;

void cria_arquivo();
void ascii_art();
void exibe_menu();

void qtd_invalida(void);///exibe mensagem de erro
void erro_codigo(void);///exibe mensagem de erro
void materia_nao_cadastrada(void);///exibe mensagem de erro

int checa_codigo(tp_produto dados, int codigo);///funçao para ver se foi inserido um codigo repetido
int add_material();/// adiciona um material no arquivo
int associa_codigo(int codigo);///associa o codigo inserido com os cadastrados

int verificacao();///verifica o tamanho em bytes do arquivos, se for = a 0 as
                  ///opcoes 2 e 3 nao poderao ser utilizadas
int inicia_saida(int contador);///efetua a saida de material
int inicia_entrada();///efetua a entrada de material

void relatorio_geral(tp_produto dados);
void relatorio_saidas(tp_produto dados);
void relatorio_entradas(tp_produto dados);
void saldo(tp_produto dados);
