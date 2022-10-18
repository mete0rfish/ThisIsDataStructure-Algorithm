#pragma once
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef int PriorityType;

typedef struct tagPQNode {
	PriorityType Priority;
	void* Data;
}PQNode;

typedef struct tagPriorityQueue {
	PQNode* Nodes;
	int Capacity; // Nodes 배열의 크기
	int UsedSize; // 실제 배열 안에 든 큐 요소의 수
}PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize);
void PQ_Destroy(PriorityQueue* PQ);
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewData);
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root);
int PQ_GetParent(int Index);
int PQ_GetLeftChild(int Index);
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2);
void PQ_PrintNodes(PriorityQueue* PQ);
int PQ_IsEmpty(PriorityQueue* PQ);


#endif // !HEAP_H
