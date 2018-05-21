#include <stdio.h>

#define MAX_VERTICES 9
#define INF 10000

void dijkstra(int graph[][MAX_VERTICES], int start, int end) {
	
	int sVertex = start;
	int eVertex = end;
	
	int distance[MAX_VERTICES];
	int found[MAX_VERTICES];
	
	int i, u, w;
	
	for( i = 0; i < MAX_VERTICES; i++ ) {
		distance[i] = graph[sVertex][i];
		found[i] = 0;
	}
	distance[sVertex] = 0;
	found[sVertex] = 1;
	
	for( i = 0; i < MAX_VERTICES - 2; i++ ) {
		u = choose(distance, found);
		found[u] = 1;
		for( w = 0; w < MAX_VERTICES; w++ ) {
			if( found[w] == 0 ) {
				if( distance[u] + graph[u][w] < distance[w] ) {
					distance[w] = distance[u] + graph[u][w];
				}
			}
		}
	}
	
	printf("%d\n", distance[eVertex]);
}

int choose(int distance[], int found[]) {
	int i, min, minpos;
	min = INF;
	minpos = -1;
	
	for( i = 0; i < MAX_VERTICES; i++ ) {
		if( distance[i] < min && found[i] == 0) {
			min = distance[i];
			minpos = i;
		}
	}
	
	return minpos;
}

void floyd(int graph[][MAX_VERTICES]) {
	
	// Define a distance matrix
	int dMatrix[MAX_VERTICES][MAX_VERTICES];
	
	// Define index variables
	int i, j, k;
	
	// Initialize the distance matrix
	for( i = 0; i < MAX_VERTICES; i++ ) {
		for( j = 0; j < MAX_VERTICES; j++ ) {
			dMatrix[i][j] = graph[i][j];
		}
	}
	
	// Generate distance matrix (by Floyd algorithm)
	for( k = 0; k < MAX_VERTICES; k++ ) {
		for( i = 0; i < MAX_VERTICES; i++ ) {
			for( j = 0; j < MAX_VERTICES; j++ ) {
				if( dMatrix[i][j] > dMatrix[i][k] + dMatrix[k][j] ) {
					dMatrix[i][j] = dMatrix[i][k] + dMatrix[k][j];
				}
			}
		}
	}
	
	// Print the distance matrix
	for( i = 0; i < MAX_VERTICES; i++ ) {
		for( j = 0; j < MAX_VERTICES; j++ ) {
			printf("%3d ", dMatrix[i][j]);
		}
		printf("\n");
	}
}

int main() {
	
	// adjacency matrix of the graph
	int myGraph[MAX_VERTICES][MAX_VERTICES] = {
		
		//S    A    B    C    D    E    F    G    H
		{  0,   7, INF, INF, INF, INF,   4, INF, INF},
		{  7,   0,   5, INF, INF,   2, INF, INF, INF},
		{INF,   5,   0,   4, INF, INF, INF, INF, INF},
		{INF, INF,   4,   0,   2, INF, INF, INF,   6},
		{INF, INF, INF,   2,   0,   3, INF,   8, INF},
		{INF,   2, INF, INF,   3,   0,  11, INF, INF},
		{  4, INF, INF, INF, INF,  11,   0,   9, INF},
		{INF, INF, INF, INF,   8, INF,   9,   0,   1},
		{INF, INF, INF,   6, INF, INF, INF,   1,   0}
	};
	
	printf("Floyd:\n");
	floyd(myGraph);
	
	printf("Dijkstra:\n");
	
	int i;
	for( i = 0; i < MAX_VERTICES; i++ ) {
		dijkstra(myGraph, 0, i);
	}
	
	return 0;
}
