#include <assert.h>
#include "46_mullist_module.h"

int compare(int a, int b)
{
    return a > b;
}

int main(void)
{
    list_t *l = list_new(compare);
    assert(l);
    assert(0 == list_insert(l, 7));
    assert(0 == list_insert(l, 2));
    assert(0 == list_insert(l, 66));
    assert(0 == list_insert(l, 444));
    assert(0 == list_insert(l, 20500));
    assert(1 == list_insert(l, 7));

    size_t s1;
    assert(0 == list_search(&s1, l, 7));
    assert(1 == s1);

    size_t s2;
    assert(0 == list_search(&s2, l, 444));
    assert(3 == s2);

    assert(-1 == list_search(NULL, l, 6325432));

    assert(0 == list_change(l, 2, 9));
    assert(1 == list_change(l, 66, 444));
    assert(1 == list_change(l, 754642, 444));
    assert(-1 == list_change(l, 754642, 664525));

    assert(0 == list_remove(l, 444));
    assert(0 == list_search(&s2, l, 20500));
    assert(3 == s2);

    int val;
    assert(0 == list_getbyindex(&val, l, 3));
    assert(20500 == val);

    assert(0 == list_getbyindex(&val, l, 0));
    assert(7 == val);

    assert(0 == list_getbyindex(&val, l, 1));
    assert(9 == val);

    assert(-1 == list_getbyindex(&val, l, 1000000));

    assert(4 == list_available(l));

    list_del(&l);
    assert(NULL == l);

    return 0;
}