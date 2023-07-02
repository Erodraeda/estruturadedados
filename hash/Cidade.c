#include "Cidade.h"




//pega cada linha do csv e transforma em um objeto dentro da memoria, provando que C pode ser orietado a objetos
Cidade* CriaCidade(char* uf, char* codUf, char* codMunic, char* nomeMunic, char* populacao){
	Cidade* novaCidade = (Cidade*)malloc(sizeof(Cidade));
	strcpy(novaCidade->uf, uf);
    strcpy(novaCidade->codUf, codUf);
    strcpy(novaCidade->codMunic, codMunic);
    strcpy(novaCidade->nomeMunic, nomeMunic);
    strcpy(novaCidade->populacao, populacao);
    return novaCidade;
}



int LerCidades() {
    FILE *file = fopen("cidades.csv", "r");//nao esqueca de ter escrito aqui da mesma maneira que seu arquivo esta nomeado no OS
    if (file == NULL) {
        printf("Deu ruim!.\n");
        system("pause");
        system("exit");        
    }
	int a;
	
    char buf[MAX_STR_LEN];//buffer para cada linha do csv
    char *tmp;
    int i = 0, count = 0;
    while (fgets(buf, MAX_STR_LEN, file) != NULL) {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n')) {
            buf[strlen(buf) - 1] = '\0';
        }
        
		/*corta cada coluna, se orientando pelas virgulas*/
        tmp = strtok(buf, ",");
        char uf[3];
        strcpy(uf, tmp);

        tmp = strtok(NULL, ",");
        char codUf[3];
        strcpy(codUf, tmp);

        tmp = strtok(NULL, ",");
        char codMunic[6];
        strcpy(codMunic, tmp);    

        tmp = strtok(NULL, ",");
        char nomeMunic[33];
        strcpy(nomeMunic, tmp);

        tmp = strtok(NULL, ",");
        char populacao[9];
        strcpy(populacao, tmp);
        
        if(count == 0){/*ignora a primeira linha do arquivo*/
        	count++;
		}
		else{
			Cidade* novaCidade = CriaCidade(uf, codUf, codMunic, nomeMunic, populacao);
			InsereCidade(novaCidade);
		}       	
    }

    fclose(file);
    return 0;
}

int InsereCidade(Cidade* cid)
{
	printf("\n %s %s %s %s %s", cid->uf, cid->codUf, cid->codMunic, cid->nomeMunic, cid->populacao);
	
	return 1;
}





