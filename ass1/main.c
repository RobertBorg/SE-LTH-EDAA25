//870906-3997 Robert Borg
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACKSPACE 10

void error(char* errMsg)
{
        printf("%s\n", errMsg);
        exit(1);
}

int stack[STACKSPACE];
int* stack_end = stack + STACKSPACE;

void push(int** stack_pointer)
{
        if(*stack_pointer >= stack_end) {
                error("Out of stack space");
        }
        ++*stack_pointer;
}

void pop(int** stack_pointer)
{
        if(*stack_pointer <= stack) {
                error("syntax error");
        }       
        --*stack_pointer;
}

int main ()
{
        register int c;
        bool is_is_digit = false;
        bool was_is_digit = false;
        int* stack_pointer = stack;
        while ((c=getchar()) != EOF) {
                if (is_is_digit = isdigit(c)) {
                        if (!was_is_digit) {
                                push(&stack_pointer);
                                *stack_pointer = 0;
                        }
                        *stack_pointer *= 10;
                        *stack_pointer += c - '0';
                } else {
                        register int current = *stack_pointer;
                        switch (c) {
                        case '+':
                                pop(&stack_pointer);
                                *stack_pointer += current;
                                break;
                        case '-':
                                pop(&stack_pointer);
                                *stack_pointer -= current;
                                break;
                        case '*':
                                pop(&stack_pointer);
                                *stack_pointer *= current;
                                break;
                        case '/':
                                pop(&stack_pointer);
                                if(current == 0) {
                                        error("division by zero");
                                }
                                *stack_pointer /= current;
                                break;
                        case '\n':
                                pop(&stack_pointer);
                                printf("%d\n", current );
                                break;
                        case ' ':
                                break;
                        default:
                                error("syntax error");
                                break; 
                        }
                }
                was_is_digit = is_is_digit;
        }
        return 0;
}