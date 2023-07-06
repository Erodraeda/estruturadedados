#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_NAME 33
#define MAX_ID 10
#define TABLE_SIZE 5574
#define HASH_SIZE 50
#define MAX_STR_LEN 255

FILE* file;

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

City * hashTable[HASH_SIZE];

citySearch allCitiesIDs[TABLE_SIZE];

int cityCounter = 0;
int searchCounter = 0;
City *cityArray[TABLE_SIZE] = { NULL };

int binaryTotalCounter = 0;
int buscas = 1;
int loopCounter = 0;
int hashCounter = 0;

int createHash(int cityId) {
    return ((cityId + cityId) % HASH_SIZE);
}

void initHashTable() {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
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
    int i;
    hashCounter = 0;
    City *buffer = hashTable[index];
    do {
        hashCounter++;
        if (buffer->ufId != ufId) {
            buffer = buffer->next;
        } else {
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
    int i, emptyCounter = 0, filledCounter = 0, colisionCounter;
    printf(" --- \n");
    if ((file = fopen("printTable.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {

        for (i = 0; i < HASH_SIZE; i++) {
            colisionCounter = 0;
            if (hashTable[i] == NULL) {
                printf("\nposicao: %d, cidade: NULL\n", i);
                fprintf(file, "\nposicao: %d, cidade: NULL\n", i);
                emptyCounter++;
            } else {
                printf("\nposicao: %d, cidades:\n", i);
                fprintf(file, "\nposicao: %d, cidades:\n", i);
                filledCounter++;
                City *buffer = hashTable[i];
                while (buffer != NULL) {
                    printf("%d, %d, %s\n", buffer->cityId, buffer->ufId, buffer->cityName);
                    fprintf(file, "%d, %d, %s\n", buffer->cityId, buffer->ufId, buffer->cityName);
                    buffer = buffer->next;
                    colisionCounter++;
                }
                fprintf(file, "\n---- %d colisoes nesta posicao ----\n", colisionCounter);
                printf("\n-----\n");
            }
        }
        fprintf(file, "\n\n---- %d posicoes preenchidas\n----- %d posicoes vazias", filledCounter, emptyCounter);
    }
    printf(" --- \n");

    fclose(file);
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
    City* city2 = (*(City**)b);

    return ((a) - (city2->cityId));
  
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

    City *buffer;

    initHashTable();

    // Questao 1, 2 e 3 - Leitura dos dados para Lista Dispersa e Array de Structs, e a ordenacao do array de structs

    ReadCities();

    City emptyCity = {.cityId = 0, .cityName = "", .uf = "", .ufId = 0, .population = 0};

    cityArray[5570] = &emptyCity;
    cityArray[5571] = &emptyCity;
    cityArray[5572] = &emptyCity;
    cityArray[5573] = &emptyCity;

    printTable();

    // Preenchimento de array com dados a serem pesquisados (struct de cityId + ufId)

    fillSearchArray();

    // Ordenacao do array de structs

    qsort(cityArray, TABLE_SIZE, sizeof(cityArray[0]), compareCityIdSort);

    // Questao 4 - Teste de buscas Hash e BSearch

    // Busca Hash

    if ((file = fopen("questao4HashSearch.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {

        for (i = 0; i < TABLE_SIZE; i++) {
            
            City *cityFound = hashTableSearch(allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);

            if (cityFound == NULL) {
                printf("Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
                fprintf(file, "Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
            } else {
                printf("Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->uf, cityFound->ufId, cityFound->population);
                fprintf(file, "Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", cityFound->cityName, cityFound->cityId, cityFound->uf, cityFound->ufId, cityFound->population);
            }

        }

    }

    fclose(file);

    // Busca Binaria

    if ((file = fopen("questao4BinarySearch.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo");
    } else {
       
        for (i = 0; i < TABLE_SIZE; i++) {

            int key = allCitiesIDs[i].cityId;
            
            City **cityFound = bsearch(allCitiesIDs[i].cityId, cityArray, TABLE_SIZE, sizeof(cityArray[0]), compareCityIdSearch);

            if (cityFound == NULL) {
                printf("Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
                fprintf(file, "Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
            } else {
                printf("Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[i]->cityName, cityArray[i]->cityId, cityArray[i]->uf, cityArray[i]->ufId, cityArray[i]->population);
                fprintf(file, "Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[i]->cityName, cityArray[i]->cityId, cityArray[i]->uf, cityArray[i]->ufId, cityArray[i]->population);
            }

        }

    }

    fclose(file);

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
                printf("Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
                fprintf(file, "Cidade inexistente: id: %d, uf: %d\n", allCitiesIDs[i].cityId, allCitiesIDs[i].ufId);
            } else {
                printf("%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
                fprintf(file, "%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
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
        printf("Cidade inexistente\n");
    } else {
        printf("%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 42);

    if (buffer == NULL) {
        printf("Cidade inexistente\n");
    } else {
        printf("%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 41);

    if (buffer == NULL) {
        printf("Cidade inexistente\n");
    } else {
        printf("%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }
    buffer = hashTableSearch(6001, 51);

    if (buffer == NULL) {
        printf("Cidade inexistente\n");
    } else {
        printf("%d lacos para encontrar - Cidade encontrada: %s - id: %d - uf: %s, %d - populacao: %d\n", hashCounter, buffer->cityName, buffer->cityId, buffer->uf, buffer->ufId, buffer->population);
    }

    cityArray[5570] = &newCity1;
    cityArray[5571] = &newCity2;
    cityArray[5572] = &newCity3;
    cityArray[5573] = &newCity4;

    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[5570]->cityName, cityArray[5570]->cityId, cityArray[5570]->uf, cityArray[5570]->ufId, cityArray[5570]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[5571]->cityName, cityArray[5571]->cityId, cityArray[5571]->uf, cityArray[5571]->ufId, cityArray[5571]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[5572]->cityName, cityArray[5572]->cityId, cityArray[5572]->uf, cityArray[5572]->ufId, cityArray[5572]->population);
    printf("%s - id: %d - uf: %s, %d - populacao: %d\n", cityArray[5573]->cityName, cityArray[5573]->cityId, cityArray[5573]->uf, cityArray[5573]->ufId, cityArray[5573]->population);

}
