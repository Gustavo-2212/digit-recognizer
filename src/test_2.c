#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* test_weights(const int[], const float[][20], const float[]);
void  print_values(const float[], const float);

int main(int argc, char* argv[]) {
    if (argc <= 1)
        return 1;

    int letter[20];
    char* token = strtok(argv[1], ",");
    int i = 0;
    while (token != NULL && i < 20) {
        letter[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }

    // Abrindo o arquivo weights.txt
    FILE* fp = fopen("src/temp/weights_2.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo weights.txt\n");
        return 1;
    }

    // Lendo os pesos dos neurônios
    float w[4][20];
    float b[4];
    char line[256];
    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *token;
        token = strtok(line, " ");

        int col = 0;
        while (token != NULL && col < 20) {
            if (row < 4) {
                w[row][col] = atof(token);
            } else {
                b[col] = atof(token);
            }
            token = strtok(NULL, " ");
            col++;
        }
        row++;
    }
    fclose(fp);
    
    // Calculando os valores de saída com base nos pesos
    char* result = test_weights(letter, w, b);
    printf("<div id=\"output-inf\">");
    printf("<h3>RESULTADO: %s</h3>", result);
    printf("</div>");

    free(token);
    free(result);
    return EXIT_SUCCESS;
}

char* test_weights(const int letter[], const float w[][20], const float b[]) {
    float y[4], yi[4];
    float theta = 0;
    char* digit_names[] = {"[0]", "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]"};
    char* result = (char*) malloc(20 * sizeof(char));

    for (int i = 0; i < 4; i++) {
        y[i] = b[i];
        for (int j = 0; j < 20; j++) {
            y[i] += letter[j] * w[i][j];
        }
        yi[i] = (y[i] >= theta) ? 1 : 0;
    }

    print_values(y, theta);

    int value = yi[0] * 8 + yi[1] * 4 + yi[2] * 2 + yi[3] * 1;

    if(value >= 0 && value <= 10) {
        strcpy(result, "Digito ");
        strcat(result, digit_names[value]);
        return result;
    }

    free(result);
    return "Nao reconheceu!\0";
}

void print_values(const float y[], const float theta) {
    printf("<br>");
    printf("<div id=\"output-sup\"> \
    <ul id=\"list-analog\">");
    for(int i = 0; i < 4; i++)
        printf("<li>Y%d: %.6f</li>", i+1, y[i]);
    printf("</ul>");

    printf("<ul id=\"list-digital\">");
    for(int i = 0; i < 4; i++)
        printf("<li>Y%d:\t %d</li>", i+1, ((y[i] >= theta) ? 1 : -1));
    printf("</ul>\
    </div>");
}
