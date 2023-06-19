#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

upDownList initUpDownList(int N, int M);

#endif