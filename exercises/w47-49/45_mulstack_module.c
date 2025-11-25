/*
Implement a multiple instance stack using an array whose length is specified when an instance is created.

The stack shall be tested using assertions and provide the following functions:

    A function to create an instance. Length of the array is a parameter of this function.
    A function to push a data element of type uint8_t to a stack.
    A function to get number of the data elements stored in a stack.
    A function to pop an element from a stack.
    A function to get length of a stack.
    A function to clear a stack
    A function to destroy a stack
*/
#include "45_mulstack_module.h"
#include <stdlib.h>

struct stack {
    size_t cap;
    size_t len;
    uint8_t data[];
};

stack_t *stack_new(size_t cap)
{
    stack_t *stack = NULL;
    if (cap > 0)
    {
        stack = (stack_t *)malloc(sizeof(stack_t) + cap);
        if (stack != NULL)
        {
            stack->cap = cap;
            stack->len = 0;
        }
    }
    return stack;
}

void stack_del(stack_t **stack)
{
    if (stack != NULL)
    {
        free(*stack);
        *stack = NULL;
    }
}

int stack_push(stack_t *stack, uint8_t element)
{
    int ec = -1;
    if (stack != NULL)
    {
        if (stack->len < stack->cap)
        {
            ec = 0;
            stack->data[stack->len] = element;
            stack->len++;
        }
    }
    return ec;
}

int stack_pop(stack_t *stack, uint8_t *element)
{
    int ec = -1;
    if (stack != NULL && element != NULL)
    {
        if (stack->len > 0)
        {
            ec = 0;
            *element = stack->data[stack->len - 1];
            stack->len--;
        }
    }
    return ec;
}

size_t stack_size(stack_t *stack)
{
    return (stack != NULL) ? stack->len : 0u;
}

size_t stack_capacity(stack_t *stack)
{
    return (stack != NULL) ? stack->cap : 0u;
}

void stack_clear(stack_t *stack)
{
    if (stack != NULL)
    {
        stack->len = 0;
    }
}