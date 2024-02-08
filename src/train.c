#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Fazer com 4 neurônios (númerio binário)


int  log_weights(float *[], float[]);
void print_result(const int, const float, float *[], float[]);

int main() {
    srand(time(NULL));

    // Definição dos dados de entrada e saída desejados
    int entries[][20] = {
        {-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1},        // 0
        {-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,1},      // 1
        {-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1},         // 2
        {1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1},         // 3
        {-1,1,-1,1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1},       // 4
        {-1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1},         // 5
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

        // Cada entrada deve passar pelos 10 neurônios
        for(int k = 0; k < 10; k++) {
            int *entrie = entries[k];

            for (int i = 0; i < 10; i++) { // Percorre cada neurônio
                float yi_in = b[i];
                for (int j = 0; j < 20; j++) {
                    yi_in += w[i][j] * entrie[j];
                }
                int yi = (yi_in >= limit_theta) ? 1 : -1;

                if(yi != output[k][i]) {
                    changed = true;
                    for(int j = 0; j < 20; j++) {
                        w[i][j] += learning_rate * output[k][i] * entrie[j];
                    }
                    b[i] += learning_rate * output[k][i];
                }
                if(changed) break;
            }
            //if(changed) break;
        }
        cycles++;
    }

    // Gera o arquivo com os pesos para serem
    // usados pelo algoritmo de teste
    log_weights(w, b);

    // Gera a saída dos pesos para o GUI
    print_result(cycles, learning_rate, w, b);

    return EXIT_SUCCESS;
}


void print_result(const int cycles, const float learning_rate, float *w[], float b[]) {
    printf("<h2>Ciclos de treinamento: %d</h2><br>", cycles);
    printf("<h2>Taxa de aprendizado: %.6f</h2><br>", learning_rate);
    printf("<h4>Pesos dos Neurônios</h4><br>");
    for(int i = 0; i < 10; i++) {
        printf("<b>NEURÔNIO %d</b><br>", i+1);
        printf("<p>[%.6f,\t", w[i][0]);
        for(int j = 1; j < 19; j++)
            printf("%.6f,\t", w[i][j]);

        printf("%.6f]</p><br><br>", w[i][19]);
        free(w[i]);
    }

    printf("<h4>BIAS</h4>");
    printf("<p>[%.6f,\t", b[0]);
    for(int i = 1; i < 9; i++)
        printf("%.6f,\t", b[i]);

    printf("%.6f]</p><br>", b[9]);
}

int log_weights(float *w[], float b[]) {
    // Escreve os pesos no arquivo weights.txt
    FILE *fp = fopen("src/temp/weights.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return EXIT_FAILURE;
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

    return EXIT_SUCCESS;
}