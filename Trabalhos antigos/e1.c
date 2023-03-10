#include <stdio.h>
#include <stdlib.h>
#include <string.h>
main (){
int i, j;
char tabela[7][7];


printf("0 1 2 3 4 5 6\n");


for (i=0; i<7; i++){
for (j=0; j<7; j++){
if (i == j) tabela[i][j] = 'x';
else tabela[i][j] = '-';
}
}


for (i=0; i<7; i++){
for (j=0; j<7; j++){
printf("%c ", tabela[i][j]);
}
printf("\n");
}


}
