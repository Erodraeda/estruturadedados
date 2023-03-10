// Lucas Walter Marquardt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void sortNumbers (int *numbers, int qnt);
void writeFile (int *numbers, int qnt);
int main (int argc, char* argv[]) {


int qnt = 1;


int *numbers = malloc(1 * sizeof(int));


FILE *p;
int a = 0;
if (!(p=fopen("numeros.txt","r"))){
printf("Arquivo nao encontrado\n");
exit(1);
} else {
printf("Reading...\n");
while (fscanf(p, "%d\n", &numbers[a]) != EOF){
a++;
qnt++;
printf("Read\n");
numbers = realloc(numbers, qnt * sizeof(int));
printf("Saved\n");
}


}


fclose(p);


sortNumbers(numbers, qnt);


}
void sortNumbers (int *numbers, int qnt) {
printf("Sorting...\n");
int i, j, aux;


for (i = 1; i < qnt; i++) {
aux = numbers[i];
j = i - 1;
while ((aux<numbers[j]) && (j>=0)){
numbers[j+1] = numbers[j];
j = j - 1;
}
numbers[j+1] = aux;
}




writeFile(numbers, qnt);
}
void writeFile (int *numbers, int qnt) {
printf("Writing...\n");
FILE *p;
int i;
if (!(p=fopen("numeros_ordenados.txt","w"))){
printf("Arquivo nao encontrado\n");
exit(1);
};


for(i = 0; i<qnt-1; i++) {
fprintf(p, "%d\n", numbers[i]);
}


fclose(p);
free(numbers);


}

