#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Funcionario {
    char nome[30];
    char sobrenome[30];
    float salario;
};

void fillArrays();
void fillArray();
void printArray();
float avgSalary();

int lastFuncionario = 0;
float avgsalary = 0;

struct Funcionario funcionarios[10];

int main() {

    fillArrays();

    printf("\n ----- \n");

    printArray();

    printf("\n ----- \n");

    fillArray();

    printf("\n ----- \n");

    printArray();

    printf("\n ----- \n");

    int avg = avgSalary();

    printf(" Média salarial: %d", avg);

    printf("\n ----- \n");

}

void fillArrays() {

    struct Funcionario func1 = {"João", "Vincente", 1200};
    funcionarios[lastFuncionario] = func1;
    lastFuncionario++;

    struct Funcionario func2 = {"Pedro", "Silva", 1200};
    funcionarios[lastFuncionario] = func2;
    lastFuncionario++;

    struct Funcionario func3 = {"Matheus", "Salamandra", 1200};
    funcionarios[lastFuncionario] = func3;
    lastFuncionario++;

    struct Funcionario func4 = {"Jorge", "Salve", 1200};
    funcionarios[lastFuncionario] = func4;
    lastFuncionario++;

    struct Funcionario func5 = {"Suzana", "Anandra", 1200};
    funcionarios[lastFuncionario] = func5;
    lastFuncionario++;

    struct Funcionario func6 = {"Juliana", "Viana", 1200};
    funcionarios[lastFuncionario] = func6;
    lastFuncionario++;

    struct Funcionario func7 = {"Ana Paula", "Pacheco", 1200};
    funcionarios[lastFuncionario] = func7;
    lastFuncionario++;


}

void fillArray() {

    struct Funcionario func;

    printf(" Insira o nome do funcionário: ");
    gets(func.nome);

    printf(" Insira o sobrenome do funcionário: ");
    gets(func.sobrenome);

    printf(" Insira o salario do funcionário: ");
    scanf("%f", &func.salario);

    printf(" Nome do novo funcionario: %s\n", func.nome);
    printf(" Sobrenome do novo funcionario: %s\n", func.sobrenome);
    printf(" Salario do novo funcionario: %f\n", func.salario);

    funcionarios[lastFuncionario] = func;
    lastFuncionario++;

}

void printArray() {

    for (int i = 0; i < 10; i++) {
        printf(" Nome do funcionario %d: %s\n", i+1, funcionarios[i].nome);
        printf(" Sobrenome do funcionario %d: %s\n", i+1, funcionarios[i].sobrenome);
        printf(" Salario do funcionario %d: %f\n", i+1, funcionarios[i].salario);
    }

}

float avgSalary() {

    for (int i = 0; i < 10; i++) {
        avgsalary += funcionarios[i].salario;
    }

    float avgBuff = avgsalary / lastFuncionario;

    return avgBuff;

}