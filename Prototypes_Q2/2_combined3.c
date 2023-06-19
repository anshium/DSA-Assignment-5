// Steps taken to remove MLE
// No more adjacency lists
// Graph would have each node as a struct that would store visited and value

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
	listnodeptr rear;
} QueueInfo;

typedef QueueInfo* Queue;
typedef Queue queueptr;

Queue createQueue();

void enqueue(Queue Q, int x, int y);

listnodeptr dequeue(Queue Q);

void printQueue(Queue Q);

bool isEmpty(Queue Q);

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

bool isEmpty(Queue Q){
	if(Q->num_elems == 0){
		return true;
	}
	return false;
}

typedef struct holder{
	short value;
	bool visited;
} holder;

typedef struct GraphNode{
	int N;
	int M;
	holder** graphArray;
} GraphNode;

typedef GraphNode* Graph;

Graph initGraph(int N, int M);

// Although I could have reused the graph declaration, I would be making a separate upDownList

typedef struct upDownListNode{
	int N;
	int M;
	short** upDownArray;
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

	G->graphArray = (holder**)malloc(sizeof(holder*) * N);
	for(int i = 0; i < N; i++){
		G->graphArray[i] = (holder*)malloc(sizeof(holder) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			G->graphArray[i][j].value = false;
		}
	}

	return G;
}

upDownList initUpDownList(int N, int M){
	upDownList U = (upDownList)malloc(sizeof(upDownListNode));
	U->N = N;
	U->M = M;

	U->upDownArray = (short**)malloc(sizeof(short*) * N);
	for(int i = 0; i < N; i++){
		U->upDownArray[i] = (short*)malloc(sizeof(short) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			U->upDownArray[i][j] = 32767;
		}
	}

	return U;
}

// pick up one element
// update all valid non-visited with the up down thingy if that is less

// for all elements adjacent to it:
// 	if(not visited)
// 		put them in a queue

// as easy as that

void doTheThingdotCom(Graph G, upDownList U, int u, int v){
	Queue Q = createQueue();
	enqueue(Q, 0, 0);

	int i, j;

	short current, myVal;

	U->upDownArray[0][0] = 0;
	int N = G->N;
	int M = G->M;
	// Dequeue a cell from the queue.
	// Check all adjacent cells that can be reached from the current cell (R, C). If an adjacent cell is within the grid boundaries and has a different height, enqueue it.
	// Update the distance of the adjacent cell if it is not visited or if the new distance is smaller than the previously recorded distance.
	// Mark the adjacent cell as visited.
	while(!isEmpty(Q)){
		listnodeptr l = dequeue(Q);
		i = l->x;
		j = l->y;
		// free(l);
		G->graphArray[i][j].visited = true;
		
		current = G->graphArray[i][j].value;
		myVal = U->upDownArray[i][j];


		if(i >= 1){
			if(G->graphArray[i - 1][j].visited == false){
				enqueue(Q, i - 1, j);
			}

			if(U->upDownArray[i - 1][j] > myVal){
				enqueue(Q, i - 1, j);
				U->upDownArray[i - 1][j] = U->upDownArray[i][j] + 1 * (current != G->graphArray[i - 1][j].value);
			}
		}
		if(i < N - 1){
			if(G->graphArray[i + 1][j].visited == false){
				enqueue(Q, i + 1, j);
			}

			if(U->upDownArray[i + 1][j] > myVal){
				enqueue(Q, i + 1, j);
				U->upDownArray[i + 1][j] = U->upDownArray[i][j] + 1 * (current != G->graphArray[i + 1][j].value);
			}
		}
		if(j >= 1){
			if(G->graphArray[i][j - 1].visited == false){
				enqueue(Q, i, j - 1);
			}

			if(U->upDownArray[i][j - 1] > myVal){
				enqueue(Q, i, j - 1);
				U->upDownArray[i][j - 1] = U->upDownArray[i][j] + 1 * (current != G->graphArray[i][j - 1].value);
			}
		}
		if(j < M - 1){
			if(G->graphArray[i][j + 1].visited == false){
				enqueue(Q, i, j + 1);
			}

			if(U->upDownArray[i][j + 1] > myVal){
				enqueue(Q, i, j + 1);
				U->upDownArray[i][j + 1] = U->upDownArray[i][j] + 1 * (current != G->graphArray[i][j + 1].value);
			}
		}
	}
	// free(Q->L);
	// free(Q->rear);
	// free(Q);
}

void print(upDownList U){
	for(int i = 0; i < U->N; i++){
		for(int j = 0; j < U->M; j++){
			printf("%d ", U->upDownArray[i][j]);
		}
		printf("\n");
	}
}

void freeGraph(Graph G){
	for(int i = 0; i < G->N; i++){
		free(G->graphArray[i]);
	}

	free(G);
}

void freeUDL(upDownList U){
	for(int i = 0; i < U->N; i++){
		free(U->upDownArray[i]);
	}

	free(U);
}

int main(){
	int T;
	scanf("%d", &T);

	int N, M;
	Graph G;
	upDownList U;

	// for(int i = 0; i < T; i++){
		scanf("%d %d", &N, &M);
		G = initGraph(N, M);
		for(int i = 0; i < N; i++){
			for(int j = 0; j < M; j++){
				scanf("%hi", &G->graphArray[i][j]);
			}
		}

		U = initUpDownList(N, M);
		doTheThingdotCom(G, U, 0, 0);

		// printf("\n");
		
		// print(U);

		printf("%d\n", U->upDownArray[N - 1][M - 1]);

		// freeGraph(G);
		// freeUDL(U);
	// }
	return 0;
}