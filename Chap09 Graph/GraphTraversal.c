#include "GraphTraversal.h"

void DFS(Vertex* v) {
	Edge* e = NULL;

	printf("%d ", v->data);
	v->Visited = Visited;

	// 한 정점의 간선들을 쭉쭉 들어가면서 본다
	e = v->AdjacencyList;
	while (e != NULL) {
		// 간선이 없거나, 방문한적이 있으면 중단
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