#include "GraphTraversal.h"

void DFS(Vertex* v) {
	Edge* e = NULL;

	printf("%d ", v->data);
	v->Visited = Visited;

	// �� ������ �������� ���� ���鼭 ����
	e = v->AdjacencyList;
	while (e != NULL) {
		// ������ ���ų�, �湮������ ������ �ߴ�
		if (e->Target != NULL && e->Target->Visited == NotVisited)
			DFS(e->Target);

		e = e->Next;
	}
}

void BFS(Vertex* v, Queue* q) {
	Edge* e;

	printf("%d ", v->Data);
	v->Visited = Visited;

	enqueue(q, createNode(v));

	while (!isEmpty(q)) {
		Node* popped = dequeue(q);
		v = popped->data;
		e = v->AdjacencyList;

		while (e != NULL) {
			v = e->Target;

			if (v != NULL && v->Visited == NotVisited) {
				printf("%d ", v->Data);
				v->Visited = Visited;
				enqueue(q, createNode(v));
			}
			e = e->Next;
		}
	}
}