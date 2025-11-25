#ifndef MULSTACK_MODULE_H
#define MULSTACK_MODULE_H
#include <stddef.h>
#include <stdint.h>

typedef struct stack stack_t;

stack_t *stack_new(size_t cap);
void stack_del(stack_t **stack);
int stack_push(stack_t *stack, uint8_t element);
int stack_pop(stack_t *stack, uint8_t *element);
size_t stack_size(stack_t *stack);
size_t stack_capacity(stack_t *stack);
void stack_clear(stack_t *stack);

#endif