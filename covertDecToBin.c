#include <stdio.h>
#include "stacksADT.h"

int main (void)
{
// Local Definitions
 unsigned int    num;
          int*   digit;
          STACK* stack;
          
// Statements
 // Create Stack
 stack = createStack ();
 // prompt and read a number
 printf ("\nEnter an integer : ");
 scanf("%d", &num);
 // create 0s and 1s and push them into the stack
 while (num > 0)   
    {
     digit  = (int*) malloc (sizeof(int));
     *digit = num % 2;
     pushStack(stack, digit);
     num = num /2;
    } // while
 // Binary number created. Now print it
 printf ("\nThe binary number is : ");
 while (!emptyStack (stack))
    {
     digit = (int*)popStack(stack);
 	 printf ("%1d", *digit);
    } // while
 printf ("\n");
 // Destroying Stack
 destroyStack (stack);
 return 0;
} // main


