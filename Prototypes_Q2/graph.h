#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "queue.h"

typedef struct GraphNode{
	int N;
	int M;
	int** graphArray;
} GraphNode;

typedef GraphNode* Graph;

Graph initGraph(int N, int M);

// Although I could have reused the graph declaration, I would be making a separate upDownList

typedef struct upDownListNode{
	int N;
	int M;
	int** upDownArray;
} upDownListNode;

typedef upDownListNode* upDownList;

#define NOT_VISITED 0
#define VISITED 1

#define QUEUED 1
#define NOT_QUEUED 0

// If 1, then you can visit that part, else no
typedef struct upDownTeller{
	int visited;
	int queued;
	int left;
	int right;
	int top;
	int bottom;
} upDownTeller;

typedef struct stAdjacencyMatrix{
	int N;
	int M;
	upDownTeller** AdjacencyMatrixArray;
} stAdjacencyMatrix;

typedef stAdjacencyMatrix* AdjacencyMatrix;

AdjacencyMatrix initAdjacencyMatrix(int N, int M);

upDownList initUpDownList(int N, int M);

void doTheThingdotCom(Graph G, upDownList U, AdjacencyMatrix A, int u, int v);

#endif