#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    char nome[30];
    char *marca;
    float preco;
};

float raisePrice(float preco);
void printStruct(struct Produto prod);

int main() {

    struct Produto prod1 = {"Arroz", "Branco", 20};

    prod1.preco = raisePrice(prod1.preco);

    printStruct(prod1);

    struct Produto prod2 = {"Feijão", "Carioquinha", 25};

    prod2.preco = raisePrice(prod2.preco);

    printStruct(prod2);

}

float raisePrice(float preco) {

    float buff = preco * 1.1;

    return buff;

}

void printStruct(struct Produto prod) {

    printf(" Nome do produto: %s\n", prod.nome);
    printf(" Marca do produto: %s\n", prod.marca);
    printf(" Preco do produto: %.2f\n", prod.preco);
    printf(" ----- \n");

}