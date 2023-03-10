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
int numPessoas = 0;
int checagem = 1;


AlunoPointer = (struct Pessoa *) malloc(sizeof(struct Pessoa));


do{
printf("Informe o nome do aluno: ");
scanf("%s", &((AlunoPointer)+numPessoas)->nome);
printf("Informe a idade do aluno: ");
scanf("%d", &((AlunoPointer)+numPessoas)->idade);


numPessoas++;


printf("Deseja inserir mais um aluno?\n | Sim - 1 | Nao - 0: ");
scanf("%d", &checagem);




} while (checagem != 0);




for (int i = 0; i<numPessoas; i++, AlunoPointer++) {
printf("%s - %d \n", AlunoPointer->nome, AlunoPointer->idade);
}
getchar();
}
