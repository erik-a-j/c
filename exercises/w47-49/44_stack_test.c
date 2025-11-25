#include <assert.h>
#include "44_stack_module.h"

int main(void)
{
    assert(0 == stack_push(55));
    assert(1 == stack_size());

    assert(0 == stack_push(231));
    assert(2 == stack_size());

    assert(0 == stack_push(864));
    assert(3 == stack_size());

    stack_pop();
    assert(2 == stack_size());

    stack_clear();
    assert(0 == stack_size());
    return 0;
}