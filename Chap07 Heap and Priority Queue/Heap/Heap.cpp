#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

using namespace std;
#define MAX 100001

typedef struct Node {
	int Data;
}Node;

typedef struct Heap {
	Node* Nodes;
	int Capacity;
	int UsedSize;
}Heap;

void swapNode(Heap* h, int a, int b) {
	int Size = sizeof(Node);
	Node* tmpNode = (Node*)malloc(sizeof(Node));

	memcpy(tmpNode, &h->Nodes[a], Size);
	memcpy(&h->Nodes[a], &h->Nodes[b], Size);
	memcpy(&h->Nodes[b], tmpNode, Size);

	free(tmpNode);
}

int getParent(int idx) {
	return (int)((idx - 1) / 2);
}

int getLeftChild(int parent) {
	return (2 * parent) + 1;
}

Heap* createHeap(int capacity) {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	heap->Capacity = capacity;
	heap->UsedSize = 0;
	heap->Nodes = (Node*)malloc(sizeof(Node) * capacity);

	printf("Heap Created! Capacity: %d\n", capacity);
	return heap;
}

void destroyHeap(Heap* heap) {
	free(heap->Nodes);
	free(heap);

	printf("Heap Destroyed!\n");
}

void insertNode(Heap* h, int data) {
	int curIdx = h->UsedSize;
	int parentIdx = getParent(curIdx);

	if (h->UsedSize == h->Capacity) {
		h->Capacity *= 2;
		h->Nodes = (Node*)realloc(h->Nodes, sizeof(Node) * h->Capacity);

		printf("Heap Realloced! Capacity: %d\n", h->Capacity);
	}

	// 1. 최고 깊이 오른쪽 노드에 삽입
	h->Nodes[curIdx].Data = data;

	// 2. 부모와 비교하면서, 자신이 더 작으면 Swap
	while (curIdx > 0 && h->Nodes[curIdx].Data < h->Nodes[parentIdx].Data) {
		swapNode(h, curIdx, parentIdx);

		curIdx = parentIdx;
		parentIdx = getParent(curIdx);
	}

	h->UsedSize++;


}

void deleteMinNode(Heap* h, Node* root) {
	int parent = 0;
	int l = 0;
	int r = 0;
	
	// 1. 최고 깊이 노드를 루트 노드로
	memcpy(root, &h->Nodes[0], sizeof(Node));
	memset(&h->Nodes[0], 0, h->UsedSize);

	h->UsedSize--;
	swapNode(h, 0, h->UsedSize);

	l = getLeftChild(0);
	r = l + 1;

	// 2. 왼쪽, 오른쪽 비교하면서 내려가기

	while (1) {
		int child = 0;
		if (l >= h->UsedSize)	break;
		
		if (r >= h->UsedSize) {
			child = l;
		}
		else {
			if (h->Nodes[l].Data > h->Nodes[r].Data)
				child = r;
			else
				child = l;
		}

		if (h->Nodes[child].Data < h->Nodes[parent].Data) {
			swapNode(h, child, parent);
			parent = child;
		}
		else
		{
			break;
		}

		l = getLeftChild(parent);
		r = l+1;

		if (h->UsedSize < (h->Capacity / 2)) {
			h->Capacity /= 2;
			h->Nodes = (Node*)realloc(h->Nodes, sizeof(Node) * h->Capacity);
		}

	}
}

void printNodes(Heap* h) {
	for (int i = 0; i < h->UsedSize; i++) {
		printf("%d ", h->Nodes[i]);
	}
	printf("\n");
}

int main() {
	Heap* h = createHeap(3);
	Node minNode;

	insertNode(h, 12);
	insertNode(h, 87);
	insertNode(h, 111);
	insertNode(h, 34);
	insertNode(h, 16);
	insertNode(h, 75);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	deleteMinNode(h, &minNode);
	printNodes(h);

	return 0;
}
