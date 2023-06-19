#include "graph.h"

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

