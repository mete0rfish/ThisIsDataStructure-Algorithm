#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int type;

typedef struct PQNode {
	type Priority;
	void* Data;
}PQNode;

typedef struct PriorityQueue {
	PQNode* Nodes;
	int Capacity;
	int UserdSize;

}PriorityQueue;

PriorityQueue* createPq(int size);
void destroyPq(PriorityQueue* pq);
void enqueuePq(PriorityQueue* pq, PQNode node);
void dequeuePq(PriorityQueue* pq, PQNode* root);
int getParent(int idx);
int getLeftChild(int idx);
void swapNodes(PriorityQueue* pq, int a, int b);
int isEmpty(PriorityQueue* pq);

#endif PRIORITYQUEUE_H
