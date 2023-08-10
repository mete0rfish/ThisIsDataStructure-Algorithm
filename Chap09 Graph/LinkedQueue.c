#include "LinkedQueue.h"

void createQueue(Queue** q) {
	(*q) = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	(*q)->front = NULL;
	(*q)->rear = NULL;
	(*q)->count = 0;
}
void destroyQueue(Queue* q) {
	while (!isEmpty(q)) {
		Node* popped = dequeue(q);
		destroyNode(popped);
	}
	free(q);
}

Node* createNode(vertex* v) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = v;
	newNode->nextNode = NULL;

	return newNode;
}
void destroyNode(Node* node) {
	free(node);
}

void enqueue(Queue* q, Node* newNode) {
	if (q->front == NULL) {
		q->front = newNode;
		q->rear = newNode;
		q->count++;
	}
	else {
		q->rear->nextNode = newNode;
		q->rear = newNode;
		q->count++;
	}
}
Node* dequeue(Queue* q) {
	Node* front = q->front;

	if (q->front->nextNode == NULL) {
		q->front = NULL;
		q->rear = NULL;
	}
	else {
		q->front = q->front->nextNode;
	}

	q->count--;
	return front;
}

int isEmpty(Queue* q) {
	return (q->front == NULL);
}