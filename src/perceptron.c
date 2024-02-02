#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXIT_SUCCESS 0

char * test_weights(int[], float[], float[], float[], float[], float[], float[], float[], float[], float[], float[], float, float, float, float, float, float, float, float, float, float);
int  * stoia(const char *, const int);
int    stoi(const char *);


/*
	> gcc perceptron.c

	(1) > ./a.out [entrada de teste]
	(2) > ./a.out 
*/
int main(int argc, char **argv) {
	srand(time(NULL));
	int entries[][20] = {
		{-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1}, 		// 0
		{-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1},	// 1
		{-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,1},		// 2
		{-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1},		// 3
		{-1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1},		// 4
		{1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,1},			// 5
		{-1,1,1,-1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,1,1,1,-1},			// 6
		{1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1},		// 7
		{-1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,1,-1},		// 8
		{1,1,1,1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1}				// 9
	};
	int output[][10] = {
		{1,-1,-1,-1,-1,-1,-1,-1,-1,-1},								// 0
		{-1,1,-1,-1,-1,-1,-1,-1,-1,-1},								// 1
		{-1,-1,1,-1,-1,-1,-1,-1,-1,-1},								// 2
		{-1,-1,-1,1,-1,-1,-1,-1,-1,-1},								// 3
		{-1,-1,-1,-1,1,-1,-1,-1,-1,-1},								// 4
		{-1,-1,-1,-1,-1,1,-1,-1,-1,-1},								// 5
		{-1,-1,-1,-1,-1,-1,1,-1,-1,-1},								// 6
		{-1,-1,-1,-1,-1,-1,-1,1,-1,-1},								// 7
		{-1,-1,-1,-1,-1,-1,-1,-1,1,-1},								// 8
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,1}								// 9
	};

	float  *w1  =  (float*) malloc(20 * sizeof(float)); 			// Os 20 pesos do neurônio 1
	float  *w2  =  (float*) malloc(20 * sizeof(float));				// Os 20 pesos do neurônio 2
	float  *w3  =  (float*) malloc(20 * sizeof(float));				// ...
	float  *w4  =  (float*) malloc(20 * sizeof(float));
	float  *w5  =  (float*) malloc(20 * sizeof(float));
	float  *w6  =  (float*) malloc(20 * sizeof(float));
	float  *w7  =  (float*) malloc(20 * sizeof(float));
	float  *w8  =  (float*) malloc(20 * sizeof(float));
	float  *w9  =  (float*) malloc(20 * sizeof(float));
	float  *w10 =  (float*) malloc(20 * sizeof(float));

	for (int i = 0; i < 20; i++) {
        w1[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w2[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w3[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w4[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w5[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w6[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w7[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w8[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w9[i]  = (float)(rand() % 1000) / 1000 - 0.5;
        w10[i] = (float)(rand() % 1000) / 1000 - 0.5;
    }

	float b1  = (float)(rand() % 1000) / 1000 - 0.5;
    float b2  = (float)(rand() % 1000) / 1000 - 0.5;
    float b3  = (float)(rand() % 1000) / 1000 - 0.5;
    float b4  = (float)(rand() % 1000) / 1000 - 0.5;
    float b5  = (float)(rand() % 1000) / 1000 - 0.5;
    float b6  = (float)(rand() % 1000) / 1000 - 0.5;
    float b7  = (float)(rand() % 1000) / 1000 - 0.5;
    float b8  = (float)(rand() % 1000) / 1000 - 0.5;
    float b9  = (float)(rand() % 1000) / 1000 - 0.5;
    float b10 = (float)(rand() % 1000) / 1000 - 0.5;
	int   limit_theta = 0;
	
	float learning_rate = (float)rand() / RAND_MAX;;
	int   cycles = 0;
	bool  changed = true;

	while(changed) {
		changed = false;
		for(int i = 0; i < 10; i++) {
			float y1_in = b1, y2_in = b2, y3_in = b3;
			float y4_in = b4, y5_in = b5, y6_in = b6;
			float y7_in = b7, y8_in = b8, y9_in = b9;
			float y10_in = b10;

			for(int j = 0; j < 20; j++) {
				y1_in  += w1[j]  * entries[i][j];
				y2_in  += w2[j]  * entries[i][j];
				y3_in  += w3[j]  * entries[i][j];
				y4_in  += w4[j]  * entries[i][j];
				y5_in  += w5[j]  * entries[i][j];
				y6_in  += w6[j]  * entries[i][j];
				y7_in  += w7[j]  * entries[i][j];
				y8_in  += w8[j]  * entries[i][j];
				y9_in  += w9[j]  * entries[i][j];
				y10_in += w10[j] * entries[i][j];
			}

			int y1 =  (y1_in >= limit_theta)  ? 1 : -1;
			int y2 =  (y2_in >= limit_theta)  ? 1 : -1;
			int y3 =  (y3_in >= limit_theta)  ? 1 : -1;
			int y4 =  (y4_in >= limit_theta)  ? 1 : -1;
			int y5 =  (y5_in >= limit_theta)  ? 1 : -1;
			int y6 =  (y6_in >= limit_theta)  ? 1 : -1;
			int y7 =  (y7_in >= limit_theta)  ? 1 : -1;
			int y8 =  (y8_in >= limit_theta)  ? 1 : -1;
			int y9 =  (y9_in >= limit_theta)  ? 1 : -1;
			int y10 = (y10_in >= limit_theta) ? 1 : -1;

			if(y1 != output[i][0]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w1[j] += learning_rate * output[i][0] * entries[i][j];
					b1    += learning_rate * output[i][0];
				}
			}

			if(y2 != output[i][1]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w2[j] += learning_rate * output[i][1] * entries[i][j];
					b2    += learning_rate * output[i][1];
				}
			}

			if(y3 != output[i][2]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w3[j] += learning_rate * output[i][2] * entries[i][j];
					b3    += learning_rate * output[i][2];
				}
			}

			if(y4 != output[i][3]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w4[j] += learning_rate * output[i][3] * entries[i][j];
					b4    += learning_rate * output[i][3];
				}
			}

			if(y5 != output[i][4]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w5[j] += learning_rate * output[i][4] * entries[i][j];
					b5    += learning_rate * output[i][4];
				}
			}

			if(y6 != output[i][5]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w6[j] += learning_rate * output[i][5] * entries[i][j];
					b6    += learning_rate * output[i][5];
				}
			}

			if(y7 != output[i][6]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w7[j] += learning_rate * output[i][6] * entries[i][j];
					b7    += learning_rate * output[i][6];
				}
			}

			if(y8 != output[i][7]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w8[j] += learning_rate * output[i][7] * entries[i][j];
					b8    += learning_rate * output[i][7];
				}
			}

			if(y9 != output[i][8]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w9[j] += learning_rate * output[i][8] * entries[i][j];
					b9    += learning_rate * output[i][8];
				}
			}

			if(y10 != output[i][9]) {
				changed = true;
				for(int j = 0; j < 20; j++) {
					w10[j] += learning_rate * output[i][9] * entries[i][j];
					b10    += learning_rate * output[i][9];
				}
			}
		}
		cycles++;
	}

	if(argc > 1) {
		int* test_letter = stoia(argv[1], 20);
		char* result = test_weights(test_letter, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10);
		printf("\nRESULTADO: %s\n", result);
	}
	else {
		printf("Cycles: %d\n\n", cycles);
		printf("Pesos dos Neurônios:\n\n");
		for(int i = 0; i < 20; i++) {
			printf("NEURÔNIO %d\n", i+1);
			printf("[%.2f\t, %.2f\t, %.2f,", w1[i], w2[i], w3[i]);
			printf("\t %.2f\t, %.2f\t, %.2f,", w4[i], w5[i], w6[i]);
			printf("\t %.2f\t, %.2f\t, %.2f\t, %.2f]\n\n", w7[i], w8[i], w9[i], w10[i]);
		}

		printf("BIAS\n\n");
		printf("[%.2f\t, %.2f\t, %.2f,", b1, b2, b3);
		printf("\t %.2f\t, %.2f\t, %.2f,", b4, b5, b6);
		printf("\t %.2f\t, %.2f\t, %.2f\t, %.2f]\n\n", b7, b8, b9, b10);
	}
	/*
	RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
	StringReference *errorMessage = CreateStringReference(L"", 0);

	DrawScatterPlot(imageRef, 600, 400, (double*) x1, 8, (double*) x2, 8, errorMessage); 

	ByteArray *pngData = ConvertToPNG(imageRef->image);
	WriteToFile(pngData, "plot.png");
	*/

	return EXIT_SUCCESS;
}

char* test_weights(int letter[], float w1[], float w2[], float w3[], float w4[], float w5[], float w6[], float w7[], float w8[], float w9[], float w10[], float b1, float b2, float b3, float b4, float b5, float b6, float b7, float b8, float b9, float b10) {
	float y1 = b1, y2 = b2, y3 = b3;
	float y4 = b4, y5 = b5, y6 = b6;
	float y7 = b7, y8 = b8, y9 = b9, y10 = b10;
	float theta = 0;
	for(int i = 0; i < 20; i++) {
		y1  += letter[i]  * w1[i];
		y2  += letter[i]  * w2[i];
		y3  += letter[i]  * w3[i];
		y4  += letter[i]  * w4[i];
		y5  += letter[i]  * w5[i];
		y6  += letter[i]  * w6[i];
		y7  += letter[i]  * w7[i];
		y8  += letter[i]  * w8[i];
		y9  += letter[i]  * w9[i];
		y10 += letter[i]  * w10[i];
	}
	printf("\nY1: %.2f\n Y2: %.2f\n Y3: %.2f", y1, y2, y3);
	printf("\nY4: %.2f\n Y5: %.2f\n Y6: %.2f", y4, y5, y6);
	printf("\nY7: %.2f\n Y8: %.2f\n Y9: %.2f\n Y10: %.2f\n\n", y7, y8, y9, y10);
	
	int y1_r  = (y1 >= theta)  ? 1 : -1;
	int y2_r  = (y2 >= theta)  ? 1 : -1;
	int y3_r  = (y3 >= theta)  ? 1 : -1;
	int y4_r  = (y4 >= theta)  ? 1 : -1;
	int y5_r  = (y5 >= theta)  ? 1 : -1;
	int y6_r  = (y6 >= theta)  ? 1 : -1;
	int y7_r  = (y7 >= theta)  ? 1 : -1;
	int y8_r  = (y8 >= theta)  ? 1 : -1;
	int y9_r  = (y9 >= theta)  ? 1 : -1;
	int y10_r = (y10 >= theta) ? 1 : -1;
	printf("\nY1: %d\n Y2: %d\n Y3: %d", y1_r, y2_r, y3_r);
	printf("\nY4: %d\n Y5: %d\n Y6: %d", y4_r, y5_r, y6_r);
	printf("\nY7: %d\n Y8: %d\n Y9: %d\n Y10: %d\n", y7_r, y8_r, y9_r, y10_r);

	bool is0 = (y1 >= theta)  ? 1 : 0;
	bool is1 = (y2 >= theta)  ? 1 : 0;
	bool is2 = (y3 >= theta)  ? 1 : 0;
	bool is3 = (y4 >= theta)  ? 1 : 0;
	bool is4 = (y5 >= theta)  ? 1 : 0;
	bool is5 = (y6 >= theta)  ? 1 : 0;
	bool is6 = (y7 >= theta)  ? 1 : 0;
	bool is7 = (y8 >= theta)  ? 1 : 0;
	bool is8 = (y9 >= theta)  ? 1 : 0;
	bool is9 = (y10 >= theta) ? 1 : 0;

	if(is0) {
		return "Digito [0]";
	}
	else if(is1) {
		return "Digito [1]";
	}
	else if(is2) {
		return "Digito [2]";
	}
	else if(is3) {
		return "Digito [3]";
	}
	else if(is4) {
		return "Digito [4]";
	}
	else if(is5) {
		return "Digito [5]";
	}
	else if(is6) {
		return "Digito [6]";
	}
	else if(is7) {
		return "Digito [7]";
	}
	else if(is8) {
		return "Digito [8]";
	}
	else if(is9) {
		return "Digito [9]";
	}
	return "Nao reconheceu!";
}

// Converte uma string de um valor numério pertencente aos inteiros
// para um tipo inteiro
// (char*) "1" -> (int) 1
int stoi(const char *value) {
    int v = 0;
    int is_negative = 1;

    if (*(value) == '-') {
        is_negative = -1;
        value++;
    }

    while ( *(value) != '\0' ) {
        int int_value = (int) (*(value++) - '0');
        v = v * 10 + int_value * 10;
    }

    return is_negative * v / 10;
}

// Converte uma string representando um vetor de números inteiros em
// um array de inteiros
// (char*) "[1,1,1,1]" -> (int) [1,1,1,1]
int * stoia(const char *str, const int size) {
    int *array = (int*) malloc(sizeof(int) * size);
    int i = 0;

    while (*str != '\0') {
        if (*str != '[' && *str != ']' && *str != ',') {
            char string_value[2] = {'\0', '\0'};
            if (*str == '-') {
                string_value[0] = '-';
                string_value[1] = *(++str);
            }
            else string_value[0] = *str;
            array[i++] = stoi( string_value );
        }
        str++;
    }
    return array;
}
