#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main(){
char nome[50];
int idade;
FILE *txt;
if((txt = fopen("dados2.txt", "a+")) == NULL) {
printf("Erro ao abrir arquivo");
}
else {
printf("Digite seu nome: ");
scanf("%s", &nome);
printf("Digite sua idade: ");
scanf("%d", &idade);
fprintf(txt, "%s, %d\n", nome, idade);
printf("Nome '%s', de idade '%d' adicionado a lista", nome, idade);
fclose(txt);
}
system("pause");
}
