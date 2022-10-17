#pragma once
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagHeapNode {
	ElementType Data;
}HeapNode;

typedef struct tagHeap {
	HeapNode* Nodes;
	int Capacity; // Nodes 배열의 크기
	int UsedSize; // 실제 배열 안에 든 큐 요소의 수
}Heap;

Heap* HEAP_Create(int InitialSize);
void HEAP_Destroy(Heap* H);
void HEAP_Insert(Heap* H, ElementType NewData);
void HEAP_DeleteMin(Heap* H, HeapNode* Root);
int HEAP_GetParent(int Index);
int HEAP_GetLeftChild(int Index);
void HEAP_SwapNodes(Heap* H, int Index1, int Index2);
void HEAP_PrintNodes(Heap* H);


#endif // !HEAP_H
