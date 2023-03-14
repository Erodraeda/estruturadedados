#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array1[10];
int array2[10];

int counter = 0;

void fillFirstArray();
void fillSecondArray();
void printArray(int array[]);

int main() {

    fillFirstArray();

    printf("\n ----- \n");

    fillSecondArray();

    printf("\n ----- \n");

    printArray(array2);

    return 0;

}

void fillFirstArray() {

    int buffer;

    for (int i = 0; i < 10; i++) {
        printf("\n insira um numero: ");
        scanf("%d", &buffer);
        printf("\n -- numero inserido: %d", buffer);
        array1[i] = buffer;
    }

}

void fillSecondArray() {

    int buffer;

    for (int i = 0; i < 10; i++) {
        if (array1[i] %2 == 0) {
            printf(" numero par");
            printf("\n -- numero inserido: %d", array1[i]);
            array2[counter] = array1[i];
            counter++;
        } else {
            printf("\n numero impar, não inserido - %d", array1[i]);
        }
    }

}

void printArray(int array[]) {

    int i = 0;

    do {
        printf("numero %d: %d \n", i+1, array[i]);
        i++;
    } while (array[i] != '\0');

}