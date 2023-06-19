// Linked list implementation of a queue
#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct QueueInfo{
	int num_elems;
	List L;
	listnodeptr front;
	listnodeptr rear;
} QueueInfo;

typedef QueueInfo* Queue;
typedef Queue queueptr;

Queue createQueue();

void enqueue(Queue Q, int x, int y);

listnodeptr dequeue(Queue Q);

void printQueue(Queue Q);

int isEmpty(Queue Q);

#endif