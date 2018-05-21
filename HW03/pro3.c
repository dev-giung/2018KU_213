#include <stdio.h>

#define MAX_VERTICES 9
#define INF 10000

void dijkstra(int map[][MAX_VERTICES]) {
	
}

void floyd(int graph[][MAX_VERTICES]) {
	
	// Define a distance matrix
	int dMatrix[MAX_VERTICES][MAX_VERTICES];
	
	// Define an index variables
	int i, j, k;
	
	// Initialize the distance matrix
	for( i = 0; i < MAX_VERTICES; i++ ) {
		for( j = 0; j < MAX_VERTICES; j++ ) {
			dMatrix[i][j] = graph[i][j];
		}
	}
	
	// Get distance matrix (by Floyd algorithm)
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
}
