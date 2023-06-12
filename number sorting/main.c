#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAYSIZE 131072

int bubbleSortArray[ARRAYSIZE], insertionSortArray[ARRAYSIZE], binSearchSortArray[ARRAYSIZE], linSearchSortArray[ARRAYSIZE], array[ARRAYSIZE];

clock_t start, end;
double cpu_time_used_bubble, cpu_time_used_insertion, cpu_time_used_binary, cpu_time_used_linear;

int bubbleCounter = 1;
int insertionCounter = 1;
//int buffer[8096];

void main() {

    int i = 0;

    // Preenche arrays com números existentes no arquivo de texto

    readFile();

    // Contando tempo do bubble sort
    start = clock();
    bubbleSort(bubbleSortArray, ARRAYSIZE);
    end = clock();
    cpu_time_used_bubble = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Printando os valores ordenados por bubble sort
    printf("\nArray ordenado por Bubble Sorting:\n");

    printArray(bubbleSortArray);

    // Contando tempo do insertion sort
    start = clock();
    insertionSort(insertionSortArray, ARRAYSIZE);
    end = clock();
    cpu_time_used_insertion = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Printando os valores ordenados por insertion sort
    printf("\nArray ordenado por Insertion Sorting:\n");

    printArray(insertionSortArray);

    // Tempo decorrido em cada tipo de sorting

    printf("\n\nListagem de tempos decorridos para cada tipo de ordenação de %d números: \n", ARRAYSIZE);

    printf("\nBubble sort: %lf segundos, total de chamadas recursivas: %d", cpu_time_used_bubble, bubbleCounter);

    printf("\nInsertion sort: %lf segundos, total de la�os: %d\n", cpu_time_used_insertion, insertionCounter);

}

void printArray(int buffArray[]) {
    int i;
    for (i = 0; i < ARRAYSIZE; i++) {
        if (i != ARRAYSIZE -1) {
            printf("%d, ",buffArray[i]);
        } else {
            printf("%d",buffArray[i]);
        }
    }
}

//void bubble(int buffArray[], int length) {
//
//    bubbleCounter++;
//    printf("Chamada bubble numero: %d\n", bubbleCounter);
//	int x;
//	if (length == 1) return;
//    if (buffArray[1] < buffArray[0]) {
//    	x = buffArray[0];
//    	buffArray[0] = buffArray[1];
//    	buffArray[1] = x;
//	}
//    bubble(buffArray + 1, length - 1);
//}
//
//void bubbleSort(int buffArray[], int length) {
//	if (length == 1) return;
//    bubble(buffArray, length);
//    bubbleSort(buffArray, length-1);
//}

void bubbleSort(int buffArray[], int length) {

    int buff, i;

    //    printf("Chamada bubble numero: %d\n", bubbleCounter);

    if (length == 1){
        return;
    }
    for (i = 0; i < length - 1; i++){
        if (buffArray[i] > buffArray[i + 1]){
            buff = buffArray[i];
            buffArray[i] = buffArray[i + 1];
            buffArray[i + 1] = buff;
        }
    }
    length = length - 1;
    bubbleCounter++;
    bubbleSort(buffArray, length);

}

void insertionSort(int buffArray[], int length) {
    int i, key, j;
    for (i = 1; i < length; i++) {

       	// printf("La�o insertion numero: %d\n", insertionCounter);

        key = buffArray[i];
        j = i - 1;

        while (j >= 0 && buffArray[j] > key) {

            buffArray[j + 1] = buffArray[j];

            j = j - 1;

        }
        
        insertionCounter++;

        buffArray[j + 1] = key;

    }
}

void binarySearch() {
    // NIY
}

void linearSearch() {
    // NIY
}

void readFile() {

    FILE *file;
    int counter;
    int buffer;
    int *output;
    char fileBuffer[ARRAYSIZE*6];
    char delims[] = ",";
    char *token = NULL;
    if ((file = fopen("numb.txt", "r")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
        while(!feof(file)){            
            counter = 0;
            fgets(fileBuffer, ARRAYSIZE*6, file);
            token = strtok(fileBuffer, delims);
            while(token != NULL){
                // converts the string token into an integer and puts it into the array
                buffer = strtol(token, &output, 10) + 0;
                bubbleSortArray[counter] = buffer;
                insertionSortArray[counter] = buffer;
                binSearchSortArray[counter] = buffer;
                linSearchSortArray[counter] = buffer;
                token = strtok(NULL, delims);
                counter++;
            }
        }
    }

}