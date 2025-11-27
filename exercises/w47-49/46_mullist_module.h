#ifndef MULLIST_MODULE_H
#define MULLIST_MODULE_H
#include <stddef.h>

typedef struct list list_t;
typedef int (*cmp_fn)(int a, int b);

list_t *list_new(cmp_fn cmp);
int list_insert(list_t *l, int value);
int list_search(size_t *out_index, list_t *l, int value);
int list_change(list_t *l, int old_value, int new_value);
int list_remove(list_t *l, int value);
int list_getbyindex(int *out_value, list_t *l, size_t index);
size_t list_available(list_t *l);
void list_del(list_t **l);

#endif /*#ifndef MULLIST_MODULE_H*/