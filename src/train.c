#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main() {
    srand(time(NULL));

    // Definição dos dados de entrada e saída desejados
    int entries[][20] = {
        {-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1},        // 0
        {-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,1},      // 1
        {-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1},         // 2
        {1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1},         // 3
        {-1,1,-1,1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1},       // 4
        {1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1},         // 5
        {-1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,1},          // 6
        {1,1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,-1},       // 7
        {-1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,-1,1,-1,1,1,1},           // 8
        {1,1,1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1}           // 9
    };
    int output[][10] = {
        {1,-1,-1,-1,-1,-1,-1,-1,-1,-1},                          // 0
        {-1,1,-1,-1,-1,-1,-1,-1,-1,-1},                          // 1
        {-1,-1,1,-1,-1,-1,-1,-1,-1,-1},                          // 2
        {-1,-1,-1,1,-1,-1,-1,-1,-1,-1},                          // 3
        {-1,-1,-1,-1,1,-1,-1,-1,-1,-1},                          // 4
        {-1,-1,-1,-1,-1,1,-1,-1,-1,-1},                          // 5
        {-1,-1,-1,-1,-1,-1,1,-1,-1,-1},                          // 6
        {-1,-1,-1,-1,-1,-1,-1,1,-1,-1},                          // 7
        {-1,-1,-1,-1,-1,-1,-1,-1,1,-1},                          // 8
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,1}                           // 9
    };

    float *w[10]; // Vetor de ponteiros para os pesos
    float b[10];  // Vetor para os pesos de bias

    // Aloca e inicializa os pesos
    for (int i = 0; i < 10; i++) {
        w[i] = (float*) malloc(20 * sizeof(float));
        for (int j = 0; j < 20; j++) {
            w[i][j] = (float)(rand() % 1000) / 1000 - 0.5;
        }
        b[i] = (float)(rand() % 1000) / 1000 - 0.5;
    }

    // Configuração do treinamento
    float learning_rate = (float)rand() / RAND_MAX;
    int   limit_theta = 0;
    int   cycles = 0;
    bool  changed = true;

    // Treinamento do perceptron
    while (changed) {
        changed = false;
        for (int i = 0; i < 10; i++) {
            float yi_in = b[i];
            for (int j = 0; j < 20; j++) {
                yi_in += w[i][j] * entries[i][j];
            }
            int yi = (yi_in >= limit_theta) ? 1 : -1;

            for (int j = 0; j < 20; j++) {
                if (yi != output[i][i]) {
                    changed = true;
                    w[i][j] += learning_rate * output[i][i] * entries[i][j];
                    b[i]    += learning_rate * output[i][i];
                }
            }
        }
        cycles++;
    }

    // Escreve os pesos no arquivo weights.txt
    FILE *fp = fopen("weights.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escreve os pesos no arquivo
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 20; j++) {
            fprintf(fp, "%.6f ", w[i][j]);
        }
        fprintf(fp, "\n");
    }
    for(int i = 0; i < 10; i++) {
        fprintf(fp, "%.6f ", b[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);

    printf("Ciclos de treinamento: %d\n\n", cycles);
    printf("Pesos dos Neuronios:\n\n");
    for(int i = 0; i < 10; i++) {
        printf("NEURONIO %d\n", i+1);
        printf("[%.6f,\t", w[i][0]);
        for(int j = 1; j < 19; j++)
            printf("%.6f,\t", w[i][j]);

        printf("%.6f]\n\n", w[i][19]);
        free(w[i]);
    }

    printf("BIAS\n");
    printf("[%.6f,\t", b[0]);
    for(int i = 1; i < 9; i++)
        printf("%.6f,\t", b[i]);

    printf("%.6f]\n\n", b[9]);

    return EXIT_SUCCESS;
}
