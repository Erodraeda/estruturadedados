#include<stdio.h>
#include<stdlib.h>
#include" stack.h"

int stackEmpty(int *array) {
	
//	printf(" size: %d", *array);
	
	if (*array == 0) {
		return 1;
	}
	
	return 0;
	
}

void push(int array, int value) {
	
	int nextIn = sizeof(array) + 1;
	
	printf(" %d", nextIn);
	
//	array[nextIn] = value;
	
}

void pop(int array) {
	
	int lastIn = sizeof(array);
	
//	printf(" Element deleted: %d\n", array[lastIn]);
	
//	array[lastIn] = 0;
	
}

void main() {
	
	int array[10] = {1, 2, 3, 4};
		
	int otherArray[10] = {};
	
	int arrayOneEmpty = stackEmpty(array);
	
	int arrayTwoEmpty = stackEmpty(otherArray);
	
	printf(" teste 1: %d\n teste 2: %d", arrayOneEmpty, arrayTwoEmpty);
	
	push(array, 5);
	
	printf("%d", array);
	
}
