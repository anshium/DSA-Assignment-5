#include <stdio.h>
#include <stdlib.h>

typedef struct Graph_Structure{
	struct Node** startList;
	int num_vertices;
} Graph_Structure;

typedef struct Node{
	int val;
	struct Node* next;
} Node;

typedef Graph_Structure* Graph;
typedef Node* nodeptr;

Graph initGraph(int num_vertices){
	Graph g = (Graph)malloc(sizeof(Graph_Structure));
	g->startList = (Node**)malloc(sizeof(Node*) * num_vertices);
	g->num_vertices = num_vertices;
	for(int i = 0; i < num_vertices; i++){
		g->startList[i] = (Node*)malloc(sizeof(Node));
	}

	return g;
}



int main(){

	return 0;
}