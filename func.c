#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cores.h"

void instrucoes(){
    //Função para imprimir os comandos que podem ser realizados
    printf(BOLD("\n\t\tComandos válidos:\n"));
    printf(BOLD("c CD ") "Move a peça na posição CD para cima.\t\t");
    printf(BOLD("b CD ") "Move a peça na posição CD para baixo.\n");
    printf(BOLD("e CD ") "Move a peça na posição CD para a esquerda.\t\t");
    printf(BOLD("d CD ") "Move a peça na posição CD para a esquerda.\n");
    printf(BOLD("ajuda ") "O programa realiza n movimentos para o usuário.\t");
    printf(BOLD("salvar ") "Salva o tabuleiro tal como está.\n");
    printf(BOLD("sair ") "Encerra o jogo sem salvar.\n\n");
    printf(BOLD("\t\tLegenda tabuleiro:\n"));
    printf(BG_CYAN(" O ")" Posição com peça que pode ser utilizada.\n");
    printf(BG_BLUE(" . ")" Posição vazia que pode ser utilizada.\n");
    printf(BG_MAGENTA(" - ")" Posição não pode ser utilizada.\n");
}

int **alocaMatriz(int linha, int coluna) { 
    //Função que aloca o tabuleiro do jogo
    int **jogo;
    jogo = malloc(linha * sizeof(int*));
    for (int i = 0; i < linha; i++){
        jogo[i] = malloc(coluna * sizeof(int));
    }
    return jogo; //Retorna o tabuleiro
}

void preencheMatriz(int **jogo, int linha, int coluna) {
    //Função para preencher as posições da matriz
    srand(time(NULL));//Função que gera os números aleatórios
    
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            jogo[i][j] = rand() % 3 - 1;//Preenchendo com um número aleatório entre -1 e 1
        }
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            //Substituindo os números para melhorar apresentação 
            if (jogo[i][j] == -1) {
                jogo[i][j] = '-'; // (-1 = -)-> posição inacessível 
            }
            
            if (jogo[i][j] == 0) {
                jogo[i][j] = '.'; // (0 = .) -> posição acessível sem peça
            }

            if (jogo[i][j] == 1) {
                jogo[i][j] = 'O'; // (1 = O) -> posição acessível com peça
            }
            
        }
        
    }
    
}

int **lerArquivoTexto(char *argv, int *linha, int *coluna) {
    // Lendo o arquivo texto especificado pelo usuário
    int **jogo;

    FILE *arquivo;
    arquivo = fopen(argv, "r");

    if (arquivo == NULL) {
        exit (1);
    }

    fscanf(arquivo, "%d %d\n", linha, coluna); //Lendo a quantidade de linhas e de colunas.

    jogo = alocaMatriz(*linha, *coluna); //Alocando dinamicamente o tabuleiro.

    while (!feof(arquivo)) { //Lendo enquanto não chegar ao fim do arquivo.

    for (int i = 0; i < *linha; i++) {
      for (int j = 0; j < *coluna; j++) {
        fscanf(arquivo, "%d", &jogo[i][j]); //Gravando na matriz os valores do arquivo.
      }
      fscanf(arquivo, "\n");
    }
    }

    fclose(arquivo); //Fechando o arquivo de texto.

    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            //Substituindo os números para melhorar apresentação 
            if (jogo[i][j] == -1) {
                jogo[i][j] = '-';
            }
            
            if (jogo[i][j] == 0) {
                jogo[i][j] = '.';
            }

            if (jogo[i][j] == 1) {
                jogo[i][j] = 'O';
            }
            
        }
        
    }


    return jogo; //Retornando a matriz;
}

void imprimeMatriz(int **jogo, int *linha, int *coluna){
    //Função que imprime o tabuleiro
    printf("\t\t");
    printf(BG_WHITE("  "));
    for (char i = 65; i < *coluna+65; i++) { 
		printf(BG_WHITE(" %c "), i);// "Cabeçalho" das colunas começando do A (65)
	}
    printf("\n");
        
    int x = 65;
        
    for (int i = 0; i < *linha; i++) {
        printf(BG_WHITE("\t\t%c "), x);// "Cabeçalho" das linhas começando do A (65)
        for (int j = 0; j < *coluna; j++) {
            //Imprime as posições da matriz em diferentes cores dependendo da peça presente nesta
            if(jogo[i][j] == 'O'){
                printf(BG_CYAN(" %c "), jogo[i][j]);
            }
            if(jogo[i][j] == '.'){
                printf(BG_BLUE(" %c "), jogo[i][j]);
            }
            if(jogo[i][j] == '-'){
                printf(BG_MAGENTA(" %c "), jogo[i][j]);
            }
        }
        printf("\n");
        x++;
   }
}

int verificaMovimento(int **jogo, int linha, int coluna, Comando *comando, int *jogada) {
    //Função que verifica se o comando inserido pelo usuário é válido
    int cont, x = 0;//Cont é referente a quantidade de movimento errado e o X ao comando
    do {
        cont = 0;
        instrucoes();//Imprime as instruções para o usuário saber o que fazer
        printf("\nDigite um comando:");
        scanf("%s", (comando[x].movimento));

        if(strcmp(comando[x].movimento, "salvar") == 0){
            salvaJogo(jogo, linha, coluna);
            break;
        }

        if(strcmp(comando[x].movimento, "sair") == 0){
            desalocaTudo(jogo, linha, coluna, comando, jogada);
            exit(0);  
        }

        if(strcmp(comando[x].movimento, "ajuda") == 0){
            ajuda(jogo, linha, coluna);
            break;
        }

        scanf(" %c", &comando[x].linha);
        scanf(" %c", &comando[x].coluna);
        
        int i = ((int) comando[x].linha) - 65; //Transforma a letra da linha digitada em número
        int j = ((int) comando[x].coluna) - 65; //Transforma a letra da coluna digitada em número


        if(strcmp(comando[x].movimento, "c") != 0 && strcmp(comando[x].movimento, "b") != 0 && strcmp(comando[x].movimento, "d") != 0 && strcmp(comando[x].movimento, "e") != 0 && strcmp(comando[x].movimento, "salvar") != 0 && strcmp(comando[x].movimento, "ajuda") != 0 && strcmp(comando[x].movimento, "sair") != 0){
            printf("\n");
            printf("Digite um comando válido. \n");
            cont++;
        }


        if(jogo[i][j] != 'O'){
            printf("\n");
            printf("Digite um movimento válido. \n");
            cont++;
        }


        if(strcmp(comando[x].movimento, "c") == 0){
            if(jogo[i-1][j] != 'O' || jogo[i-2][j] != '.'){
                printf("Comando inválido!!\n");
                cont++;
            }
        }    

        else if(strcmp(comando[x].movimento, "b") == 0){
            if(jogo[i+1][j] != 'O' || jogo[i+2][j] != '.'){
                printf("Comando inválido!!\n");
                cont++;
            }        
        }

        else if(strcmp(comando[x].movimento, "e") == 0){
            if(jogo[i][j-1] != 'O' || jogo[i][j-2] != '.'){
                printf("Comando inválido!!\n");
                cont++;
            }       
        }

        else if(strcmp(comando[x].movimento, "d") == 0){
            if(jogo[i] [j+1] != 'O' || jogo[i][j+2] != '.'){
                printf("Comando inválido!!\n");
                cont++;
            }      
        }

        x++;

    }while(cont!=0);

    return x; //Retorna a posição do vetor comando na qual o usuário digita entradas válidas
}

void realizaJogada(int **jogo, int linha, int coluna, Comando *comando, int x) {

    //Função que realiza a jogada, ou seja, altera o tabuleiro, caso o movimento digitado pelo usuário seja válido
    int i = ((int) comando[x].linha) - 65;//Transforma a letra da linha digitada em número
    int j = ((int) comando[x].coluna) - 65;//Transforma a letra da linha digitada em número
         
    if(strcmp(comando[x].movimento, "c") == 0){
        jogo[i][j] = '.';
        jogo[i-1][j] = '.';
        jogo[i-2][j] = 'O';
    }    

    if(strcmp(comando[x].movimento, "b") == 0){
        jogo[i][j] = '.';
        jogo[i+1][j] = '.';
        jogo[i+2][j] = 'O';       
    }

    if(strcmp(comando[x].movimento, "e") == 0){
        jogo[i][j] = '.';
        jogo[i][j-1] = '.';
        jogo[i][j-2] = 'O';     
    }

    if(strcmp(comando[x].movimento, "d") == 0){
        jogo[i][j] = '.';
        jogo[i][j+1] = '.';
        jogo[i][j+2] = 'O';       
    }

    printf("\n");
    imprimeMatriz(jogo, &linha, &coluna); //Imprime o novo tabuleiro depois que as alterações da jogada forem feitas
    
}

int verificaPerdeu(int **jogo, int linha, int coluna) {
    //Função que verifica se o usuário ainda tem jogadas possíveis
    int contPeca = 0;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            if(jogo[i][j] == 'O') {
                contPeca++; //Contando quantas peças ainda restam
            }
        }
    }

    int cont = 0;// Auxiliar para contar as jogadas possíveis
    if (contPeca > 1){
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                if(jogo[i][j]=='O'){
                    if(i - 2 >= 0){
                        if(jogo[i-1][j] == 'O' && jogo[i-2][j] == '.'){
                        cont++;
                        }
                    }

                    if (i + 2 < linha){
                        if(jogo[i+1][j] == 'O' && jogo[i+2][j] == '.'){
                        cont++;
                        }
                    }

                    if (j + 2 < coluna){
                        if(jogo[i][j+1] == 'O' && jogo[i][j+2] == '.'){
                        cont++;
                        }
                    }

                    if (j - 2 >= 0){
                        if(jogo[i][j-1] == 'O' && jogo[i][j-2] == '.'){
                        cont++;
                        }
                    } 
                }   
            }
        }
    }

    else if (contPeca == 1) { //SE só tem uma peça o usuário ganha
        printf(BOLD("Você ganhou o jogo!\n"));
        return 2;
    }

    if (cont > 0) { //Se tem mais de uma peça e o contador de movimentos possíveis for maior que zero ele continua a jogar
        return 1;
    }

    else { //Se não há mais jogadas possíveis ele perde o jogo
        printf(BOLD("Você perdeu o jogo.\n"));
        return 0;
    }
    

}

void jogando(int **jogo, int linha, int coluna, Comando *comando, int *jogada) {
    //Função que junta as outras para realizar o jogo enquanto houverem jogadas disponíveis
    int i = 0;
    do{
    jogada[i] = verificaMovimento(jogo, linha, coluna, comando, jogada) - 1; //jogada recebe a posição do vetor comando na qual o usuário digita entradas válidas
    realizaJogada(jogo, linha, coluna, comando, jogada[i]);
    i++;  
    }while(verificaPerdeu(jogo, linha, coluna) == 1);

}

void salvaJogo(int **jogo, int linha, int coluna){
    //Função que salva o tabuleiro do jogo atual quando o usuário solicita
    char nome[50];
    int aux;
    printf("Digite o nome do arquivo:\n");
	scanf("%s", nome);
    FILE *arquivo = fopen(nome, "w");//Abrindo o arquivo para gravação com o nome digitado pelo usuário
    fprintf(arquivo, "%d %d\n" , linha, coluna);//Gravando a linha e a coluna
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {//Trocando de novo os caracteres por inteiros ('-' = -1 / '.' = 0 / 'O' = 1)
            if(jogo[i][j] == 'O'){
                aux = 1;
                fprintf(arquivo, "%3d" , aux);
            }
            if(jogo[i][j] == '.'){
                aux = 0;
                fprintf(arquivo, "%3d" , aux);
            }
            if(jogo[i][j] == '-'){
                aux = -1;
                fprintf(arquivo, "%3d" , aux);
            }
        }
        fprintf(arquivo,"\n");
    }  
    printf("Arquivo %s salvo com sucesso.\n\n", nome);
    fclose(arquivo);
}

void ajuda(int **jogo, int linha, int coluna){
    //Função que realiza movimentos pelo usuário
    int n, cont = 0;// N é a quantidade de movimentos que ele solicitar e cont é pra contar quantas vezes os movimentos foram realizados
    printf("Quantos movimentos?\n");
    scanf("%d", &n);
    for(int x = 1; x <= n; x++){
        if(cont == n)
            break;

        for (int i = 0; i < linha; i++) {
            if(cont == n)
                break;

            for (int j = 0; j < coluna; j++){
                if(cont == n)
                    break;

                if(jogo[i][j] == 'O'){

                    if(i - 2 >= 0){
                        if(jogo[i-1][j] == 'O' && jogo[i-2][j] == '.'){
                            jogo[i][j] = '.';
                            jogo[i-1][j] = '.';
                            jogo[i-2][j] = 'O';
                            cont++;
                            printf("Movimendo c %c%c realizado.\n\n", i+65, j+65);
                            if(cont == n)
                                break;
                        }
                    } 

                    if(i + 2 < linha){
                        if(jogo[i+1][j] == 'O' && jogo[i+2][j]== '.'){
                            jogo[i][j] = '.';
                            jogo[i+1][j] = '.';
                            jogo[i+2][j] = 'O';
                            cont++;
                            printf("Movimendo b %c%c realizado.\n\n", i+65, j+65);
                            if(cont == n)
                                break;       
                        }
                    }

                    if(j + 2 < coluna){
                        if(jogo[i][j+1] == 'O' && jogo[i][j+2] == '.'){
                            jogo[i][j] = '.';
                            jogo[i][j+1] = '.';
                            jogo[i][j+2] = 'O';
                            cont++;
                            printf("Movimendo d %c%c realizado.\n\n", i+65, j+65);
                            if(cont == n)
                                break;
                        }
                    } 

                    if(j - 2 >= 0){
                        if(jogo[i] [j-1] == 'O' && jogo[i][j-2] == '.'){
                            jogo[i][j] = '.';
                            jogo[i][j-1] = '.';
                            jogo[i][j-2] = 'O';
                            cont++;
                            printf("Movimendo e %c%c realizado.\n\n", i+65, j+65);
                            if(cont == n)
                                break;
                        }
                    }
                          
                }

        
            }
        }
    }
}

void desalocaTudo(int **jogo, int linha, int coluna, Comando *comando, int *jogada){
    //Função pra desalocar tudo que está alocado dinamicamente
    for (int i = 0; i < linha; i++){
        free(jogo[i]);
    }
    free(jogo);
    free(comando);
    free(jogada);
    
}

// '-' = -1
// '.' = 0
// 'O' = 1