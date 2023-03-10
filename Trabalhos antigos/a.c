
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main(){
char nome[50];
FILE *txt;
if((txt = fopen("dados.txt", "a+")) == NULL) {
printf("Erro ao abrir arquivo");
}
else {
printf("Digite um nome: ");
scanf("%s", &nome);
fprintf(txt, "%s\n", nome);
printf("Nome '%s' adicionado a lista", nome);
fclose(txt);
}
system("pause");
}
