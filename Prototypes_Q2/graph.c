#include "graph.h"
#include <limits.h>
#include "queue.h"

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

	while(!isEmpty(Q)){
		listnodeptr l = dequeue(Q);

		i = l->x;
		j = l->y;

		current = G->graphArray[i][j];
		A->AdjacencyMatrixArray[i][j].visited = VISITED;
		// look up if there is a valid block
		if(A->AdjacencyMatrixArray[i][j].top == 1){
			// Then look if it is unvisited
			if(A->AdjacencyMatrixArray[i - 1][j].visited == NOT_VISITED){
				if(A->AdjacencyMatrixArray[i - 1][j].queued == NOT_QUEUED){
					enqueue(Q, i - 1, j);
					A->AdjacencyMatrixArray[i - 1][j].queued = QUEUED;
				}
				// Then check if the current and the top is different, if yes change it to the current value of current in upDownTeller to that + 1
				if(current != G->graphArray[i - 1][j]){
					if(U->upDownArray[i - 1][j] > U->upDownArray[i][j] + 1){
						U->upDownArray[i - 1][j] = U->upDownArray[i][j] + 1; 
					}
				}
				else{
					if(U->upDownArray[i - 1][j] > U->upDownArray[i][j]){
						U->upDownArray[i - 1][j] = U->upDownArray[i][j];
					}
				}
			} else {
				if(current != G->graphArray[i - 1][j]){
					if(U->upDownArray[i - 1][j] > U->upDownArray[i][j] + 1){
						U->upDownArray[i - 1][j] = U->upDownArray[i][j] + 1; 
					}
				}
				else{
					if(U->upDownArray[i - 1][j] > U->upDownArray[i][j]){
						U->upDownArray[i - 1][j] = U->upDownArray[i][j];
					}
				}
			}
		}

		// Do the same things for bellow, left and right
		if(A->AdjacencyMatrixArray[i][j].bottom == 1){
			// Then look if it is unvisited
			if(A->AdjacencyMatrixArray[i + 1][j].visited == NOT_VISITED){
				if(A->AdjacencyMatrixArray[i + 1][j].queued == NOT_QUEUED){
					enqueue(Q, i + 1, j);
					A->AdjacencyMatrixArray[i + 1][j].queued = QUEUED;
				}
				// Then check if the current and the bottom is different, if yes change it to the current value of current in upDownTeller to that + 1
				if(current != G->graphArray[i + 1][j]){
					if(U->upDownArray[i + 1][j] > U->upDownArray[i][j] + 1){
						U->upDownArray[i + 1][j] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i + 1][j] > U->upDownArray[i][j]){
						U->upDownArray[i + 1][j] = U->upDownArray[i][j];
					}
				}
			} else{
				if(current != G->graphArray[i + 1][j]){
					if(U->upDownArray[i + 1][j] > U->upDownArray[i][j] + 1){
						U->upDownArray[i + 1][j] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i + 1][j] > U->upDownArray[i][j]){
						U->upDownArray[i + 1][j] = U->upDownArray[i][j];
					}
				}
			}
		}
		if(A->AdjacencyMatrixArray[i][j].left == 1){
			// Then look if it is unvisited
			if(A->AdjacencyMatrixArray[i][j - 1].visited == NOT_VISITED){
				if(A->AdjacencyMatrixArray[i][j - 1].queued == NOT_QUEUED){
					enqueue(Q, i, j - 1);
					A->AdjacencyMatrixArray[i][j - 1].queued = QUEUED;
				}
				// Then check if the current and the top is different, if yes change it to the current value of current in upDownTeller to that + 1
				if(current != G->graphArray[i][j - 1]){
					if(U->upDownArray[i][j - 1] > U->upDownArray[i][j] + 1){
						U->upDownArray[i][j - 1] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i][j - 1] > U->upDownArray[i][j]){
						U->upDownArray[i][j - 1] = U->upDownArray[i][j];
					}
				}
			} else {
				if(current != G->graphArray[i][j - 1]){
					if(U->upDownArray[i][j - 1] > U->upDownArray[i][j] + 1){
						U->upDownArray[i][j - 1] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i][j - 1] > U->upDownArray[i][j]){
						U->upDownArray[i][j - 1] = U->upDownArray[i][j];
					}
				}
			}
		}
		if(A->AdjacencyMatrixArray[i][j].right == 1){
			// Then look if it is unvisited
			if(A->AdjacencyMatrixArray[i][j + 1].visited == NOT_VISITED){
				if(A->AdjacencyMatrixArray[i][j + 1].queued == NOT_QUEUED){
					enqueue(Q, i, j + 1);
					A->AdjacencyMatrixArray[i][j + 1].queued = QUEUED;
				}
				// Then check if the current and the top is different, if yes change it to the current value of current in upDownTeller to that + 1
				if(current != G->graphArray[i][j + 1]){
					if(U->upDownArray[i][j + 1] > U->upDownArray[i][j] + 1){
						U->upDownArray[i][j + 1] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i][j + 1] > U->upDownArray[i][j]){
						U->upDownArray[i][j + 1] = U->upDownArray[i][j];
					}
				}
			} else {
				if(current != G->graphArray[i][j + 1]){
					if(U->upDownArray[i][j + 1] > U->upDownArray[i][j] + 1){
						U->upDownArray[i][j + 1] = U->upDownArray[i][j] + 1;
					}
				}
				else{
					if(U->upDownArray[i][j + 1] > U->upDownArray[i][j]){
						U->upDownArray[i][j + 1] = U->upDownArray[i][j];
					}
				}
			}
		}
	}
}