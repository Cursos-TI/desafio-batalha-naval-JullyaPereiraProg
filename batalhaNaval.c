#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Constantes do jogo
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, bool horizontal);
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                      int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                      int centro_linha, int centro_coluna);
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]);

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (coordenadas pré-definidas)
    posicionarNavio(tabuleiro, 2, 3, true);   // Navio horizontal
    posicionarNavio(tabuleiro, 5, 7, false);  // Navio vertical

    // Matrizes para as habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    // Cria os padrões das habilidades
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Aplica as habilidades ao tabuleiro (coordenadas pré-definidas)
    aplicarHabilidade(tabuleiro, cone, 4, 4);      // Cone no centro
    aplicarHabilidade(tabuleiro, cruz, 1, 1);      // Cruz no canto superior esquerdo
    aplicarHabilidade(tabuleiro, octaedro, 7, 8);  // Octaedro próximo ao navio vertical

    // Exibe o tabuleiro com os navios e áreas de habilidade
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Inicializa todas as posições do tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona um navio (horizontal ou vertical)
bool posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, bool horizontal) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = horizontal ? linha : linha + i;
        int c = horizontal ? coluna + i : coluna;
        
        // Verifica limites do tabuleiro
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) {
            return false;
        }
        
        tabuleiro[l][c] = NAVIO;
    }
    return true;
}

// Cria o padrão de habilidade em Cone (triângulo apontando para baixo)
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        int largura = i + 1;  // A largura aumenta a cada linha
        int inicio = (TAM_HABILIDADE - largura) / 2;
        
        for (int j = inicio; j < inicio + largura; j++) {
            if (j >= 0 && j < TAM_HABILIDADE) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Cria o padrão de habilidade em Cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        habilidade[centro][i] = 1;  // Linha horizontal central
        habilidade[i][centro] = 1;  // Coluna vertical central
    }
}

// Cria o padrão de habilidade em Octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        int distancia = centro - abs(centro - i);
        for (int j = centro - distancia; j <= centro + distancia; j++) {
            if (j >= 0 && j < TAM_HABILIDADE) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Aplica uma habilidade ao tabuleiro, centrada nas coordenadas especificadas
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                     int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                     int centro_linha, int centro_coluna) {
    int offset = TAM_HABILIDADE / 2;
    
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linha_tab = centro_linha - offset + i;
                int coluna_tab = centro_coluna - offset + j;
                
                // Verifica se está dentro do tabuleiro
                if (linha_tab >= 0 && linha_tab < TAM_TABULEIRO && 
                    coluna_tab >= 0 && coluna_tab < TAM_TABULEIRO) {
                    // Marca apenas se não for navio (para visualização)
                    if (tabuleiro[linha_tab][coluna_tab] != NAVIO) {
                        tabuleiro[linha_tab][coluna_tab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro de Batalha Naval com Habilidades:\n");
    
    // Cabeçalho das colunas
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Linhas do tabuleiro
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    printf("\nLegenda:\n");
    printf("%2d = Água\n", AGUA);
    printf("%2d = Navio\n", NAVIO);
    printf("%2d = Área de Habilidade\n", HABILIDADE);
    
    // Exibe os padrões das habilidades separadamente
    printf("\nPadrões das Habilidades:\n");
    
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    criarHabilidadeCone(cone);
    printf("\nCone:\n");
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", cone[i][j]);
        }
        printf("\n");
    }
    
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    criarHabilidadeCruz(cruz);
    printf("\nCruz:\n");
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", cruz[i][j]);
        }
        printf("\n");
    }
    
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    criarHabilidadeOctaedro(octaedro);
    printf("\nOctaedro:\n");
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", octaedro[i][j]);
        }
        printf("\n");
    }

 return 0;   
}