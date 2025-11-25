/*
Implement a single instance queue module using a linked list to store data of type int.
The module shall be tested using assertion and provide the following functions.

    A function to enqueue a value in the queue
    A function to dequeue a value from the queue
    A function to get number of the data elements stored in the queue
    A function to delete all the data elements stored in the queue
*/
#include <stdlib.h>
#include "43_queue_module.h"

typedef struct node {
    int data;
    struct node *next;
} node_t;

struct queue {
    node_t *head;
    node_t *tail;
    size_t cap;
};

static queue_t queue;

int queue_enqueue(int val)
{
    int ec = -1;
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node)
    {
        ec = 0;
        new_node->data = val;
        new_node->next = NULL;
        queue.cap++;
        if (queue.head == NULL)
        {
            queue.head = new_node;
            queue.tail = queue.head;
        } else
        {
            queue.tail->next = new_node;
            queue.tail = new_node;
        }
    }
    return ec;
}

void queue_dequeue(void)
{
    if (queue.head != NULL)
    {
        node_t *old_head = queue.head;
        queue.head = queue.head->next;
        free(old_head);
        queue.cap--;
    }
}

size_t queue_size(void)
{
    return queue.cap;
}

void queue_delete(void)
{
    node_t *head = queue.head;
    while (head != NULL)
    {
        node_t *current = head;
        head = head->next;
        free(current);
    }
    queue.head = NULL;
    queue.tail = NULL;
    queue.cap = 0;
}