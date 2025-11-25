#ifndef STACK_MODULE_H
#define STACK_MODULE_H
#include <stddef.h>

typedef struct stack stack_t;

int stack_push(int val);
void stack_pop(void);
size_t stack_size(void);
void stack_clear(void);

#endif