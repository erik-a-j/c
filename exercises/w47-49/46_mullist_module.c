/*
Implement a multiple-instance linked list module of unique and sorted data elements of type int. 
The module shall be tested using assertion and support the following operations:
    Creating a list
    Inserting a new node in a list
    Change a data element in a list
    Deleting a value from a list
    Searching for a value in a list
    Getting data stored in the nth node of a list
    Getting available number of elements stored in a list
    Destroying a list
Sorted means that when you want to add a new data element, 
you should find the right position for the new node in a way that the list is always sorted.
*/
#include "46_mullist_module.h"
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;
struct list {
    cmp_fn cmp;
    node_t *head;
    node_t *tail;
    size_t available;
};

list_t *list_new(cmp_fn cmp)
{
    list_t *l = NULL;
    if (cmp)
    {
        l = (list_t *)malloc(sizeof(list_t));
        if (l)
        {
            l->cmp = cmp;
            l->head = NULL;
            l->tail = NULL;
            l->available = 0;
        }
    }
    return l;
}

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
static void list_sort(list_t *l)
{
    for (node_t *node = l->head; node != NULL; node = node->next)
    {
        for (node_t *next = node->next; next != NULL; next = next->next)
        {
            if (l->cmp(node->data, next->data))
            {
                swap(&node->data, &next->data);
            }
        }
    }
}
static int _list_search(list_t *l, int value, node_t **out_prev_node, size_t *out_index, int *change)
{
    int ec = -1;
    if (l)
    {
        size_t i = 0;
        node_t *prev_node = NULL;
        for (node_t *node = l->head; node != NULL; node = node->next, i++)
        {
            if (node->data == value)
            {
                ec = 0;
                if (out_prev_node)
                {
                    *out_prev_node = prev_node;
                }
                if (out_index)
                {
                    *out_index = i;
                }
                if (change)
                {
                    node->data = *change;
                    list_sort(l);
                }
                break;
            }
            prev_node = node;
        }
    }
    return ec;
}

int list_insert(list_t *l, int value)
{
    int ec = -1;
    if (l)
    {
        if (0 == _list_search(l, value, NULL, NULL, NULL))
        {
            ec = 1;
        } else
        {
            node_t *node = (node_t *)malloc(sizeof(node_t));
            if (node)
            {
                ec = 0;
                node->next = NULL;
                node->data = value;
                if (l->head == NULL)
                {
                    l->head = node;
                    l->tail = l->head;
                } else
                {
                    l->tail->next = node;
                    l->tail = node;
                    list_sort(l);
                }
                l->available++;
            }
        }
    }
    return ec;
}

int list_search(size_t *out_index, list_t *l, int value)
{
    return _list_search(l, value, NULL, out_index, NULL);
}

int list_change(list_t *l, int old_value, int new_value)
{
    int ec = -1;
    if (l)
    {
        ec = 1;
        if (0 != _list_search(l, new_value, NULL, NULL, NULL))
        {
            ec = _list_search(l, old_value, NULL, NULL, &new_value);
        }
    }
    return ec;
}

int list_remove(list_t *l, int value)
{
    int ec = -1;
    if (l)
    {
        node_t *prev_remove = NULL;
        if (0 == _list_search(l, value, &prev_remove, NULL, NULL))
        {
            ec = 0;
            node_t *current = prev_remove->next;
            prev_remove->next = current->next;
            free(current);
            l->available--;
        }
    }
    return ec;
}

int list_getbyindex(int *out_value, list_t *l, size_t index)
{
    int ec = -1;
    if (out_value && l && index <= l->available - 1)
    {
        node_t *node = l->head;
        for (; index != 0 && node != NULL; node = node->next, index--)
            ;
        if (node)
        {
            ec = 0;
            *out_value = node->data;
        }
    }
    return ec;
}

size_t list_available(list_t *l)
{
    return l ? l->available : 0;
}

void list_del(list_t **l)
{
    if (l)
    {
        node_t *node = (*l)->head;
        while (node)
        {
            node_t *current = node;
            node = node->next;
            free(current);
        }
        free(*l);
        *l = NULL;
    }
}

/*
Implement a multiple-instance linked list module of unique and sorted data elements of type int. 
The module shall be tested using assertion and support the following operations:
    Creating a list
    Inserting a new node in a list
    Change a data element in a list
    Deleting a value from a list
    Searching for a value in a list
    Getting data stored in the nth node of a list
    Getting available number of elements stored in a list
    Destroying a list
Sorted means that when you want to add a new data element, 
you should find the right position for the new node in a way that the list is always sorted.
*/