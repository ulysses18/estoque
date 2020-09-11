#include <stdio.h>
#include "biblioteca.h"
#include "rlutil.h"

void exibe_menu()
{
    printf("\n\n----------------------------\n");
    printf("1. Cadastro de material    |\n");
    printf("2. Saida de material       |\n");
    printf("3. Entrada de material     |\n");
    printf("4. Relatorio               |\n");
    printf("5. Estatisticas de venda   |\n");
    printf("6. Estatisticas de entrada |\n");
    printf("7. Saldo                   |\n");
    printf("0. Sair                    |\n");
    printf("----------------------------");
    printf("\n\nDigite a opcao desejada: ");
}
void ascii_art(void)
{
    printf("\t\t\t\t\t           _      _    _      _____      \n");
    printf("\t\t\t\t\t          | |    | |  | |    | ____|  \n");
    printf("\t\t\t\t\t          | |    | |  | |    | |     _____  _ _____ ______  ____  _ ___  _   _  \n");
    printf("\t\t\t\t\t      _   | |    | |  | |    | |    |  _  || '_   _'   _  |/  _  | '_  || | | | \n");
    printf("\t\t\t\t\t     | |__| | _  | |__| | _  | |___ | (_) || | | | |  |_) || (_| | | | || |_| | \n");
    printf("\t\t\t\t\t     |_____ /(_) |______|(_) |_____||_____||_| |_| |  ____||___,_|_| |_||___, | \n");
    printf("\t\t\t\t\t                                                   | |                    __/ | \n");
    printf("\t\t\t\t\t                                                   |_|                   |___/ \n");
}

void qtd_invalida (void)
{
    setColor(RED);
    printf("***Quantidade invalida!!!***\n");
    resetColor();
    msleep(2000);
}
void erro_codigo(void)
{
    setColor(RED);
    printf("\n***Codigo nao encontrado!!!***");
    resetColor();
    msleep(2000);
}
void materia_nao_cadastrada(void)
{
    setColor(RED);
    printf("\nE necessario cadastrar pelo menos uma materia para usar esta opcao!!!");
    resetColor();
    msleep(2000);
}

void cria_arquivo()
{
    setBackgroundColor(WHITE);
    setColor(BLUE);
    saveDefaultColor();
    cls();
    FILE *arq_cadastro;
    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        if((arq_cadastro = fopen(NOME_ARQUIVO, "wb")) == NULL)
            return 1;

    fclose(arq_cadastro);
}

int add_material()
{
    FILE *arq_cadastro;
    tp_produto dados;
    int condicao, codigo, qtd_cadastrada=0;

    printf("\t\t\t\t***Cadastro de materiais***\n");
    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);
    if(checa_codigo(dados, codigo) != CODIGO_INVALIDO)
    {
        dados.material = codigo;
        printf("Digite o nome do produto: ");
        scanf("%s", dados.nome);
        getchar();
        printf("Digite o valor unitario do produto: ");
        scanf("%f", &dados.valor_unitario);
        getchar();
        printf("Digite a quantidade inicial em estoque: ");
        scanf("%d", &dados.estoque_inicial);
        getchar();
        printf("Digite a quantidade minima em estoque: ");
        scanf("%d", &dados.estoque_minimo);
        getchar();
        dados.n_entrada = 0;
        dados.n_saida = 0;
        dados.valor_total_pedido=0;
        dados.maior_saida=0;
        dados.qtd_abaixo=0;
        dados.n_mair_pedido=0;
        dados.qtd_total_saida=0;
        dados.saida_recusada=0;
        dados.valor_total_compra=0;
        dados.valor_total_entrada=0;
        dados.qtd_total_entrada=0;
        dados.menor_entrada=100000;
        dados.entrada_recusada=0;
        system("cls");
    }
    else
    {
        setColor(RED);
        printf("Codigo ja cadastrado!!");
        return 1;
        resetColor();
        msleep(2000);
    }
    if((arq_cadastro = fopen(NOME_ARQUIVO, "ab+")) == NULL)
    {
        return 1;
    }
    if (fwrite(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        fclose(arq_cadastro);
        return 1;
    }
    fclose(arq_cadastro);
}

int associa_codigo(int codigo)
{
    FILE *arq_cadastro;
    tp_produto dados;
    int status = CODIGO_NAO_ENCONTRADO;

    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        return 1;
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        if (dados.material == codigo)
        {
            status = CODIGO_VALIDO;
            break;
        }
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    return status;
}

void relatorio_geral(tp_produto dados)
{
    setColor(GREEN);
    FILE *arq_cadastro;

    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        return 1;
    printf("\nCod. do item\t  Valor unitario\t  Estoque\t  Estoque min.\t   Qtd de pedidos\t  Qtd de entradas");
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        printf("\n%12d\t\t%8.2f\t%9d\t\t%5d\t\t%9d\t\t%9d", dados.material, dados.valor_unitario,
                                                            dados.estoque_inicial, dados.estoque_minimo,
                                                            dados.n_saida, dados.n_entrada);

        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    resetColor();
}

int checa_codigo(tp_produto dados, int codigo)
{
    int posicao = CODIGO_VALIDO;
    FILE *arq_cadastro;

    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        return 1;
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            printf("erro leitura");
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        if (dados.material == codigo)
        {
            posicao = CODIGO_INVALIDO;
            break;
        }
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                printf("erro leitura");
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    return posicao;
}

int inicia_saida(int contador)
{
    FILE *arq_cadastro;
    tp_produto dados;
    int status, qtd_compra, escolha, posicao=0, resultado=0;

    printf("\t\t\t***Venda de materiais***\n");
    printf("\nDigite o codigo do material: ");
    scanf("%d", &escolha);
    status = associa_codigo(escolha);
    if (status != CODIGO_VALIDO)
    {
        erro_codigo();
        return 1;
    }
    printf("Numero de seu pedido: %d\n", contador);
    printf("\nDigite a quantidade que voce deseja: ");
    scanf("%d", &qtd_compra);
    getchar();
    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb+")) == NULL)
        return 1;
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        if(qtd_compra <= 0)
        {
            dados.saida_recusada+=1;
            qtd_invalida();
            return 1;
        }
        if (dados.material == escolha)
        {
            if(qtd_compra > dados.estoque_inicial)
            {
                setColor(RED);
                dados.saida_recusada+=1;
                printf("***Nao ha estoque para esse pedido!!!***");
                return 1;
                resetColor();
                msleep(2000);

            }
            else if(qtd_compra <= dados.estoque_inicial && qtd_compra > 0)
            {
                dados.estoque_inicial -= qtd_compra;
                if (dados.estoque_inicial < dados.estoque_minimo)
                {
                    setColor(RED);
                    printf("\n***Estoque abaixo do recomendado!***\n");
                    dados.qtd_abaixo+=1;
                    resetColor();msleep(2000);
                }
                dados.valor_pedido = qtd_compra * dados.valor_unitario;
                printf("\nPedido No.%d efetuado com sucesso!\nValor do pedido: %.2f(BRL)", contador,
                       dados.valor_pedido);
                resultado=PEDIDO_FEITO;

                dados.n_saida+=1;
                dados.valor_total_pedido += dados.valor_pedido;
                dados.qtd_total_saida += qtd_compra;

                if(qtd_compra > dados.maior_saida)
                {
                    dados.maior_saida = qtd_compra;
                    dados.n_mair_pedido = dados.n_saida;
                }
            }
            posicao = ftell(arq_cadastro) - sizeof(tp_produto);
            fseek(arq_cadastro, posicao, SEEK_SET);
            if (fwrite(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
                return 1;
            break;
        }
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    return resultado;
}

int verificacao()
{
    FILE *arq_cadastro;
    int qtd_cadastradas;
    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
    {
        printf("erro ao ler");
        return 1;
    }
    fseek(arq_cadastro, 0, SEEK_END);
    qtd_cadastradas = ftell(arq_cadastro);
    fclose(arq_cadastro);
    return qtd_cadastradas;
}

int inicia_entrada()
{
    FILE *arq_cadastro;
    tp_produto dados;
    int status, qtd_entrada, escolha, posicao=0, resultado=0;

    printf("\t\t\t***Compra de materiais***\n");
    printf("\nDigite o codigo do material: ");
    scanf("%d", &escolha);
    status = associa_codigo(escolha);
    if (status != CODIGO_VALIDO)
    {
        erro_codigo();
        return 1;
    }
    printf("\nDigite a quantidade que voce deseja: ");
    scanf("%d", &qtd_entrada);
    getchar();
    if(qtd_entrada <= 0)
    {
        qtd_invalida();
        dados.entrada_recusada++;
        return 1;
    }
    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb+")) == NULL)
        return 1;
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        if (dados.material == escolha)
        {
            if(dados.estoque_inicial >= dados.estoque_minimo)
            {
                setColor (RED);
                printf("***Entrada negada! Estamos acima do estoque minimo***");
                dados.entrada_recusada++;
                resetColor();
                msleep(2500);
                break;
            }
            printf("\nOperacao realizada com sucesso!\nEstoque atual: %d", dados.estoque_inicial + qtd_entrada);

            if(qtd_entrada < dados.menor_entrada)
            {
                dados.menor_entrada = qtd_entrada;
            }
            dados.n_entrada++;
            dados.estoque_inicial += qtd_entrada;
            dados.valor_total_compra = dados.valor_unitario * qtd_entrada;
            dados.valor_total_entrada += dados.valor_total_compra;
            dados.qtd_total_entrada += qtd_entrada;

            posicao = ftell(arq_cadastro) - sizeof(tp_produto);
            fseek(arq_cadastro, posicao, SEEK_SET);
            if (fwrite(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
                return 1;
            break;
        }
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
}

void relatorio_saidas(tp_produto dados)
{
    setColor(GREEN);
    FILE *arq_cadastro;

    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        return 1;
    printf("\nQtd pedidos\tValor total\tN./Qtd. > pedido\tMedia pedidos\tPedidos abaixo do min.\tPedidos recusados");
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        printf("\n\t%3d\t%11d\t%2d\t%8d\t%13.2f\t\t\t%5d\t\t%9d", dados.n_saida, dados.valor_total_pedido, dados.n_mair_pedido,
                                                                  dados.maior_saida, dados.qtd_total_saida / (dados.n_saida),
                                                                  dados.qtd_abaixo, dados.saida_recusada);
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    resetColor();
}

void relatorio_entradas(tp_produto dados)
{
    setColor(GREEN);
    FILE *arq_cadastro;

    if((arq_cadastro = fopen(NOME_ARQUIVO, "rb")) == NULL)
        return 1;
    printf("\nQtd entradas\tValor total entrada\tQtd. da < entrada\tMedia entradas\tEntrada recusada");
    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    while(!feof(arq_cadastro))
    {
        printf("\n\t%4d\t\t%11d\t\t%9d\t\t%6.2f\t\t%8d", dados.n_entrada, dados.valor_total_entrada,
                                                         dados.menor_entrada, dados.qtd_total_entrada/(dados.n_entrada),
                                                         dados.entrada_recusada);
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }

    }
    fclose(arq_cadastro);
    resetColor();
}

void saldo(tp_produto dados)
{
    setColor(MAGENTA);
    FILE *arq_cadastro;

    if((arq_cadastro=fopen(NOME_ARQUIVO, "rb+")) == NULL)
        return 1;

    if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
    {
        if (!feof(arq_cadastro))
        {
            fclose(arq_cadastro);
            return 1;
        }
    }
    printf("\n\t\t\t\t\t\t\t\t\t***Saldo total***\n");
    printf("\n\t\t\t\t\t\t\t\tGanhos\t\tGastos\t\tSaldo(BRL)");
    while(!feof(arq_cadastro))
    {
        printf("\n\t\t\t\t\t\t\t\t%6d\t\t%6d\t\t%5d", dados.valor_total_pedido, dados.valor_total_entrada,
                                                      dados.valor_total_pedido-dados.valor_total_entrada);
        if (fread(&dados, sizeof(tp_produto), 1, arq_cadastro) == 0)
        {
            if (!feof(arq_cadastro))
            {
                fclose(arq_cadastro);
                return 1;
            }
        }
    }
    fclose(arq_cadastro);
    resetColor();
}
