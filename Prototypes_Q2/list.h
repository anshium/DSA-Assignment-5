#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct ListNode{
	int x;
	int y;
	struct ListNode* next;
} ListNode;

typedef ListNode* List;
typedef ListNode* listnodeptr;

listnodeptr makeListNode(int x, int y);

listnodeptr removeFromFrontOfList(List L);

void addToBack(List L, int val);



#endif