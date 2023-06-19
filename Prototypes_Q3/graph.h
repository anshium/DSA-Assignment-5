#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

typedef struct stGraph{
	int N;
	int M;
	int** graphArray;
} stGraph;

typedef stGraph* Graph;

// If 1, then you can visit that part, else no
typedef struct upDownTeller{
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

Graph initGraph(int N, int M);

AdjacencyMatrix initAdjacencyMatrix(int N, int M);

// Codes:
/**
 * 0 = Not-Fertile
 * 1 = Fertile
 * 2 = Not-Fertile-Visited
 * 3 = Fertile-Visited
 * **/

#define NOT_FERTILE 0
#define FERTILE 1
#define NOT_FERTILE_VISITED 2
#define FERTILE_VISITED 3

void addFertility(Graph G, int u, int v);

int dfs(Graph G, AdjacencyMatrix A, Queue Q, int u, int v);

int solution(Graph G, AdjacencyMatrix A);

#endif