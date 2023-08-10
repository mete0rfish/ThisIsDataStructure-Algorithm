#include "Graph.h"
#include "GraphTraversal.h"

int main(void) {
	int  Mode = 0;
	Graph* g = CreateGraph();

	Vertex* v1 = CreateVertex(1);
	Vertex* v2 = CreateVertex(2);
	Vertex* v3 = CreateVertex(3);
	Vertex* v4 = CreateVertex(4);
	Vertex* v5 = CreateVertex(5);
	Vertex* v6 = CreateVertex(6);
	Vertex* v7 = CreateVertex(7);

	AddVertex(g, v1);
	AddVertex(g, v2);
	AddVertex(g, v3);
	AddVertex(g, v4);
	AddVertex(g, v5);
	AddVertex(g, v6);
	AddVertex(g, v7);

	AddEdge(v1, CreateEdge(v1, v2, 0));
	AddEdge(v1, CreateEdge(v1, v3, 0));

	AddEdge(v2, CreateEdge(v2, v4, 0));
	AddEdge(v2, CreateEdge(v2, v5, 0));

	AddEdge(v3, CreateEdge(v3, v4, 0));
	AddEdge(v3, CreateEdge(v3, v6, 0));


	AddEdge(v4, CreateEdge(v4, v5, 0));
	AddEdge(v4, CreateEdge(v4, v7, 0));


	AddEdge(v5, CreateEdge(v5, v7, 0));

	AddEdge(v6, CreateEdge(v6, v7, 0));

	printf("Enter Traversal Mode (0:DFS, 1:BFS) : ");
	scanf("%d", &Mode);

	if (Mode == 0) {
		DFS(g->Vertices);
	}
	else {
		Queue* q = NULL;
		createQueue(&q);

		BFS(v1, q);

		destroyQueue(q);
	}

	DestroyGraph(g);
	return 0;
}