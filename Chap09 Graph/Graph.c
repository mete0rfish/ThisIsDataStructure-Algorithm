#include "Graph.h"

Graph* CreateGraph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->Vertices = NULL;
	graph->VertexCount = 0;
	return graph;
}
void DestroyGraph(Graph* G) {
	while (G->Vertices != NULL) {
		Vertex* Vertices = G->Vertices->next;
		DestroyVertex(G->Vertices);
		G->Vertices = Vertices;
	}

	free(G);
}

Vertex* CreateVertex(VElementType Data) {
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	vertex->Data = Data;
	vertex->AdjacencyList = NULL;
	vertex->next = NULL;
	vertex->Visited = NotVisited;
	vertex->Index = -1;
	return vertex;
}
void DestroyVertex(Vertex* v){
	while (v->AdjacencyList != NULL) {
		Edge* e = v->AdjacencyList->Next;
		DestroyEdge(v->AdjacencyList);
		v->AdjacencyList = e;
	}

	free(v);
}


Vertex* CreateEdge(Vertex* From, Vertex* Target, int Weight) {
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->From = From;
	e->Target = Target;
	e->Next = NULL;
	e->Weight = Weight;

	return e;
}
void DestroyEdge(Edge* E) {
	free(E);
}

void AddVertex(Graph* G, Vertex* V) {
	Vertex* vList = G->Vertices;

	if (vList == NULL)
		G->Vertices = V;
	else {
		while (vList->next != NULL)
			vList = vList->next;

		vList->next = V;
	}

	V->Index = G->VertexCount++;
}
void AddEdge(Vertex* V, Edge* E) {
	if (V->AdjacencyList == NULL) {
		V->AdjacencyList = E;
	}
	else {
		Edge* AdjacencyList = V->AdjacencyList;
		printf("v: %c\n", V->Data);
		while (AdjacencyList->Next != NULL) {
			//printf("%c\n", AdjacencyList->From->Data);
			AdjacencyList = AdjacencyList->Next;
		}
			
		AdjacencyList->Next = E;
	}
}
void PrintGraph(Graph* G) {
	Vertex* v = NULL;
	Edge* e = NULL;

	if ((v = G->Vertices) == NULL)
		return;

	while (v != NULL) {
		printf("%c : ", v->Data);

		if ((e = v->AdjacencyList) == NULL) {
			v = v->next;
			printf("\n");
			continue;
		}
		while (e != NULL) {
			printf("%c[%d] ", e->Target->Data, e->Weight);
			e = e->Next;
		}

		printf("\n");

		v = v->next;
	}
	printf("\n"); 
}