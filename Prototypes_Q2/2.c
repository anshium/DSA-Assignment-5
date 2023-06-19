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

	doTheThingdotCom(Graph G, upDownList);
	pick up one element
	update all valid with the up down thingy if that is less

	for all elements adjacent to it:
		if(not visited)
			put them in a queue
	
	as easy as that

	return 0;
}