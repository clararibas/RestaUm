#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cores.h"



int main(int argc, char **argv){

    int linha, coluna;
    int **jogo;
    Comando *comando = malloc(100 * sizeof(Comando));
    int *jogada = malloc(100 * sizeof(int));

    printf("\n");
    printf(MAGENTA("\t 🅱 🅴 🅼  🆅 🅸 🅽 🅳 🅾  🅰 🅾  🆁 🅴 🆂 🆃 🅰  🆄 🅼\n"));
    printf("\n");
    printf(BOLD("\tObjetivo:"));
    printf(" por meio de movimentos válidos, \n\tdeixar apenas uma peça no tabuleiro.");
    printf("\n\n");

    if (argc == 1)
    {
        srand(time(NULL));
        linha = rand()% 16 + 1;
        coluna = rand() % 16 + 1;
        if (linha <= 3) {
            linha += 3;
        }
        if (coluna <= 3) {
            coluna += 3;
        }
        jogo = alocaMatriz(linha, coluna);
        preencheMatriz(jogo, linha, coluna);
        imprimeMatriz(jogo, &linha, &coluna);
        jogando(jogo, linha, coluna, comando, jogada);
        desalocaTudo(jogo, linha, coluna, comando, jogada);
    }

    else if (argc == 2)
    {    
        jogo = lerArquivoTexto(argv[1], &linha, &coluna);
        imprimeMatriz(jogo, &linha, &coluna);
        jogando(jogo, linha, coluna, comando, jogada);
        desalocaTudo(jogo, linha, coluna, comando, jogada);
    }
    
    else if (argc == 3)
    {    
        jogo = lerArquivoTexto(argv[2], &linha, &coluna);
        imprimeMatriz(jogo, &linha, &coluna);
        jogando(jogo, linha, coluna, comando, jogada);
        desalocaTudo(jogo, linha, coluna, comando, jogada);
    }   

    return 0;
}