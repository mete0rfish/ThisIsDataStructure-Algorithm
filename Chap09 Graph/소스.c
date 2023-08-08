#include "Graph.h"

int main() {
	Graph* G = CreateGraph();

	Vertex* v1 = CreateVertex('1');
	Vertex* v2 = CreateVertex('2');
	Vertex* v3 = CreateVertex('3');
	Vertex* v4 = CreateVertex('4');
	Vertex* v5 = CreateVertex('5');

	AddVertex(G, v1);
	AddVertex(G, v2);
	AddVertex(G, v3);
	AddVertex(G, v4);
	AddVertex(G, v5);

	AddEdge(v1, CreateEdge(v1, v2, 0));
	AddEdge(v1, CreateEdge(v1, v3, 0));
	AddEdge(v1, CreateEdge(v1, v4, 0));
	AddEdge(v1, CreateEdge(v1, v5, 0));
	
	AddEdge(v2, CreateEdge(v2, v1, 0));
	AddEdge(v2, CreateEdge(v2, v3, 0));
	AddEdge(v2, CreateEdge(v2, v5, 0));

	AddEdge(v3, CreateEdge(v3, v1, 0));
	AddEdge(v3, CreateEdge(v3, v2, 0));

	AddEdge(v4, CreateEdge(v4, v1, 0));
	AddEdge(v4, CreateEdge(v4, v5, 0));

	AddEdge(v5, CreateEdge(v5, v1, 0));
	AddEdge(v5, CreateEdge(v5, v2, 0));
	AddEdge(v5, CreateEdge(v5, v4, 0));

	PrintGraph(G);

	DestroyGraph(G);

	return 0;
}
