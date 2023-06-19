#include "queue.h"

void foo(Queue Q){
	enqueue(Q, 3, 3);
}

int main(){
	Queue Q = createQueue();
	// foo(Q);
	enqueue(Q, 1, 1);
	// enqueue(Q, 2, 2);
	// enqueue(Q, 3, 3);
	// enqueue(Q, 4, 4);
	// listnodeptr p = dequeue(Q);
	// printf("%d\n", p->x);
	dequeue(Q);
	enqueue(Q, 2, 2);
	dequeue(Q);
	// dequeue(Q);

	printQueue(Q);
	return 0;
}