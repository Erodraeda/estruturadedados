#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 255//limite de caracteres de cada linha do arquivo

//struct de Cidade
typedef struct cidadeInfo{
 char uf[3];
 char codUf[3];
 char codMunic[6];
 char nomeMunic[33];// Vila Bela da Santissima Trindade eh a cidade brasileira com o maior nome, tem 32 caracteres contando os espacos.
 char populacao[9];//Sao Paulo tem 15 meloes de habitantes, sao 8 digitos

} Cidade;



Cidade* CriaCidade(char* uf, char* codUf, char* codMunic, char* nomeMunic, char* populacao);

/*sao essas as funcoes que serao chamadas na main*/
int LerCidades();//funcao para ler o arquivo
int InsereCidade(Cidade* cid);




