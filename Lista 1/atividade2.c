#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arraySize = 0;
int totalAvg = 0;

#define maxValue 100;

int *array;

void getArraySize();
void calcAvg();
void printArray();

int main() {

    getArraySize();

    printf("\n ----- \n");

    array = malloc(arraySize*sizeof(int));

    printf("%d", arraySize*sizeof(int));

    fillArray();

    printf("\n ----- \n");

    calcAvg();

    printArray();

    free(array);

    return 0;

}

void getArraySize() {

    printf(" Insira tamanho do array: ");
    scanf("%d", &arraySize);

}

void fillArray() {

    int buffer = 0;

    for (int i = 0; i < arraySize; i++) {

        buffer = rand() % maxValue;

        printf("%d\n", buffer);

        array[i] = buffer;

    }

}

void calcAvg() {

    int buffer = 0;

    for (int i = 0; i < arraySize; i++) {

        buffer += array[i];

    }

    totalAvg = buffer / arraySize;

    printf(" Avg: %d\n", totalAvg);

}

void printArray() {

    for (int i = 0; i < arraySize; i++) {
        printf("numero %d: %d \n", i+1, array[i]);
    }


}