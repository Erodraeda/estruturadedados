#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Pessoa {
char nome[20];
int idade;
};
int main(void) {
Pessoa Aluno;
Pessoa *AlunoPointer;
AlunoPointer = &Aluno;


AlunoPointer = (struct Pessoa *) malloc(4*sizeof(struct Pessoa));


strcpy((*AlunoPointer).nome, "Janice");
(*AlunoPointer).idade = 22;


strcpy((*(AlunoPointer+1)).nome, "Julia");
(*(AlunoPointer+1)).idade = 22;


strcpy((*(AlunoPointer+2)).nome, "Augusto");
(*(AlunoPointer+2)).idade = 23;


strcpy((*(AlunoPointer+3)).nome, "Alberto");
(*(AlunoPointer+3)).idade = 24;


for (int i = 0; i<4; i++, AlunoPointer++) {
// printf("%s - %d \n", (*(AlunoPointer+i)).nome, (*(AlunoPointer+i)).idade);
printf("%s - %d \n", (*AlunoPointer).nome, (*AlunoPointer).idade);
printf("%s - %d \n", AlunoPointer->nome, AlunoPointer->idade);
}
getchar();
}
