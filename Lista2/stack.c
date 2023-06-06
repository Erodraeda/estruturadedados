/* Replace "dll.h" with the name of your header */
#include "stack.h"
#include <windows.h>

DLLIMPORT void HelloWorld()
{
	MessageBox(0,"Hello World from DLL!\n","Hi",MB_ICONINFORMATION);
}

DLLIMPORT int stackEmpty(int *array) {
	
//	printf(" size: %d", *array);
	
	if (*array == 0) {
		return 1;
	}
	
	return 0;
	
}

DLLIMPORT void push(int array, int value) {
	
	int nextIn = sizeof(array) + 1;
	
//	array[nextIn] = value;
	
}

DLLIMPORT int pop(int array) {
	
	int lastIn = sizeof(array);
	
//	printf(" Element deleted: %d\n", array[lastIn]);
	
//	array[lastIn] = 0;

	return array;
	
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
