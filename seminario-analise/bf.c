#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

// ========== FUNÇÕES AUXILIARES ==========

// Função para trocar dois inteiros
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para calcular a distância total de um caminho
int calculatePathDistance(int caminho[], int n, int distancia[n][n]) {
    int distancia_total = 0;

    for (int i = 0; i < n - 1; i++) {
        distancia_total += distancia[caminho[i]][caminho[i+1]];
    }

    // Adiciona a distância de volta à cidade inicial
    distancia_total += distancia[caminho[n-1]][caminho[0]];

    return distancia_total;
}

// Função principal de força bruta (backtracking)
void tspForcaBruta(int caminho[], int start, int end, int *distancia_min, int melhor_caminho[], int n, int distancia[n][n]) {
    if (start == end) {
        int distancia_atual = calculatePathDistance(caminho, n, distancia);

        if (distancia_atual < *distancia_min) {
            *distancia_min = distancia_atual;

            for (int i = 0; i < n; i++) {
                melhor_caminho[i] = caminho[i];
            }
        }

        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&caminho[start], &caminho[i]);
        tspForcaBruta(caminho, start + 1, end, distancia_min, melhor_caminho, n, distancia);
        swap(&caminho[start], &caminho[i]); // Backtrack
    }
}

// ========== DEFINIÇÃO DOS GRAFOS ==========

// Grafo 1: 3 cidades
#define N1 5

int g1[N1][N1] = {
    {0, 12, 10, 19, 8},
    {12, 0, 3, 7, 2},
    {10, 3, 0, 6, 20},
    {19, 7, 6, 0, 4},
    {8, 2, 20, 4, 0}
};

// Grafo 4: 6 cidades
#define N2 8

int g2[N2][N2] = {
    {0, 12, 18, 5, 21, 9, 14, 7},
    {12, 0, 6, 15, 30, 11, 8, 3},
    {18, 6, 0, 9, 22, 19, 4, 13},
    {5, 15, 9, 0, 17, 10, 25, 16},
    {21, 30, 22, 17, 0, 8, 20, 28},
    {9, 11, 19, 10, 8, 0, 7, 14},
    {14, 8, 4, 25, 20, 7, 0, 12},
    {7, 3, 13, 16, 28, 14, 12, 0}
};

#define N3 10

int g3[N3][N3] = {
    {0, 5, 8, 12, 7, 15, 20, 9, 11, 3},
    {5, 0, 6, 9, 4, 18, 14, 7, 10, 2},
    {8, 6, 0, 11, 5, 13, 17, 8, 12, 4},
    {12, 9, 11, 0, 8, 6, 10, 15, 7, 13},
    {7, 4, 5, 8, 0, 12, 16, 6, 9, 5},
    {15, 18, 13, 6, 12, 0, 5, 11, 8, 14},
    {20, 14, 17, 10, 16, 5, 0, 13, 4, 18},
    {9, 7, 8, 15, 6, 11, 13, 0, 10, 8},
    {11, 10, 12, 7, 9, 8, 4, 10, 0, 9},
    {3, 2, 4, 13, 5, 14, 18, 8, 9, 0}
};

#define N4 11

int g4[N4][N4] = {
    {0, 12, 45, 23, 67, 34, 89, 56, 21, 78, 43},
    {12, 0, 33, 87, 42, 91, 24, 76, 55, 38, 80},
    {45, 33, 0, 65, 18, 77, 52, 29, 84, 47, 11},
    {23, 87, 65, 0, 49, 26, 73, 40, 95, 58, 22},
    {67, 42, 18, 49, 0, 61, 37, 92, 54, 28, 83},
    {34, 91, 77, 26, 61, 0, 48, 13, 79, 44, 97},
    {89, 24, 52, 73, 37, 48, 0, 68, 35, 99, 64},
    {56, 76, 29, 40, 92, 13, 68, 0, 74, 31, 86},
    {21, 55, 84, 95, 54, 79, 35, 74, 0, 69, 16},
    {78, 38, 47, 58, 28, 44, 99, 31, 69, 0, 57},
    {43, 80, 11, 22, 83, 97, 64, 86, 16, 57, 0}
};

#define N5 12

int g5[N5][N5] = {
    {0, 15, 40, 25, 60, 35, 80, 50, 20, 75, 45, 85},
    {15, 0, 35, 80, 45, 90, 25, 70, 50, 40, 75, 30},
    {40, 35, 0, 60, 20, 75, 50, 30, 80, 45, 10, 95},
    {25, 80, 60, 0, 50, 30, 70, 45, 95, 55, 25, 80},
    {60, 45, 20, 50, 0, 65, 40, 95, 55, 30, 85, 50},
    {35, 90, 75, 30, 65, 0, 55, 15, 85, 50, 100, 35},
    {80, 25, 50, 70, 40, 55, 0, 65, 30, 98, 60, 20},
    {50, 70, 30, 45, 95, 15, 65, 0, 75, 35, 90, 55},
    {20, 50, 80, 95, 55, 85, 30, 75, 0, 70, 18, 92},
    {75, 40, 45, 55, 30, 50, 98, 35, 70, 0, 60, 25},
    {45, 75, 10, 25, 85, 100, 60, 90, 18, 60, 0, 65},
    {85, 30, 95, 80, 50, 35, 20, 55, 92, 25, 65, 0}
};

// ========== FUNÇÃO PARA EXECUTAR TSP EM UM GRAFO ==========
void rodaTSP(int n, int distancia[n][n], const char *grafoNome) {
    int caminho[n], melhor_caminho[n];
    int distancia_min = INT_MAX;
    
    // Inicializa o caminho com a ordem padrão (0, 1, 2, ..., n-1)
    for (int i = 0; i < n; i++) {
        caminho[i] = i;
    }

    // clock_t start = clock();
    tspForcaBruta(caminho, 0, n - 1, &distancia_min, melhor_caminho, n, distancia);
    // clock_t end = clock();

    printf("\n=== %s (n=%d) ===\n", grafoNome, n);
    printf("Melhor rota: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", melhor_caminho[i]);
    }
    printf("%d\n", melhor_caminho[0]);
    printf("Distância total: %d\n", distancia_min);
}

// ========== MAIN (COM PARÂMETROS DO TERMINAL) ==========
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero_do_grafo>\n", argv[0]);
        printf("Opções:\n");
        printf("  1 - Grafo com 5 cidades\n");
        printf("  2 - Grafo com 8 cidades\n");
        printf("  3 - Grafo com 10 cidades\n");
        printf("  4 - Grafo com 11 cidades\n");
        printf("  5 - Grafo com 12 cidades\n");
        printf("Exemplo: %s 1\n", argv[0]);

        return 1;
    }

    int num_grafo = atoi(argv[1]);

    switch (num_grafo) {
        case 1:
            rodaTSP(N1, g1, "Grafo 1");

            break;
        case 2:
            rodaTSP(N2, g2, "Grafo 2");

            break;
        case 3:
            rodaTSP(N3, g3, "Grafo 3");

            break;
        case 4:
            rodaTSP(N4, g4, "Grafo 4");

            break;
        case 5:
            rodaTSP(N5, g5, "Grafo 5");

            break;
        default:
            printf("Erro: Grafo inválido! Use 1, 2, 3, 4 ou 5.\n");

            return 1;
    }

    return 0;
}