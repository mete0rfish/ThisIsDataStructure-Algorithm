#include "PriorityQueue.h"

PriorityQueue* createPq(int size) {
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->Capacity = size;
	pq->UserdSize = 0;
	pq->Nodes = (PQNode*)malloc(sizeof(PQNode) * size);

	return pq;
}

void destroyPq(PriorityQueue* pq) {
	free(pq->Nodes);
	free(pq);
}

void enqueuePq(PriorityQueue* pq, PQNode node) {
	int curIdx = pq->UserdSize;
	int parentIdx = getParent(curIdx);

	if (curIdx == pq->Capacity) {
		if (pq->Capacity == 0)	pq->Capacity = 1;

		pq->Capacity *= 2;
		pq->Nodes = (PQNode*)realloc(pq->Nodes, sizeof(PQNode)*pq->Capacity);
	}

	pq->Nodes[pq->UserdSize] = node;

	// 1. �θ�� ���ϸ鼭 �ڽ��� ������ ��ȯ
	while (curIdx > 0 && pq->Nodes[curIdx].Priority < pq->Nodes[parentIdx].Priority) {
		swapNodes(pq, curIdx, parentIdx);

		curIdx = parentIdx;
		parentIdx = getParent(curIdx);
	}

	pq->UserdSize++;
}

void dequeuePq(PriorityQueue* pq, PQNode* root) {
	int p = 0, l = 0, r = 0;

	// 1. �ְ� ���� �ּҰ� ��带 ��Ʈ ����
	memcpy(root, &pq->Nodes[0], sizeof(PQNode));
	memset(&pq->Nodes[0],0, sizeof(PQNode));

	pq->UserdSize--;
	swapNodes(pq, pq->UserdSize, 0);

	l = getLeftChild(0);
	r = l + 1;

	// 2. �ڽİ� ���ϸ鼭, �ڽ��� �� ũ�� ��ȯ
	while (1) {
		int selected = 0;

		// 2.1 �ڽ��� ������ �н�
		if (l >= pq->UserdSize)	break;

		// 2.2 ���� �ڽĸ� ������ ���� ����
		if (r >= pq->UserdSize) {
			selected = l;
		}
		// 2.3 �ڽ��� �Ѵ� �ִ� ���, ���� �켱������ ���� �ڽ� ����
		else {
			if (pq->Nodes[l].Priority > pq->Nodes[r].Priority)
				selected = r;
			else
				selected = l;
		}

		if (pq->Nodes[selected].Priority < pq->Nodes[p].Priority) {
			swapNodes(pq, selected, p);
			p = selected;
		}
		else
			break;

		l = getLeftChild(p);
		r = l + 1;
	}

	if (pq->UserdSize < (pq->Capacity / 2)) {
		pq->Capacity /= 2;
		pq->Nodes = (PQNode*)realloc(pq->Nodes, sizeof(PQNode) * pq->Capacity);
	}
}

int getParent(int idx) {
	return (int)((idx - 1) / 2);
}

int getLeftChild(int idx) {
	return (idx * 2) + 1;
}

void swapNodes(PriorityQueue* pq, int a, int b) {
	
	int NodeSize = sizeof(PQNode);
	PQNode* tmp = (PQNode*)malloc(NodeSize);

	memcpy(tmp, &pq->Nodes[a], NodeSize);
	memcpy(&pq->Nodes[a], &pq->Nodes[b], NodeSize);
	memcpy(&pq->Nodes[b], tmp, NodeSize);
	
	free(tmp);
}

int isEmpty(PriorityQueue* pq) {
	return (pq->UserdSize == 0);
}