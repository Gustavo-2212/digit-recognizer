#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* test_weights(int letter[], float w[][20], float b[]) {
    float y[10];
    float theta = 0;
    char* digit_names[] = {"[0]", "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]"};
    char* result = (char*) malloc(20 * sizeof(char));

    for (int i = 0; i < 10; i++) {
        y[i] = b[i];
        for (int j = 0; j < 20; j++) {
            y[i] += letter[j] * w[i][j];
        }
    }

    printf("<br>");
    printf("<div id=\"output-sup\"> \
    <ul id=\"list-analog\">");
    for(int i = 0; i < 10; i++)
        printf("<li>Y%d: %.6f</li>", i+1, y[i]);
    printf("</ul>");

    printf("<ul id=\"list-digital\">");
    for(int i = 0; i < 10; i++)
        printf("<li>Y%d:\t %d</li>", i+1, ((y[i] >= theta) ? 1 : -1));
    printf("</ul>\
    </div>");

    for (int i = 0; i < 10; i++) {
        if (y[i] >= theta) {
            strcpy(result, "Digito ");
            strcat(result, digit_names[i]);
            return result;
        }
    }

    return "Nao reconheceu!";
}

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
    FILE* fp = fopen("weights.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo weights.txt\n");
        return 1;
    }

    // Lendo os pesos dos neurônios
    float w[10][20];
    float b[10];
    char line[256];
    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *token;
        token = strtok(line, " ");

        int col = 0;
        while (token != NULL && col < 20) {
            if (row < 10) {
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

    return EXIT_SUCCESS;
}
