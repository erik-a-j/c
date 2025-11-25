/*
Implement a single instance stack module using a linked list to store data of type int.
The module shall be tested using assertion and provide the following functions:

    A function to push a data element to the stack
    A function to pop a data element from the stack
    A function to get number of data elements stored in the stack
    A function to clear the stack
*/
#include "44_stack_module.h"
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} node_t;

struct stack {
    node_t *bot;
    node_t *top;
    size_t cap;
};

static stack_t stack;

int stack_push(int val)
{
    int ec = -1;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node)
    {
        ec = 0;
        new_node->data = val;
        new_node->next = NULL;
        new_node->prev = stack.top;
        if (stack.bot == NULL)
        {
            stack.bot = new_node;
            stack.top = stack.bot;
        } else
        {
            stack.top->next = new_node;
            stack.top = new_node;
        }
        stack.cap++;
    }
    return ec;
}

void stack_pop(void)
{
    if (stack.top != NULL)
    {
        node_t *current = stack.top;
        stack.top = stack.top->prev;
        stack.top->next = NULL;
        free(current);
        stack.cap--;
    }
}

size_t stack_size(void)
{
    return stack.cap;
}

void stack_clear(void)
{
    node_t *top = stack.top;
    while (top != NULL)
    {
        node_t *current = top;
        top = top->prev;
        free(current);
    }
    stack.bot = NULL;
    stack.top = NULL;
    stack.cap = 0;
}