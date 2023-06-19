// Steps taken to remove MLE
// No more adjacency lists
// Graph would have each node as a struct that would store visited and value

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct QueueInfo{
	int num_elems;
	int size;
	int* array;
	int front;
	int rear;
} QueueInfo;

typedef QueueInfo* Queue;

Queue createQueue(int size) {
    Queue queue = (QueueInfo*)malloc(sizeof(QueueInfo));
    queue->array = (int*)malloc(sizeof(int) * size);
    queue->num_elems = 0;
    queue->size = size;
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void destroyQueue(Queue queue) {
    free(queue->array);
    free(queue);
}

int isEmpty(Queue queue) {
    if(queue->num_elems == 0){
		return 1;
	}
	return 0;
}

int isFull(Queue queue) {
	if(queue->num_elems == queue->size){
		return 1;
	}
	return 0;
}

void enqueue(Queue queue, int elem) {
    if (isFull(queue)) {
        return;
    }

    queue->rear = (queue->rear + 1) % queue->size;
    queue->array[queue->rear] = elem;
    queue->num_elems++;
}

int dequeue(Queue queue) {
    if (isEmpty(queue)) {
        return 0;
    }

    int elem = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    queue->num_elems--;
    return elem;
}

typedef struct holder{
	int value;
	bool visited;
} holder;

typedef struct GraphNode{
	int N;
	int M;
	holder* graphArray;
} GraphNode;

typedef GraphNode* Graph;

Graph initGraph(int N, int M);

// Although I could have reused the graph declaration, I would be making a separate upDownList

typedef struct upDownListNode{
	int N;
	int M;
	int* upDownArray;
} upDownListNode;

typedef upDownListNode* upDownList;

#define NOT_VISITED 0
#define VISITED 1

upDownList initUpDownList(int N, int M);

void doTheThingdotCom(Graph G, upDownList U, int u, int v);

Graph initGraph(int N, int M){
	Graph G = (Graph)malloc(sizeof(GraphNode));
	G->N = N;
	G->M = M;

	G->graphArray = (holder*)malloc(sizeof(holder) * N * M);

	for(int i = 0; i < N * M; i++){
		G->graphArray[i].visited = false;
	}

	return G;
}

upDownList initUpDownList(int N, int M){
	upDownList U = (upDownList)malloc(sizeof(upDownListNode));
	U->N = N;
	U->M = M;

	U->upDownArray = (int*)malloc(sizeof(int) * N * M);

	for(int i = 0; i < N * M; i++){
		U->upDownArray[i] = 32767;
	}

	return U;
}

// pick up one element
// update all valid non-visited with the up down thingy if that is less

// for all elements adjacent to it:
// 	if(not visited)
// 		put them in a queue

// as easy as that


void print(upDownList U){
	for(int i = 0; i < U->N; i++){
		for(int j = 0; j < U->M; j++){
			printf("%d ", U->upDownArray[i* U->M + j]);
		}
		printf("\n");
	}
}

void freeGraph(Graph G){
	free(G->graphArray);

	free(G);
}

void freeUDL(upDownList U){
	free(U->upDownArray);

	free(U);
}

struct HeapInfo {
    int* heap;
    int capacity;
    int size;
};

typedef struct HeapInfo* Heap;

Heap createHeap(int capacity) {
    Heap heap = (Heap) malloc(sizeof(struct HeapInfo));
    heap->capacity = capacity;
    heap->size = 0;
    heap->heap = (int*)malloc(capacity * sizeof(int));
    return heap;
}

int getParent(int i) {
    int parent = (i - 1) >> 2;
	return parent;
}

int getLeftChild(int i) {
	int leftChild = i << 2 + 1;
    return leftChild;
}

int getRightChild(int i) {
	int rightChild = i << 2 + 2;
    return rightChild;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Heap heap, int index) {
    int parentIndex = parent(index);
    if (index > 0) {
		if(heap->heap[index] < heap->heap[parentIndex]){
			swap(&heap->heap[index], &heap->heap[parentIndex]);
			heapifyUp(heap, parentIndex);
		}
    }
}

void heapifyDown(Heap heap, int index) {
    int leftChildIndex = leftChild(index);
    int rightChildIndex = rightChild(index);
    int smallestIndex = index;

    if (leftChildIndex < heap->size)
		if(heap->heap[leftChildIndex] < heap->heap[smallestIndex])
			smallestIndex = leftChildIndex;
    if (rightChildIndex < heap->size)
		if(heap->heap[rightChildIndex] < heap->heap[smallestIndex])
        	smallestIndex = rightChildIndex;

    if (smallestIndex != index) {
        swap(&heap->heap[index], &heap->heap[smallestIndex]);
        heapifyDown(heap, smallestIndex);
    }
}

void insert(Heap heap, int value) {
    if (heap->size == heap->capacity) {
		// heap full
        return;
    }

    heap->heap[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;

	return;
}

int getMin(Heap heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    return heap->heap[0];
}

void doTheThingdotCom(Graph G, upDownList U, int u, int v){
	Queue Q = createQueue(2 * 1e6 + 1e3);
	enqueue(Q, 0);

	int i, j;

	int current, myVal;

	int N = G->N;
	int M = G->M;
	U->upDownArray[0 * M + 0] = 0;
	// Dequeue a cell from the queue.
	// Check all adjacent cells that can be reached from the current cell (R, C). If an adjacent cell is within the grid boundaries and has a different height, enqueue it.
	// Update the distance of the adjacent cell if it is not visited or if the new distance is smaller than the previously recorded distance.
	// Mark the adjacent cell as visited.
	int l;
	Heap H;
	while(!isEmpty(Q)){
		l = dequeue(Q);
		i = l / M;
		j = l % M;

		// free(l);
		G->graphArray[l].visited = true;
		
		current = G->graphArray[l].value;
		myVal = U->upDownArray[l];

		H = createHeap(G->N * G->M);

		if(i >= 1){
			// if(G->graphArray[(i - 1) * M + j].visited == false){
			// 	enqueue(Q, (i - 1) * M + j);
			// }

			if(U->upDownArray[(i - 1) * M + j] > myVal){
				// enqueue(Q, (i - 1) * M + j);
				insert(H, (i - 1) * M + j);
				U->upDownArray[(i - 1) * M + j] = U->upDownArray[i * M + j] + 1 * (current != G->graphArray[(i - 1) * M + j].value);
			}
		}
		if(i < N - 1){
			// if(G->graphArray[(i + 1) * M + j].visited == false){
			// 	enqueue(Q, (i + 1) * M + j);
			// }

			if(U->upDownArray[(i + 1) * M + j] > myVal){
				// enqueue(Q, (i + 1) * M + j);
				insert(H, (i + 1) * M + j);
				U->upDownArray[(i + 1) * M + j] = U->upDownArray[i * M + j] + 1 * (current != G->graphArray[(i + 1) * M + j].value);
			}
		}
		if(j >= 1){
			// if(G->graphArray[i * M + (j - 1)].visited == false){
			// 	enqueue(Q, i * M + (j - 1));
			// }

			if(U->upDownArray[i * M + (j - 1)] > myVal){
				// enqueue(Q, i * M + (j - 1));
				insert(H, i * M + (j - 1));
				U->upDownArray[i * M + (j - 1)] = U->upDownArray[i * M + j] + 1 * (current != G->graphArray[i * M + (j - 1)].value);
			}
		}
		if(j < M - 1){
			// if(G->graphArray[i * M + (j + 1)].visited == false){
			// 	enqueue(Q, i * M + (j + 1));
			// }

			if(U->upDownArray[i * M + (j + 1)] > myVal){
				// enqueue(Q, i * M + (j + 1));
				insert(H, i * M + (j + 1));
				U->upDownArray[i * M + (j + 1)] = U->upDownArray[i * M + j] + 1 * (current != G->graphArray[i * M + (j + 1)].value);
			}
		}
		enqueue(Q, getMin(H));
		free(H->heap);
		free(H);
	}
	// free(Q->L);
	// free(Q->rear);
	// free(Q);
}
int main(){
	int T;
	scanf("%d", &T);

	int N, M;
	Graph G;
	upDownList U;

	for(int i = 0; i < T; i++){
		scanf("%d %d", &N, &M);
		G = initGraph(N, M);
		for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				scanf("%d", &G->graphArray[i * M + j].value);
			}
		}
		// printf("%d\n", G->graphArray[0].value);
		U = initUpDownList(N, M);
		doTheThingdotCom(G, U, 0, 0);

		printf("%d\n", U->upDownArray[(N - 1) * M  + M - 1]);
	}
	return 0;
}