#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
bool posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
bool posicionarNavioDiagonalDecrescente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
bool posicionarNavioDiagonalCrescente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
bool verificarPosicoes(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (coordenadas pré-definidas)
    // Navio horizontal - linha 2, coluna 3
    if (!posicionarNavioHorizontal(tabuleiro, 2, 3)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }

    // Navio vertical - linha 5, coluna 7
    if (!posicionarNavioVertical(tabuleiro, 5, 7)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }

    // Navio diagonal decrescente (\) - linha 1, coluna 1
    if (!posicionarNavioDiagonalDecrescente(tabuleiro, 1, 1)) {
        printf("Erro ao posicionar navio diagonal decrescente!\n");
        return 1;
    }

    // Navio diagonal crescente (/) - linha 2, coluna 6
    if (!posicionarNavioDiagonalCrescente(tabuleiro, 2, 6)) {
        printf("Erro ao posicionar navio diagonal crescente!\n");
        return 1;
    }

    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Inicializa todas as posições do tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função auxiliar para verificar se as posições estão livres e dentro do tabuleiro
bool verificarPosicoes(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int delta_linha, int delta_coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i * delta_linha;
        int c = coluna + i * delta_coluna;
        
        // Verifica se está dentro do tabuleiro
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) {
            return false;
        }
        
        // Verifica se a posição já está ocupada
        if (tabuleiro[l][c] != AGUA) {
            return false;
        }
    }
    return true;
}

// Posiciona um navio horizontalmente (da esquerda para direita)
bool posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as posições estão livres
    if (!verificarPosicoes(tabuleiro, linha, coluna, 0, 1)) {
        return false;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
    
    return true;
}

// Posiciona um navio verticalmente (de cima para baixo)
bool posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as posições estão livres
    if (!verificarPosicoes(tabuleiro, linha, coluna, 1, 0)) {
        return false;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
    
    return true;
}

// Posiciona um navio na diagonal decrescente (\)
bool posicionarNavioDiagonalDecrescente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as posições estão livres
    if (!verificarPosicoes(tabuleiro, linha, coluna, 1, 1)) {
        return false;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    
    return true;
}

// Posiciona um navio na diagonal crescente (/)
bool posicionarNavioDiagonalCrescente(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Verifica se as posições estão livres
    if (!verificarPosicoes(tabuleiro, linha, coluna, 1, -1)) {
        return false;
    }
    
    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    
    return true;
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    
    // Cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\nLegenda: 0 = Água, 3 = Navio\n");

 return 0;   
}