#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 18


int weight[MAX_VERTICES][MAX_VERTICES];
int distance[MAX_VERTICES];

typedef struct Space {
	
	// Building ID & Name
	int id;
	char * name;
	
	// Facility Info
	int is_cafe;
	int is_lounge;
	int is_convenience;
	int is_vendingMac;
	int is_copyMac;
	
} Space;

typedef struct GraphNode {
	
	// Data Field
	// this index value will load space data from SpaceInfoArray[index].
	int index;

	// Link Field
	struct GraphNode * link;
	
} GraphNode;

typedef struct GraphType {
	
	// Number of Vertices
	int n;
	
	// Pointer Array
	GraphNode * adj_list[MAX_VERTICES];

} GraphType;


void graph_init(GraphType * g) {
	
	int v;
	
	g->n = 0;
	
	for(v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_edge(GraphType * g, int u, int v, Space p) {
	
	GraphNode * node;
	
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "존재하지 않는 건물입니다.");
		return;
	}
	
	node = (graphNode *)malloc(sizeof(graphNode));
	node->index = v;
	node->Pos = p;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}


int main() {
	//graphType * g; graph_init(g);
	return 0;
}
