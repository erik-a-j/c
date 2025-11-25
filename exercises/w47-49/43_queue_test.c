#include <assert.h>
#include "43_queue_module.h"

int main(void)
{
    assert(0 == queue_enqueue(5));
    assert(1 == queue_size());

    assert(0 == queue_enqueue(10));
    assert(2 == queue_size());

    assert(0 == queue_enqueue(15));
    assert(3 == queue_size());

    assert(0 == queue_enqueue(20));
    assert(4 == queue_size());

    queue_dequeue();
    assert(3 == queue_size());

    queue_delete();
    assert(0 == queue_size());
    return 0;
}