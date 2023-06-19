#include "graph.h"

// Add testcases also

void print(upDownList U){
	for(int i = 0; i < U->N; i++){
		for(int j = 0; j < U->M; j++){
			printf("%d ", U->upDownArray[i][j]);
		}
		printf("\n");
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

	printf("\n");
	
	print(U);

	printf("%d\n", U->upDownArray[N - 1][M - 1]);

	return 0;
}