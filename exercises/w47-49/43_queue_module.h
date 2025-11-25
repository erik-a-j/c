#ifndef QUEUE_MODULE_H
#define QUEUE_MODULE_H
#include <stddef.h>

typedef struct queue queue_t;

int queue_enqueue(int val);
void queue_dequeue(void);
size_t queue_size(void);
void queue_delete(void);

#endif