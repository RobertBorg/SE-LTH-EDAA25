#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACKSPACE 10

void error(char* errMsg) {
	printf("%s\n", errMsg);
	exit(1);
}

int stack[STACKSPACE];
int* stackEnd = stack + STACKSPACE;

void push(int** stackPointer) {
	++*stackPointer;
	if(*stackPointer > stackEnd) {
		error("Out of stack space");
	}
}

void pop(int** stackPointer) {
	--*stackPointer;
	if(*stackPointer < stack) {
		error("syntax error");
	}	
}


int main ()
{

	register int c;
	bool isIsDigit = false;
	bool wasIsDigit = false;
	int* stackPointer = stack;
	while ((c=getchar()) != EOF){
	    if (isIsDigit = isdigit(c)) {
	    	if(!wasIsDigit) {
	    		push(&stackPointer);
	    		*stackPointer = 0;
	    	}
	    	*stackPointer *= 10;
	    	*stackPointer += c - '0';
	    } else {
		    register int current = *stackPointer;
		    switch (c) {
		    	case '+':
		    		pop(&stackPointer);
		    		//printf("%d + %d\n", *stackPointer, current);
		    		*stackPointer += current;
		    		break;
		    	case '-':
		    		pop(&stackPointer);
		    		//printf("%d - %d\n", *stackPointer, current);
		    		*stackPointer -= current;
		    		break;
		    	case '*':
		    		pop(&stackPointer);
		    		//printf("%d * %d\n", *stackPointer, current);
		    		*stackPointer *= current;
		    		break;
		    	case '/':
		    		pop(&stackPointer);
		    		if(current == 0) {
		    			error("division by zero");
		    		}
		    		//printf("%d / %d\n", *stackPointer, current);
		    		*stackPointer += current;
		    		break;
		    	case '\n':
		    		pop(&stackPointer);
		    		printf("%d\n", current );
		    		break;
		    	case ' ':
		    		break;
		    	default:
		    		error("syntax error");
		    		break;
		    }
	    }
		wasIsDigit = isIsDigit;
	}
	return 0;
}