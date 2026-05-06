#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->data = (Action *)malloc(sizeof(Action) * capacity);
    stack->top = -1;
    return stack;
}

void push(Stack *stack, Action action)
{
    if (stack->top == stack->capacity - 1)
    {
        printf("stack dolu\n");
        return;
    }
    stack->top++;
    stack->data[stack->top] = action;
}

Action pop(Stack *stack)
{
    if (isEmptyStack(stack))
    {
        printf("stack bos\n");
        return;
    }
    Action temp = stack->data[stack->top];
    stack->top--;
    return temp;
}

Action peek(Stack *stack)
{
    return stack->data[stack->top];
}

int isEmptyStack(Stack *stack)
{
    return stack->top == -1;
}

void freeStack(Stack *stack)
{
    free(stack->data);
    free(stack);
}