#include <stdio.h>
#include <stdbool.h>



int main ()
{

	int c;
	int temp = 0;
	bool isIsDigit = false;
	bool wasIsDigit = false;
	int stack[100];
	int* stackPointer = stack;
	int* stackEnd = stackPointer + sizeof(int) * 100;
	while ((c=getchar()) != EOF){
	    if (isIsDigit = isdigit(c)) {
	    	if(!wasIsDigit) {
	    		*++stackPointer = 0;
	    	}
	    	*stackPointer *= 10;
	    	*stackPointer += c - '0';
	    } else {
	    }
	    int current = *stackPointer;
	    switch (c) {
	    	case '+':
	    		--stackPointer;
	    		//printf("%d + %d\n", *stackPointer, current);
	    		*stackPointer += current;
	    		break;
	    	case '-':
	    		--stackPointer;
	    		//printf("%d - %d\n", *stackPointer, current);
	    		*stackPointer -= current;
	    		break;
	    	case '*':
	    		--stackPointer;
	    		//printf("%d * %d\n", *stackPointer, current);
	    		*stackPointer *= current;
	    		break;
	    	case '/':
	    		--stackPointer;
	    		//printf("%d / %d\n", *stackPointer, current);
	    		*stackPointer += current;
	    		break;
	    	case '\n':
	    		--stackPointer;
	    		printf("%d\n", current );
	    		break;
	    	default:
	    		break;
	    }
		wasIsDigit = isIsDigit;
	}
	return 0;
}