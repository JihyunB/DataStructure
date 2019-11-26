#include <stdio.h>
#include <stdbool.h>
#include "stacksADT.h"

int main (void)
{
	bool done = false;
	int* dataPtr;
	
	STACK* stack;
	
	stack = createStack();
	
	while(!done)
	{
		dataPtr = (int*) malloc (sizeof(int));
		printf("Enter a number: <EOF> to stop: ");
		if( (scanf("%d", dataPtr)) == EOF || fullStack(stack))
			done = true;
		else
			pushStack(stack, dataPtr);
	}
	
	printf("\n\nThe list of numbers reversed:\n");
	while(!emptyStack(stack))
	{
		dataPtr = (int*)popStack(stack);
		printf("%3d\n",*dataPtr);
		free(dataPtr);
	}
	
	
	destroyStack(stack);
	return 0;
}
