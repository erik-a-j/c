#include <assert.h>
#include "45_mulstack_module.h"

int main(void)
{
    stack_t *stack = stack_new(5);
    assert(stack != NULL);
    assert(5 == stack_capacity(stack));
    assert(0 == stack_size(stack));

    assert(0 == stack_push(stack, 100u));
    assert(1 == stack_size(stack));
    assert(0 == stack_push(stack, 44u));
    assert(2 == stack_size(stack));

    uint8_t last;
    assert(0 == stack_pop(stack, &last));
    assert(1 == stack_size(stack));
    assert(44u == last);

    assert(0 == stack_push(stack, 255u));
    assert(2 == stack_size(stack));

    assert(0 == stack_pop(stack, &last));
    assert(1 == stack_size(stack));
    assert(255u == last);

    stack_clear(stack);
    assert(0 == stack_size(stack));

    assert(0 == stack_push(stack, 1u));
    assert(1 == stack_size(stack));
    assert(0 == stack_push(stack, 1u));
    assert(2 == stack_size(stack));
    assert(0 == stack_push(stack, 1u));
    assert(3 == stack_size(stack));
    assert(0 == stack_push(stack, 1u));
    assert(4 == stack_size(stack));
    assert(0 == stack_push(stack, 1u));
    assert(5 == stack_size(stack));

    assert(-1 == stack_push(stack, 1u));

    stack_del(&stack);
    assert(stack == NULL);

    return 0;
}