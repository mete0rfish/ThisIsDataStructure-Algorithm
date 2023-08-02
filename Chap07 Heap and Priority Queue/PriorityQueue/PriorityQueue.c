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

	// 1. 부모와 비교하면서 자신이 작으면 교환
	while (curIdx > 0 && pq->Nodes[curIdx].Priority < pq->Nodes[parentIdx].Priority) {
		swapNodes(pq, curIdx, parentIdx);

		curIdx = parentIdx;
		parentIdx = getParent(curIdx);
	}

	pq->UserdSize++;
}

void dequeuePq(PriorityQueue* pq, PQNode* root) {
	int p = 0, l = 0, r = 0;

	// 1. 최고 깊이 최소값 노드를 루트 노드로
	memcpy(root, &pq->Nodes[0], sizeof(PQNode));
	memset(&pq->Nodes[0],0, sizeof(PQNode));

	pq->UserdSize--;
	swapNodes(pq, pq->UserdSize, 0);

	l = getLeftChild(0);
	r = l + 1;

	// 2. 자식과 비교하면서, 자신이 더 크면 교환
	while (1) {
		int selected = 0;

		// 2.1 자식이 없으면 패스
		if (l >= pq->UserdSize)	break;

		// 2.2 왼쪽 자식만 있으면 왼쪽 선택
		if (r >= pq->UserdSize) {
			selected = l;
		}
		// 2.3 자식이 둘다 있는 경우, 가장 우선순위가 작은 자식 선택
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