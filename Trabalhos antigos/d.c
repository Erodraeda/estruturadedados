#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main(){
int numeros[1000];
int numero;
int i;
int pos;
int numTemp;
FILE *txt;
if((txt = fopen("numeros.txt", "a+")) == NULL) {
printf("Erro ao abrir arquivo");
}
else {
printf("Numeros ja guardados: ");
while (!feof(txt)) {
fscanf (txt, "%d ", &numero);
printf ("%d, ", numero);
}
printf("\n");
for (pos=0; numTemp>=0; pos++){
printf("Insira um numero positivo. Um numero negativo encerrara o processo: ");
scanf("%d", &numTemp);
numeros[pos] = numTemp;
}
printf("\n");
for (i=0; i<pos-1; i++){
fprintf(txt, "%d\n", numeros[i]);
}
fclose(txt);
}
system("pause");
}
