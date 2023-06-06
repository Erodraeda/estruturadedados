#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
int stack[MAX];
int top = 0;

int stackEmpty(int *array) {
	
	if (*array == '\0') {
		return 1;
	}
	
	return 0;
	
}

void push(int *array, int value) {
	
	int nextIn = sizeof(*array);

    printf("%d", nextIn);
	
//	array[nextIn] = value;
	
}

int pop(int array) {
	
	int lastIn = sizeof(array);
	
//	printf(" Element deleted: %d\n", array[lastIn]);
	
//	array[lastIn] = 0;

	return array;
	
}