#include <stdio.h>
#include <stdbool.h>

#define SIZE 7
#define TOTAL_PINOS 32

// Definição do tabuleiro inicial
// -1: Inválido, 1: Pino, 0: Vazio
int tabuleiro[SIZE][SIZE] = {
    {-1, -1,  1,  1,  1, -1, -1},
    {-1, -1,  1,  1,  1, -1, -1},
    { 1,  1,  1,  1,  1,  1,  1},
    { 1,  1,  1,  0,  1,  1,  1},
    { 1,  1,  1,  1,  1,  1,  1},
    {-1, -1,  1,  1,  1, -1, -1},
    {-1, -1,  1,  1,  1, -1, -1}
};

// Estrutura para armazenar o histórico de movimentos
typedef struct {
    int r1, c1, r2, c2;
} Movimento;

Movimento passos[31];
long int tentativas = 0;

//Função para exibir o tabuleiro 
void imprimirTabuleiro() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tabuleiro[i][j] == -1) printf("  ");
            else printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Verifica se a posição está dentro dos limites e é válida
bool ehValido(int r, int c) {
    return (r >= 0 && r < SIZE && c >= 0 && c < SIZE && tabuleiro[r][c] != -1);
}

//Algoritmo: Backtracking
bool resolver(int pinosRestantes) {
    // Artifício para mostrar que o programa está rodando
    tentativas++;
    if (tentativas % 1000000 == 0) {
        printf("Processando... Tentativas: %ld\r", tentativas);
    }

    // Condição de parada: Se resta apenas 1 pino
    if (pinosRestantes == 1) {
        // Verifica se o último pino está no centro (3,3)
        return (tabuleiro[3][3] == 1);
    }

    // Tenta mover cada pino em 4 direções
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (tabuleiro[r][c] == 1) {
                
                // Direções: Cima, Baixo, Esquerda, Direita
                int dr[] = {-1, 1, 0, 0};
                int dc[] = {0, 0, -1, 1};

                for (int i = 0; i < 4; i++) {
                    int mr = r + dr[i];     // Posição do pino a ser "comido"
                    int mc = c + dc[i];
                    int fr = r + 2 * dr[i]; // Posição final (vazia)
                    int fc = c + 2 * dc[i];

                    if (ehValido(fr, fc) && tabuleiro[mr][mc] == 1 && tabuleiro[fr][fc] == 0) {
                        // Faz o movimento
                        tabuleiro[r][c] = 0;
                        tabuleiro[mr][mc] = 0;
                        tabuleiro[fr][fc] = 1;
                        
                        passos[32 - pinosRestantes].r1 = r;
                        passos[32 - pinosRestantes].c1 = c;
                        passos[32 - pinosRestantes].r2 = fr;
                        passos[32 - pinosRestantes].c2 = fc;

                        // Recursão
                        if (resolver(pinosRestantes - 1)) return true;

                        // Backtrack: Desfaz o movimento
                        tabuleiro[r][c] = 1;
                        tabuleiro[mr][mc] = 1;
                        tabuleiro[fr][fc] = 0;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    printf("Resolvendo Resta Um...\n");
    
    if (resolver(TOTAL_PINOS)) {
        printf("\n\nSolucao encontrada com sucesso!\n");
        printf("Sequencia de movimentos (Linha, Coluna):\n");
        printf("----------------------------------------\n");
        for (int i = 0; i < 31; i++) {
            printf("%02d: (%d,%d) -> (%d,%d)\n", i + 1, 
                   passos[i].r1, passos[i].c1, passos[i].r2, passos[i].c2);
        }
    } else {
        printf("\nNao foi possivel encontrar uma solucao.\n");
    }

    return 0;
}