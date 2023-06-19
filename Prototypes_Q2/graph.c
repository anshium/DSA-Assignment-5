#include "graph.h"
#include <limits.h>

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