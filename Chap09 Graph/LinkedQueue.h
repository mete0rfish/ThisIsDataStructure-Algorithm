#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

typedef struct tagNode {
	Vertex* data;
	struct tagNode* nextNode;
}Node;

typedef struct tagLinkedQueue {
	Node* front;
	Node* rear;
	int count;
}Queue;

void createQueue(Queue** q);
void destroyQueue(Queue* q);

Node* createNode(Vertex* newData);
void destroyNode(Node* node);

void enqueue(Queue* q, Node* newNode);
Node* dequeue(Queue* q);

int isEmpty(Queue* q);

#endif