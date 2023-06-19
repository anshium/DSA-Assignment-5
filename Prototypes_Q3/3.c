#include "graph.h"
#include "queue.h"

int main(){
	int N, M, R;
	scanf("%d %d %d", &N, &M, &R);
	
	Graph G = initGraph(N, M);
	AdjacencyMatrix A = initAdjacencyMatrix(N, M);
	
	int u, v;

	for(int i = 0; i < R; i++){
		scanf("%d %d", &u, &v);
		addFertility(G, u - 1, v - 1); // 1-indexing is used in the input
	}

	int cost = solution(G, A);

	printf("%d\n", cost);

	return 0;
}