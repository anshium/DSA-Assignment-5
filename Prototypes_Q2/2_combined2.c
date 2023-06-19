#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode{
	int x;
	int y;
	struct ListNode* next;
} ListNode;

typedef ListNode* List;
typedef ListNode* listnodeptr;

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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct GraphNode{
	int N;
	int M;
	int** graphArray;
} GraphNode;

typedef GraphNode* Graph;

Graph initGraph(int N, int M);

// Although I could have reused the graph declaration, I would be making a separate upDownList

typedef struct upDownListNode{
	int N;
	int M;
	int** upDownArray;
} upDownListNode;

typedef upDownListNode* upDownList;

#define NOT_VISITED 0
#define VISITED 1

#define QUEUED 1
#define NOT_QUEUED 0

// If 1, then you can visit that part, else no
typedef struct upDownTeller{
	int visited;
	int queued;
	int left;
	int right;
	int top;
	int bottom;
} upDownTeller;

typedef struct stAdjacencyMatrix{
	int N;
	int M;
	upDownTeller** AdjacencyMatrixArray;
} stAdjacencyMatrix;

typedef stAdjacencyMatrix* AdjacencyMatrix;

AdjacencyMatrix initAdjacencyMatrix(int N, int M);

upDownList initUpDownList(int N, int M);

void doTheThingdotCom(Graph G, upDownList U, AdjacencyMatrix A, int u, int v);

Graph initGraph(int N, int M){
	Graph G = (Graph)malloc(sizeof(GraphNode));
	G->N = N;
	G->M = M;

	G->graphArray = (int**)malloc(sizeof(int*) * N);
	for(int i = 0; i < N; i++){
		G->graphArray[i] = (int*)malloc(sizeof(int) * M);
	}

	return G;
}

upDownList initUpDownList(int N, int M){
	upDownList U = (upDownList)malloc(sizeof(upDownListNode));
	U->N = N;
	U->M = M;

	U->upDownArray = (int**)malloc(sizeof(int*) * N);
	for(int i = 0; i < N; i++){
		U->upDownArray[i] = (int*)malloc(sizeof(int) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			U->upDownArray[i][j] = INT_MAX;
		}
	}

	return U;
}

AdjacencyMatrix initAdjacencyMatrix(int N, int M){
	AdjacencyMatrix A = (AdjacencyMatrix)malloc(sizeof(stAdjacencyMatrix));
	A->AdjacencyMatrixArray = (upDownTeller**)malloc(sizeof(upDownTeller*) * N);
	for(int i = 0; i < N; i++){
		A->AdjacencyMatrixArray[i] = (upDownTeller*)malloc(sizeof(upDownTeller) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			A->AdjacencyMatrixArray[i][j].visited = NOT_VISITED;
			A->AdjacencyMatrixArray[i][j].queued = NOT_QUEUED;
			if(i != 0){
				A->AdjacencyMatrixArray[i][j].top = 1;
			} else{
				A->AdjacencyMatrixArray[i][j].top = 0;
			}

			if(i != N - 1){
				A->AdjacencyMatrixArray[i][j].bottom = 1;
			} else{
				A->AdjacencyMatrixArray[i][j].bottom = 0;
			}

			if(j != 0){
				A->AdjacencyMatrixArray[i][j].left = 1;
			} else {
				A->AdjacencyMatrixArray[i][j].left = 0;
			}

			if(j != M - 1){
				A->AdjacencyMatrixArray[i][j].right = 1;
			} else {
				A->AdjacencyMatrixArray[i][j].right = 0;
			}
		}
	}

	return A;
}

// pick up one element
// update all valid non-visited with the up down thingy if that is less

// for all elements adjacent to it:
// 	if(not visited)
// 		put them in a queue

// as easy as that

void doTheThingdotCom(Graph G, upDownList U, AdjacencyMatrix A, int u, int v){
	Queue Q = createQueue();
	enqueue(Q, 0, 0);

	int i, j;

	int current;

	U->upDownArray[0][0] = 0;

	// Dequeue a cell from the queue.
	// Check all adjacent cells that can be reached from the current cell (R, C). If an adjacent cell is within the grid boundaries and has a different height, enqueue it.
	// Update the distance of the adjacent cell if it is not visited or if the new distance is smaller than the previously recorded distance.
	// Mark the adjacent cell as visited.

	while(!isEmpty(Q)){
		listnodeptr l = dequeue(Q);
		int i = l->x;
		int j = l->y;
		
		int current = G->graphArray[i][j];
		int myVal = U->upDownArray[i][j];


		if(A->AdjacencyMatrixArray[i][j].top == 1){
			if(current != G->graphArray[i - 1][j]){
				enqueue(Q, i - 1, j);
			}

			if(A->AdjacencyMatrixArray[i - 1][j].visited == NOT_VISITED || U->upDownArray[i - 1][j] > myVal){
				U->upDownArray[i - 1][j] = U->upDownArray[i][j] + 1;
			}
		}
		if(A->AdjacencyMatrixArray[i][j].bottom == 1){
			if(current != G->graphArray[i + 1][j]){
				enqueue(Q, i + 1, j);
			}
		}
		if(A->AdjacencyMatrixArray[i][j].left == 1){
			if(current != G->graphArray[i][j - 1]){
				enqueue(Q, i, j - 1);
			}
		}
		if(A->AdjacencyMatrixArray[i][j].right == 1){
			if(current != G->graphArray[i][j + 1]){
				enqueue(Q, i, j + 1);
			}
		}
	}
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	Graph G = initGraph(N, M);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			scanf("%d", &G->graphArray[i][j]);
		}
	}

	upDownList U = initUpDownList(N, M);
	AdjacencyMatrix A = initAdjacencyMatrix(N, M);

	doTheThingdotCom(G, U, A, 0, 0);
	printf("%d\n", U->upDownArray[N - 1][M - 1]);
	return 0;
}