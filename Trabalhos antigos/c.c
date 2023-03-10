#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main(){
int codigo;
char empresa[15];
char sobrenome[20];
char nome[20];
char cargo[20];
FILE *txt;
if((txt = fopen("arquivo.txt", "r")) == NULL) {
printf("Erro ao abrir arquivo");
}
else {
while (!feof(txt)) {
fscanf (txt, "%d %s %s %s %s ", &codigo, empresa, sobrenome, nome, cargo);
printf ("%-2d \t %-15s %-20s %-20s %-20s\n", codigo, empresa, sobrenome, nome, cargo);
}
fclose(txt);
}
system("pause");
}
