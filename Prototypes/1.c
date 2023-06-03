#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

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

	for(int i = 0; i < num_vertices; i++){
		g->startList[i] = NULL;
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

Node* findMinimumUnvisited(Graph g, int from){
	nodeptr p = g->startList[from - 1];

	int minimum = INT_MAX;
	nodeptr min_node = NULL;
	nodeptr tempNode = NULL;
	int test = 0;
	while(p != NULL){
		if(g->startList[p->val - 1]->visited == 0){ // or simple initial p->visited
			tempNode = p;
			test = p->val;
		} else{
			tempNode = findMinimumUnvisited(g, p->val);
			test = tempNode->val;
		}

		if(test < minimum){
			minimum = test;
			min_node = tempNode;
		}
		p = p->next;
	}

	return min_node;
}

// The function that does the work that we have to perform
Array doTheTask(Graph g){
	Array journal = (Array)malloc(sizeof(int) * g->num_vertices);
	assert(journal != NULL);

	journal[0] = 1;

	g->startList[0]->visited = 1;

	/*
		nodeptr t = findMinimumUnvisited(journal[0]);
		journal[1] = t->val;
		nodeptr s = findMinimumUnvisited(journal[1]);
		journal[2] = s->val;

		// Do this until the journal is full
	*/
	int from = 1;
	int index = 1;
	for(int i = 1; i < g->num_vertices; i++){
		nodeptr minNode = findMinimumUnvisited(g, from);
		int temp = minNode->val;
		g->startList[minNode->val - 1]->visited = 1;
		journal[index] = temp;

		from = temp;
		index++;
	}

	return journal;
}

void printGraph(Graph g){
	for(int i = 0; i < g->num_vertices; i++){
		nodeptr p = g->startList[i];
		while(p != NULL){
			printf("(%d -> %d) ", i + 1, p->val);
			p = p->next;
		}
		printf("\n");
	}
}

int main(){
	Graph g = initGraph(5);
	addUndirectedEdge(g, 1, 4);
	addUndirectedEdge(g, 3, 4);
	addUndirectedEdge(g, 5, 4);
	addUndirectedEdge(g, 3, 2);
	addUndirectedEdge(g, 1, 5);

	printGraph(g);

	return 0;
}