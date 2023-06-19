#include "graph.h"

// Add testcases also

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	Graph G = initGraph(N, M);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			scanf("%d", &G->graphArray[i][j]);
		}
	}

	

	return 0;
}