/*
	GraphFileHandler.c contains functions for file loading.
	- Graph_info.txt
*/

#include <stdio.h>
#include <malloc.h>

/*
	Constants
*/
#define MAX_VERTICES 50

/*
	Structures
*/
typedef struct GraphNode {
	
	// Data Field
    int index;
    int weight;

	// Link Field
	struct GraphNode * link;
	
} GraphNode;

typedef struct GraphType {
	
	// Number of Vertices
	int n;
	
	// Pointer Array
	GraphNode * adj_list[MAX_VERTICES];

} GraphType;

/*
	Global Variables
*/
char * GraphFileName = "Graph_info.txt";
GraphType myCampusGraph;

/*
	Graph Functions
*/
void initialize_Graph(GraphType * g) {
	
	int v;
	
	g->n = 0;
	
	for( v = 0; v < MAX_VERTICES; v++ ) {
		g->adj_list[v] = NULL;
	}
}

void insertEdge_Graph(GraphType * g, int u, int v, int weight) {
	
	GraphNode * new_node;
	
	if( u >= MAX_VERTICES || v >= MAX_VERTICES ) {
		
		printf("Error : vertex index out of range.");
		return;
	}
	
	new_node = (GraphNode *)malloc(sizeof(GraphNode));
	new_node->index = v;
	new_node->weight = weight;
	new_node->link = g->adj_list[u];
	g->adj_list[u] = new_node;
}

void display_Graph(GraphType * g) {
	
	int v;
	GraphNode *p = NULL;
	
	for( v = 0; v < MAX_VERTICES; v++ ) {
		
		printf("Vertex[%d] connected to...\n", v);
		
		p = g->adj_list[v];
		
		while( p != NULL ) {
			
			printf("  v[%d] with weight %d\n", p->index, p->weight);
			p = p->link;
		}
	}
}

/*
	File Handler Functions
*/
void loadTXT_Graph(GraphType * myCG) {
	
	FILE * myCampusGraphFile = NULL;
	
	int i, j;
	
	int numVertex, numEdge;
	
	int temp[3] = { 0 };
	
	if( (myCampusGraphFile = fopen(GraphFileName, "r")) == NULL ) {
		
		printf("Error : Cannot find the file <%s>", GraphFileName);
		return;
	}
	
	fscanf( myCampusGraphFile, "#%d %s\n", &numVertex);
	//printf("%d\n", numVertex);
	fscanf( myCampusGraphFile, "#%d %s\n", &numEdge);
	//printf("%d\n", numEdge);
	
	for( i = 0; i < numEdge; i++ ) {
		
		fscanf( myCampusGraphFile, "%d\t%d\t%d\n", &temp[0], &temp[1], &temp[2]);
		//printf("%d, %d, %d\n", temp[0], temp[1], temp[2]);
		insertEdge_Graph( myCG, temp[0], temp[1], temp[2] );
	}
	
	fclose( myCampusGraphFile );
}

/*
	Main Function
*/
int main() {
	
	initialize_Graph(&myCampusGraph);
	
	loadTXT_Graph(&myCampusGraph);
	
	display_Graph(&myCampusGraph);
	
	return 0;
}
