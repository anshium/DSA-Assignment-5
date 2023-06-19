#include "queue.h"
Queue createQueue(){
	Queue Q = (Queue)malloc(sizeof(QueueInfo));
	Q->num_elems = 0;
	Q->L = (listnodeptr)malloc(sizeof(ListNode));
	Q->L->x = 0;
	Q->L->y = 0;
	Q->L->next = NULL;
	Q->rear = Q->L;

	return Q;
}

listnodeptr makeListNode(int x, int y){
	listnodeptr l = (listnodeptr)malloc(sizeof(ListNode));
	l->x = x;
	l->y = y;
	l->next = NULL;

	return l;
}

void enqueue(Queue Q, int x, int y){
	if(Q->num_elems == 0){
		Q->rear = Q->L;
	}
	Q->rear->next = makeListNode(x, y);
	Q->rear = Q->rear->next;
	Q->num_elems += 1;
	return;
}

listnodeptr dequeue(Queue Q){
	if(isEmpty(Q)){
		return NULL;
	}
	
	listnodeptr p = Q->L->next;
	Q->L->next = Q->L->next->next;
	Q->num_elems -= 1;
	
	return p;
}

void printQueue(Queue Q){
	listnodeptr p = Q->L->next;
	for(int i = 0; i < Q->num_elems; i++){
		printf("(%d, %d) ", p->x, p->y);
		p = p->next;
	}
		// printf("%d ", p->val);
	printf("\n");
}

int isEmpty(Queue Q){
	if(Q->num_elems == 0){
		return 1;
	}
	return 0;
}