#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAYSIZE 32768
#define SEARCH_ARRAYSIZE 32768

int bubbleSortArray[ARRAYSIZE], insertionSortArray[ARRAYSIZE], binSearchArray[SEARCH_ARRAYSIZE], linSearchArray[SEARCH_ARRAYSIZE];

clock_t start, end;
double cpu_time_used_bubble, cpu_time_used_insertion, cpu_time_used_binary, cpu_time_used_linear, cpu_time_used_recbinary;

int bubbleCounter = 1;
int insertionCounter = 1;
int binaryCounter = 1;
int recbinaryCounter = 1;
int linearCounter = 1;
int binaryFoundCounter = 0;
int recbinaryFoundCounter = 0;
int linearFoundCounter = 0;

void main() {

    int i = 0;

    // Preenche arrays com n�meros existentes no arquivo de texto
    readSortingFiles();

    readSearchingFiles();

    // Contando tempo do bubble sort
    start = clock();
    bubbleSort(bubbleSortArray, ARRAYSIZE);
    end = clock();
    cpu_time_used_bubble = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Contando tempo do insertion sort
    start = clock();
    insertionSort(insertionSortArray, ARRAYSIZE);
    end = clock();
    cpu_time_used_insertion = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Binary Search
    start = clock();
    int binarySearchNumber;
    for (i = 0; i < SEARCH_ARRAYSIZE; i++) {
        int search_number = binSearchArray[i];
        binarySearchNumber = binarySearch(insertionSortArray, ARRAYSIZE/2, ARRAYSIZE, search_number);

        if (binarySearchNumber > -1) binaryFoundCounter++;
    }
    end = clock();
    cpu_time_used_binary = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Recursive Binary Search
    start = clock();
    int recBinarySearchNumber;
    for (i = 0; i < SEARCH_ARRAYSIZE; i++) {
        int search_number = binSearchArray[i];
        recBinarySearchNumber = recursiveBinarySearch(insertionSortArray, ARRAYSIZE/2, ARRAYSIZE, search_number);

        if (recBinarySearchNumber > -1) recbinaryFoundCounter++;
    }
    end = clock();
    cpu_time_used_recbinary = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Linear Search
    start = clock();
    int linearSearchNumber;
    for (i = 0; i < SEARCH_ARRAYSIZE; i++) {
        int search_number = binSearchArray[i];
        linearSearchNumber = linearSearch(insertionSortArray, ARRAYSIZE, search_number);

        if (linearSearchNumber > -1) linearFoundCounter++;
    }
    end = clock();
    cpu_time_used_linear = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Tempo decorrido em cada tipo de sorting

    printf("\n\nListagem de tempos decorridos para cada tipo de ordena��o de %d n�meros: \n", ARRAYSIZE);

    printf("\nBubble sort: %lf segundos, total de chamadas recursivas: %d", cpu_time_used_bubble, bubbleCounter);

    printf("\nInsertion sort: %lf segundos, total de la?os: %d\n", cpu_time_used_insertion, insertionCounter);

    // Tempo decorrido em cada tipo de search

    printf("\n\nListagem de tempos decorridos para cada tipo de busca de %d n�meros: \n", SEARCH_ARRAYSIZE);

    printf("\nRegular Binary search: %lf segundos para encontrar %d de %d numeros. Total de chamadas: %d\n", cpu_time_used_binary, binaryFoundCounter, SEARCH_ARRAYSIZE, binaryCounter);

    printf("\nRecursive Binary search: %lf segundos, total de chamadas recursivas: %d\n", cpu_time_used_recbinary, recbinaryFoundCounter, SEARCH_ARRAYSIZE, recbinaryCounter);

    printf("\nLinear search: %lf segundos, total de la?os: %d\n\n", cpu_time_used_linear, linearFoundCounter, SEARCH_ARRAYSIZE, linearCounter);

    FILE *file;

        if ((file = fopen("results.txt", "a")) == NULL) {
            printf("failed to open file");
        } else {
            fprintf(file, "\n\nListagem de tempos decorridos para cada tipo de ordena��o de %d n�meros: \n", ARRAYSIZE);

            fprintf(file, "\nBubble sort: %lf segundos, total de chamadas recursivas: %d", cpu_time_used_bubble, bubbleCounter);

            fprintf(file, "\nInsertion sort: %lf segundos, total de la?os: %d\n", cpu_time_used_insertion, insertionCounter);

            // Tempo decorrido em cada tipo de search

            fprintf(file, "\n\nListagem de tempos decorridos para cada tipo de busca de %d n�meros: \n", SEARCH_ARRAYSIZE);

            fprintf(file, "\nRegular Binary search: %lf segundos para encontrar %d de %d numeros. Total de chamadas: %d\n", cpu_time_used_binary, binaryFoundCounter, SEARCH_ARRAYSIZE, binaryCounter);

            fprintf(file, "\nRecursive Binary search: %lf segundos, total de chamadas recursivas: %d\n", cpu_time_used_recbinary, recbinaryFoundCounter, SEARCH_ARRAYSIZE, recbinaryCounter);

            fprintf(file, "\nLinear search: %lf segundos, total de la?os: %d\n\n", cpu_time_used_linear, linearFoundCounter, SEARCH_ARRAYSIZE, linearCounter);

            fprintf(file, "-----------------");
        }

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

       	// printf("La?o insertion numero: %d\n", insertionCounter);

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

int binarySearch(int array[], int start, int arraysize, int number) {
    // NIY

    while (start <= arraysize) {
        int m = start + (arraysize - start) / 2;
 
        if (array[m] == number) {
            return m;
        } 
        
        if (array[m] < number) {
            start = m + 1;
        } else {
            arraysize = m - 1;
        }

        binaryCounter++;
    }
 
    // If we reach here, then element was not present
    return -1;

}

int recursiveBinarySearch(int array[], int start, int arraysize, int number) {
    if (arraysize >= start) {
        int mid = start + (arraysize - start) / 2;
  
        if (array[mid] == number)
            return mid;
 
        if (array[mid] > number)
            return binarySearch(array, start, mid - 1, number);
 
        recbinaryCounter++;
        return binarySearch(array, mid + 1, arraysize, number);
    }
 
    return -1;
}

int linearSearch(int array[], int arraysize, int number) {
    
    int i;

    for (i = 0; i < arraysize; i++) { 
        if (array[i] == number) {
            return i;
        }
        linearCounter++;
    }
    return -1;
}

void readSearchingFiles() {

    FILE *file;
    int counter;
    int buffer;
    int *output;
    char fileBuffer[SEARCH_ARRAYSIZE*6];
    char delims[] = ",";
    char *token = NULL;
    if ((file = fopen("searchable.txt", "r")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
        while(!feof(file)){            
            counter = 0;
            fgets(fileBuffer, SEARCH_ARRAYSIZE*6, file);
            token = strtok(fileBuffer, delims);
            while(token != NULL){
                // converts the string token into an integer and puts it into the array
                buffer = strtol(token, &output, 10) + 0;
                linSearchArray[counter] = buffer;
                binSearchArray[counter] = buffer;
                token = strtok(NULL, delims);
                counter++;
            }
        }
    }

}

void readSortingFiles() {

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
                token = strtok(NULL, delims);
                counter++;
            }
        }
    }

}
