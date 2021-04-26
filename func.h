#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char movimento[10];
    char linha;
    char coluna;
} Comando;

void instrucoes();

int **alocaMatriz(int linha, int coluna);

void preencheMatriz(int **jogo, int linha, int coluna);

int **lerArquivoTexto(char *argv, int *linha, int *coluna);

void imprimeMatriz(int **jogo, int *linha, int *coluna);

int verificaMovimento(int **jogo, int linha, int coluna, Comando *comando, int *jogada);

void realizaJogada(int **jogo, int linha, int coluna, Comando *comando, int x);

int verificaPerdeu(int **jogo, int linha, int coluna);

void jogando(int **jogo, int linha, int coluna, Comando *comando, int *jogada);

void salvaJogo(int **jogo, int linha, int coluna);

void ajuda(int **jogo, int linha, int coluna);

void desalocaTudo(int **jogo, int linha, int coluna, Comando *comando, int *jogada);