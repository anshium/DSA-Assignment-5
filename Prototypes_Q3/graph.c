#include "graph.h"
#include "queue.h"
#include <limits.h>

Graph initGraph(int N, int M){
	Graph G = (Graph)malloc(sizeof(stGraph));
	G->N = N;
	G->M = M;
	G->graphArray = (int**)malloc(sizeof(int) * N);
	for(int i = 0; i < N; i++){
		G->graphArray[i] = (int*)malloc(sizeof(int) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			G->graphArray[i][j] = 0;
		}
	}

	return G;
}

AdjacencyMatrix initAdjacencyMatrix(int N, int M){
	AdjacencyMatrix A = (AdjacencyMatrix)malloc(sizeof(stAdjacencyMatrix));
	A->AdjacencyMatrixArray = (upDownTeller**)malloc(sizeof(upDownTeller*) * N);
	for(int i = 0; i < N; i++){
		A->AdjacencyMatrixArray[i] = (upDownTeller*)malloc(sizeof(upDownTeller) * M);
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
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

// Codes:
/**
 * 0 = Not-Fertile
 * 1 = Fertile
 * 2 = Not-Fertile-Visited
 * 3 = Fertile-Visited
 * **/

void addFertility(Graph G, int u, int v){
	G->graphArray[u][v] = FERTILE;
}

int dfs(Graph G, AdjacencyMatrix A, Queue Q, int u, int v){
	int type = G->graphArray[u][v];
	int cost = 0;
	if(G->graphArray[u][v] == FERTILE){
		cost += 4;
	}
	// Denoting visited or not
	if(type < 2){
		G->graphArray[u][v] += 2;
	} else{
		return 0;
	}
	

	if(A->AdjacencyMatrixArray[u][v].top == 1){
		if(G->graphArray[u - 1][v] != 2 && G->graphArray[u - 1][v] != 3){
			if(G->graphArray[u - 1][v] != type % 2){
				// enqueue(Q, u - 1, v);
				cost -= 1;
			}
			else{
				cost += dfs(G, A, Q, u - 1, v);
			}
		}
	} else{
		cost -= 1;
	}
	if(A->AdjacencyMatrixArray[u][v].bottom == 1){
		if(G->graphArray[u + 1][v] != 2 && G->graphArray[u + 1][v] != 3){
			if(G->graphArray[u + 1][v] != type % 2){
				// enqueue(Q, u + 1, v);
				cost -= 1;
			}
			else{
				cost += dfs(G, A, Q, u + 1, v);
			}
		}
	} else{
		cost -= 1;
	}
	if(A->AdjacencyMatrixArray[u][v].left == 1){
		if(G->graphArray[u][v - 1] != 2 && G->graphArray[u][v - 1] != 3){
			if(G->graphArray[u][v - 1] != type % 2){
				// enqueue(Q, u, v - 1);
				cost -= 1;
			}
			else{
				cost += dfs(G, A, Q, u, v - 1);
			}
		}
	} else{
		cost -= 1;
	}
	if(A->AdjacencyMatrixArray[u][v].right == 1){
		if(G->graphArray[u][v + 1] != 2 && G->graphArray[u][v + 1] != 3){
			if(G->graphArray[u][v + 1] != type % 2){
				// enqueue(Q, u, v + 1);
				cost -= 1;
			}
			else{
				cost += dfs(G, A, Q, u, v + 1);
			}
		}
	} else{
		cost -= 1;
	}

	return cost;
}

int solution(Graph G, AdjacencyMatrix A){
	listnodeptr l;
	int max_cost = INT_MIN;
	int cost = 0;
	
	Queue Q = createQueue();
	// enqueue(Q, 0, 0);
	// while(!isEmpty(Q)){
	// 	l = dequeue(Q);
	// 	cost = dfs(G, A, Q, l->x, l->y);
	// 	if(G->graphArray[l->x][l->y] % 2 == FERTILE){
	// 		if(cost > max_cost){
	// 			max_cost = cost;
	// 		}
	// 	}
	// }

	for(int i = 0; i < G->N; i++){
		for(int j = 0; j < G->M; j++){
			if(G->graphArray[i][j] == FERTILE){
				cost = dfs(G, A, Q, i, j);
			}
			if(cost > max_cost){
				max_cost = cost;
			}
		}
	}

	return max_cost;
}

