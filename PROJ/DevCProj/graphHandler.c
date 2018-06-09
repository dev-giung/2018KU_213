#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "graphHandle.h"

/*
*
*	File Name
*
*/
char * GraphFileName = "Graph_info.txt";

/*
*
*	Path Functions
*
*/
void insert_Path(Path * p, int point) {

	Path * new_node = NULL;
	Path * last_node = p;

	while ( last_node->link != NULL ) {
		last_node = last_node->link;
	}

	new_node = (Path *)malloc(sizeof(Path));
	new_node->point = point;
	new_node->link = last_node->link;
	last_node->link = new_node;
	
}

int getDistance_Path(GraphType * g, Path p) {

	int distance = 0;
	Path * cur = &p;

	while ( cur != NULL && cur->link != NULL ) {
		distance += get_Weight(g, cur->point, cur->link->point);
		cur = cur->link;
	}
	
	return distance;
	
}

void display_Path(Path p) {
	
	Path * cur_node = &p;
	
	while ( cur_node != NULL ) {
		printf("%d -> ", cur_node->point);
		cur_node = cur_node->link;
	}
	printf("END\n");
	
}

/*
*
*	Graph Functions
*
*/
void initialize_Graph(GraphType * g) {
	
	int v;
	g->n = 0;

	for ( v = 0; v < MAX_VERTICES; v++ ) {
		g->adj_list[v] = NULL;
	}
	
}

void insertEdge_Graph(GraphType * g, int u, int v, int weight) {
	
	GraphNode * new_node;

	if ( u >= MAX_VERTICES || v >= MAX_VERTICES ) {
		printf("Error : vertex index out of range.");
		return;
	}
	
	// u to v
	new_node = (GraphNode *)malloc(sizeof(GraphNode));
	new_node->index = v;
	new_node->weight = weight;
	new_node->link = g->adj_list[u];
	g->adj_list[u] = new_node;

	// v to u
	new_node = (GraphNode *)malloc(sizeof(GraphNode));
	new_node->index = u;
	new_node->weight = weight;
	new_node->link = g->adj_list[v];
	g->adj_list[v] = new_node;
	
}

void display_Graph(GraphType * g) {

	int v;
	GraphNode *p = NULL;

	for ( v = 0; v < MAX_VERTICES; v++ ) {

		printf("Vertex[%d] connected to...\n", v);
		p = g->adj_list[v];

		while ( p != NULL ) {
			printf("  v[%d] with weight %d\n", p->index, p->weight);
			p = p->link;
		}
	}

}

int get_Weight(GraphType * g, int sVertex, int eVertex) {

	GraphNode * temp = g->adj_list[sVertex];

	if ( sVertex >= MAX_VERTICES || eVertex >= MAX_VERTICES ) {
		printf("Error : vertex index out of range.");
		return INF;

	}

	if ( sVertex == eVertex ) {
		return 0;
	}

	while ( temp != NULL ) {
		if ( temp->index == eVertex ) {
			return temp->weight;
		}
		temp = temp->link;
	}
	
	return INF;
	
}

Path get_Path(GraphType * g, int sVertex, int eVertex) {

	int distance[MAX_VERTICES];
	int found[MAX_VERTICES];
	int path[MAX_VERTICES];
	GraphNode * temp = NULL;
	int i, u;
	Path myPath = { eVertex, NULL };
	Path error = { -1, NULL };

	if ( sVertex >= MAX_VERTICES || eVertex >= MAX_VERTICES ) {
		printf("Error : vertex index out of range.");
		return error;
	}

	for ( i = 0; i < MAX_VERTICES; i++ ) {
		distance[i] = get_Weight(g, sVertex, i);
		found[i] = 0;
		path[i] = -1;
	}

	found[sVertex] = 1;

	while (1) {
		u = choose(distance, found);
		if (u == -1) {
			break;
		}

		found[u] = 1;
		temp = g->adj_list[u];

		while ( temp != NULL ) {

			if ( found[temp->index] == 0 ) {

				if ( distance[u] + temp->weight < distance[temp->index] ) {

					distance[temp->index] = distance[u] + temp->weight;
					path[temp->index] = u;
				}
			}

			temp = temp->link;
		}
	}

	i = path[eVertex];
	while ( i != -1 ) {
		insert_Path(&myPath, i);
		i = path[i];
	}
	insert_Path(&myPath, sVertex);
	
	return myPath;
}

int choose(int distance[], int found[]) {

	int i, min, minpos;

	min = INF;
	minpos = -1;

	for ( i = 0; i < MAX_VERTICES; i++ ) {

		if ( distance[i] < min && found[i] == 0 ) {
			min = distance[i];
			minpos = i;
		}
	}

	return minpos;

}

/*
*
*	File Handler Functions
*
*/
void loadTXT_Graph(GraphType * myCG) {
	
	FILE * myCampusGraphFile = NULL;
	int i, j;
	int numVertex, numEdge;
	char tempString[100];
	int temp[3] = { 0 };

	if ( (myCampusGraphFile = fopen(GraphFileName, "r")) == NULL ) {
		printf("Error : Cannot find the file <%s>", GraphFileName);
		return;
	}

	fscanf(myCampusGraphFile, "#%d %s\n", &numVertex, &tempString);
	fscanf(myCampusGraphFile, "#%d %s\n", &numEdge,&tempString);

	for ( i = 0; i < numEdge; i++ ) {
		fscanf(myCampusGraphFile, "%d\t%d\t%d\n", &temp[0], &temp[1], &temp[2]);
		insertEdge_Graph(myCG, temp[0], temp[1], temp[2]);
	}
	
	fclose(myCampusGraphFile);
	
}
