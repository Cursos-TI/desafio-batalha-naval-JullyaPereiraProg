#include <stdio.h>

// Código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
int main() {
printf("*** Desafio Batalha Naval - MateCheck *** \n");
    int tabuleiro[10][10] = {0};
    
    // Navio horizontal (linha 2)
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[2][5] = 3;
    
    // Navio vertical (coluna 7)
    tabuleiro[5][7] = 3;
    tabuleiro[6][7] = 3;
    tabuleiro[7][7] = 3;
    
    printf("Tabuleiro:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}