#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

int array[10];

//int stackEmpty(int array) {
//	
//	if (array == NULL) {
//		return 1;
//	}
//	
//	return 0;
//	
//}
//
//void push(int array, int value) {
//	
//	int nextIn = sizeof(array) + 1;
//	
//	printf(" %d", nextIn);
//	
////	array[nextIn] = value;
//	
//}
//
//void pop(int array) {
//	
//	int lastIn = sizeof(array);
//	
////	printf(" Element deleted: %d\n", array[lastIn]);
//	
////	array[lastIn] = 0;
//	
//}

void main() {
	
	int i;
	
	for (i = 0; i < 15; i++) {
		push(array, i);
	}
	
	for (i = 0; i < 15; i++) {
		int valor = pop(array);
		printf("%d\n", valor);
	}
		
	int otherArray[10] = {};
	
	int arrayOneEmpty = stackEmpty(array);
	
	int arrayTwoEmpty = stackEmpty(otherArray);
	
	printf(" teste 1: %d\n teste 2: %d", arrayOneEmpty, arrayTwoEmpty);
	
	push(array, 5);
	
	printf("%d", array);
	
	system("pause");
	
}
