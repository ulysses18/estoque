#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main()
{
    int cont_while = 3, opcao_menu, resultado, contador_saida=1, tamanho_arq;
    FILE *arq_cadastro;
    tp_produto dados;

    cria_arquivo();
    ascii_art();
    printf("\n\n\t\t\t\t\t\t\t\t***Venda de material de construcao***");
    do
    {
        exibe_menu();
        scanf("%d", &opcao_menu);
        system("cls");
        switch(opcao_menu)
        {
        case 1:
            add_material();
            break;
        case 2:
            tamanho_arq = verificacao();
            if(tamanho_arq == 0)
            {
                materia_nao_cadastrada();
                break;
            }
            resultado = inicia_saida(contador_saida);
            if(resultado == PEDIDO_FEITO)
            {
                contador_saida++;
            }
            break;
        case 3:
            tamanho_arq = verificacao();
            if(tamanho_arq == 0)
            {
                materia_nao_cadastrada();
                break;
            }
            inicia_entrada();
            break;
        case 4:
            relatorio_geral(dados);
            break;
        case 5:
            relatorio_saidas(dados);
            break;
        case 6:
            relatorio_entradas(dados);
            break;
        case 7:
            saldo(dados);
            break;
        case 0:
            printf("\n\t\t\t\t\t\t\t\t\t***Finalizando programa***\n\n");
            return 0;
        default:
            printf("\n\t\t\t\t\t\t\t***Operacao invalida!***");
            break;
        }

    }
    while(cont_while != 0);
}
