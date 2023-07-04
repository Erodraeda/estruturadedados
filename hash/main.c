#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_NAME 33
#define MAX_ID 10
#define TABLE_SIZE 5570
#define MAX_STR_LEN 255

typedef struct {
    char cityName[MAX_NAME];
    int cityId;
    int ufId;
    char uf[3];
    int population;
    struct City *next;
} City;

typedef struct {
    int cityId;
    int ufId;
} citySearch;

City * hashTable[TABLE_SIZE];

citySearch allCitiesIDs[TABLE_SIZE];

int cityCounter = 0;
int searchCounter = 0;
City *cityArray[TABLE_SIZE] = { NULL };

int binaryTotalCounter = 0;
int buscas = 1;
int loopCounter = 0;

int createHash(int cityId) {
    return ((cityId + cityId) % TABLE_SIZE);
}

void initHashTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashTableInsert(City *city) {
    if (city == NULL) return -1;
    int index = createHash(city->cityId);
    int i;
    city->next = hashTable[index];
    hashTable[index] = city;
    return 1;
}

City* hashTableSearch(int *cityId, int *ufId) {
    int index = createHash(cityId);
    int i, counter = 0;
    City *buffer = hashTable[index];
    do {
        counter++;
        if (buffer->ufId != ufId) {
            buffer = buffer->next;
        } else {
            printf("%d lacos para encontrar - ", counter);
            return buffer;
        }
    } while (buffer != NULL);

    return buffer;
}

City* hashTableDelete(int *cityId, int *ufId) {
    int index = createHash(cityId);
    int i;
    City *buffer = hashTable[index];
    City *previous = NULL;
    do {
        if (buffer->ufId != ufId) {
            previous = buffer;
            buffer = buffer->next;
        } else {

        if (buffer == NULL) return NULL;
        if (previous == NULL) {
            hashTable[index] = buffer->next;
        } else {
            previous->next = buffer->next;
        }
            return buffer;
        }
    } while (buffer != NULL);

    return buffer;
}

void printTable() {
    int i;
    printf(" --- \n");
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == NULL) {
            printf("\nposicao: %d, cidade: NULL\n", i);
        } else {
            printf("\nposicao: %d, cidades:\n", i);
            City *buffer = hashTable[i];
            while (buffer != NULL) {
                printf("%d, %d, %s\n", buffer->cityId, buffer->ufId, buffer->cityName);
                buffer = buffer->next;
            }
            printf("\n-----\n");
        }
    }
    printf(" --- \n");
}

// Agradecimento ao Andre por esta parte feita por ele
// Algumas modificacoes minhas mas o credito e dele.

City* createCity(char* uf, int ufId, int cityId, char* cityName, int population) {
	City* newCity = (City*)malloc(sizeof(City));
	strcpy(newCity->uf, uf);
    newCity->ufId = ufId;
    newCity->cityId = cityId;
    strcpy(newCity->cityName, cityName);
    newCity->population = population;
    return newCity;
}

int ReadCities() {
    FILE *file = fopen("cidades.csv", "r");
    if (file == NULL) {
        printf("Deu ruim!.\n");
        system("pause");
        system("exit");        
    }
	int a;
	
    char buf[MAX_STR_LEN];
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
        int ufId;
        sscanf(tmp, "%d", &ufId);

        tmp = strtok(NULL, ",");
        int cityId;
        sscanf(tmp, "%d", &cityId);

        tmp = strtok(NULL, ",");
        char cityName[MAX_NAME];
        strcpy(cityName, tmp);

        tmp = strtok(NULL, ",");
        int population;
        sscanf(tmp, "%d", &population);
        
        if(count == 0){/*ignora a primeira linha do arquivo*/
        	count++;
		}
		else{
			City* newCity = createCity(uf, ufId, cityId, cityName, population);
            hashTableInsert(newCity);
            cityArray[cityCounter] = newCity;
            cityCounter++;
		}
    }

    fclose(file);
    return 1;
}

// Preenche array com todos os codigos de municipios presentes no arquivo
void fillSearchArray() {

	FILE *file;
    if ((file = fopen("cityIds.txt", "r")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
        char buf[MAX_STR_LEN];//buffer para cada linha do csv
    char *tmp;
    int i = 0, count = 0;
    while (fgets(buf, MAX_STR_LEN, file) != NULL) {
        if ((strlen(buf) > 0) && (buf[strlen(buf) - 1] == '\n')) {
            buf[strlen(buf) - 1] = '\0';
        }
        
		/*corta cada coluna, se orientando pelas virgulas*/
        tmp = strtok(buf, ",");
        int cityId;
        sscanf(tmp, "%d", &cityId);
        
        tmp = strtok(NULL, ",");
        int ufId;
        sscanf(tmp, "%d", &ufId);

        citySearch newCity = {.cityId = cityId, .ufId = ufId};

        allCitiesIDs[searchCounter] = newCity;

        searchCounter++;
    }
    }

}

// funcao necessaria para o qsort, adequada para o caso atual
int compareCityIdSort (const void * a, const void * b) {

	City* city1 = (*(City**)a);
    City* city2 = (*(City**)b);

    if (city1->cityId < city2->cityId) {
        return -1;
    } else if (city1->cityId > city2->cityId) {
        return 1;
    } else {
        if (city1->ufId < city2->ufId) {
            return -1;
        } else if (city1->ufId > city2->ufId) {
            return 1;
        } else {
            return 0;
        }
            
    }
  
}

// funcao necessaria para o bsearch, adequada para o caso atual
int compareCityIdSearch (const void * a, const void * b) {

	City* city1 = (*(City**)a);
    City* city2 = (*(City**)b);

    return ((city1->cityId) - (city2->cityId));
  
}

City *binarySearch(City *array[], int start, int arraysize, int cityId, int ufId) {
    
    loopCounter = 0;

    buscas++;

    while (start <= arraysize) {
        loopCounter++;
        binaryTotalCounter++;
        int m = start + (arraysize - start) / 2;
        if (array[m]->cityId == cityId) {
            if (array[m]->ufId == ufId) {
                return array[m];
            } else {
                // Procura pra esquerda e direita pelo UF correspondente quando tem city ID conflitante
                int left = m - 1;
                while (left >= start && array[left]->cityId == cityId) {
                    if (array[left]->ufId == ufId) {    
                        return array[left];
                    }
                    left--;
                }
                int right = m + 1;
                while (right <= arraysize && array[right]->cityId == cityId) {
                    if (array[right]->ufId == ufId) {    
                        return array[right];
                    }
                    right++;
                }
            }
        } else if (array[m]->cityId < cityId) {
            start = m + 1;
        } else {
            arraysize = m - 1;
        }
        
    }

    return NULL;

}

void main() {
	setlocale(LC_ALL, "Portuguese");

    int i;

    FILE* file;

    City *buffer;

    initHashTable();

    // Questao 1, 2 e 3 - Leitura dos dados para Lista Dispersa e Array de Structs, e a ordenacao do array de structs

    ReadCities();

    // Preenchimento de array com dados a serem pesquisados (struct de cityId + ufId)

    fillSearchArray();

    // Ordenacao do array de structs

    qsort(cityArray, TABLE_SIZE, sizeof(cityArray[0]), compareCityIdSearch);

    // Questao 4 - Teste de buscas Hash e BSearch

    // Gera 10 valores aleatorios dentro do tamanho da tabela para serem pesquisados, comparando com 10 valores dentro da
    // tabela de ids de municipios, assim pesquisando 10 valores validos

    srand(time(NULL));

    int searchValues[10];

    for (i = 0; i < 10; i++) {
        searchValues[i] = rand() % TABLE_SIZE;
    }
    
    // Busca Hash

    if ((file = fopen("questao4HashSearch.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {

        for (i = 0; i < 10; i++) {
            
            City *cityFound = hashTableSearch(allCitiesIDs[searchValues[i]].cityId, allCitiesIDs[searchValues[i]].ufId);

            printf("Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

            fprintf(file, "Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

        }

    }

    fclose(file);

    // Busca Binaria
    
    // Nao deu

    // if ((file = fopen("questao4BinarySearch.txt", "w")) == NULL) {
    //     printf("Erro ao abrir arquivo");
    // } else {

    //     for (i = 0; i < 10; i++) {
            
    //         City *cityFound = bsearch(allCitiesIDs[searchValues[i]].cityId, cityArray, TABLE_SIZE, sizeof(cityArray[0]), compareCityIdSearch);

    //         printf("Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

    //         fprintf(file, "Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

    //     }

    // }

    // fclose(file);

    // Questao 5 - Busca Binaria com contador

    if ((file = fopen("questao5BinarySearch.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {

        for (i = 0; i < TABLE_SIZE; i++) {

            City *cityFound = binarySearch(cityArray, 0, TABLE_SIZE, allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);

            printf("%d lacos para encontrar - Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", loopCounter, cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

            fprintf(file, "%d lacos para encontrar - Nome da Cidade: %s, ID da Cidade: %d, ID do UF: %d, UF: %s, Populacao: %d\n", loopCounter, cityFound->cityName, cityFound->cityId, cityFound->ufId, cityFound->uf, cityFound->population);

        }

    }

    printf("Numero total de lacos de busca: %d\n", binaryTotalCounter);

    fprintf(file, "Numero total de lacos de busca: %d\n", binaryTotalCounter);

    fclose(file);
    
    // Questao 6 - Busca Hash

    if ((file = fopen("questao6HashSearch.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {

        for (i = 0; i < TABLE_SIZE; i++) {

            buffer = hashTableSearch(allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);

            if (buffer == NULL) {
                printf(" Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
                fprintf(file, " Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
            } else {
                printf(" Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
                fprintf(file, "Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
            }

        }

    }

    fclose(file);

    // Questao 7: Insira os novos registros abaixo.

    City newCity1 = {.cityId = 6001, .cityName = "Albatroz", .uf = "RS", .ufId = 43, .population = 5000};
    cityArray[cityCounter] = &newCity1;
    cityCounter++;

    City newCity2 = {.cityId = 6001, .cityName = "Borussia", .uf = "SC", .ufId = 42, .population = 4000};
    cityArray[cityCounter] = &newCity2;
    cityCounter++;

    City newCity3 = {.cityId = 6001, .cityName = "Palmital", .uf = "PR", .ufId = 41, .population = 3000};
    cityArray[cityCounter] = &newCity3;
    cityCounter++;

    City newCity4 = {.cityId = 6001, .cityName = "Laranjeiras", .uf = "Mt", .ufId = 51, .population = 2000};
    cityArray[cityCounter] = &newCity4;
    cityCounter++;

    hashTableInsert(&newCity1);
    hashTableInsert(&newCity2);
    hashTableInsert(&newCity3);
    hashTableInsert(&newCity4);

    buffer = hashTableSearch(6001, 43);

    if (buffer == NULL) {
        printf(" Cidade inexistente\n");
    } else {
        printf(" Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 42);

    if (buffer == NULL) {
        printf(" Cidade inexistente\n");
    } else {
        printf(" Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 41);

    if (buffer == NULL) {
        printf(" Cidade inexistente\n");
    } else {
        printf(" Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 51);

    if (buffer == NULL) {
        printf(" Cidade inexistente\n");
    } else {
        printf(" Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }

    City *cityArray2[5574] = { NULL };

    for (i = 0; i < 5574; i++) {
        cityArray2[i] = cityArray[i];
    }

    cityArray2[5570] = &newCity1;
    cityArray2[5571] = &newCity2;
    cityArray2[5572] = &newCity3;
    cityArray2[5573] = &newCity4;

    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray2[5570]->cityName, cityArray2[5570]->cityId, cityArray2[5570]->uf, cityArray2[5570]->ufId, cityArray2[5570]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray2[5571]->cityName, cityArray2[5571]->cityId, cityArray2[5571]->uf, cityArray2[5571]->ufId, cityArray2[5571]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray2[5572]->cityName, cityArray2[5572]->cityId, cityArray2[5572]->uf, cityArray2[5572]->ufId, cityArray2[5572]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray2[5573]->cityName, cityArray2[5573]->cityId, cityArray2[5573]->uf, cityArray2[5573]->ufId, cityArray2[5573]->population);

}
