#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Graph_Structure{
	struct Node** startList;
	int num_vertices;
} Graph_Structure;

typedef struct Node{
	int val;
	int visited;
	struct Node* next;
} Node;

typedef Graph_Structure* Graph;
typedef Node* nodeptr;

typedef int* Array;

Graph initGraph(int num_vertices){
	Graph g = (Graph)malloc(sizeof(Graph_Structure));
	g->startList = (Node**)malloc(sizeof(Node*) * num_vertices);
	g->num_vertices = num_vertices;
	for(int i = 0; i < num_vertices; i++){
		g->startList[i] = (Node*)malloc(sizeof(Node));
	}

	return g;
}

Node* createNode(int val){
	Node* n = (Node*)malloc(sizeof(Node));
	n->val = val;
	n->visited = 0;
	n->next = NULL;

	return n;
}

// One indexing done (also handles exceptions)
int addUndirectedEdge(Graph g, int u, int v){
	nodeptr one = createNode(u);
	assert(one != NULL);
	one->next = g->startList[v - 1];
	g->startList[v - 1] = one;

	nodeptr two = createNode(v);
	assert(two != NULL);
	two->next = g->startList[u - 1];
	g->startList[u - 1] = two;

	return 1;	
}

// The function that does the work that we have to perform
Array doTheTask(Graph g){
	Array journal = (Array)malloc(sizeof(int) * g->num_vertices);
	assert(journal != NULL);

	journal[0] = g->startList[0]->val; // Basically 1

	g->startList[0]->visited = 1;

	for(int i = 1; i < g->num_vertices; i++){
		
	}

	return journal;
}

int main(){

	return 0;
}