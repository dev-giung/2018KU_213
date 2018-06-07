#include <stdio.h>

#define MAX_VERTICES 9
#define INF 10000

/*
	function: �׷����� �����������κ��� �������������� �ִܰŸ��� ��� (by Dijkstra algorithm) 
	input	: graph(int[][MAX_VERTICES]) : �׷��� ������� (call by reference)
			  start(int) : ���������� �ε��� ��
			  end(int) : ���������� �ε��� �� 
	output	: (NULL)
*/
void dijkstra(int graph[][MAX_VERTICES], int start, int end) {
	
	// define start & end vertices' index
	int sVertex = start;
	int eVertex = end;
	
	// define distance & found arrays
	int distance[MAX_VERTICES];
	int found[MAX_VERTICES];
	
	// define index variables
	int i, u, w;
	
	// initialize distance & found arrays
	for( i = 0; i < MAX_VERTICES; i++ ) {
		distance[i] = graph[sVertex][i];
		found[i] = 0;
	}
	
	// initialize values of start vertex
	distance[sVertex] = 0;
	found[sVertex] = 1;
	
	// generate distance & found arrays (by Dijkstra algorithm)
	for( i = 0; i < MAX_VERTICES - 2; i++ ) {
		
		// get the vertex in 'unvisited set' which have the smallest distance
		u = choose(distance, found);
		
		printf("[%d] ", u);
		
		// and the vetex moves to the 'visited set'
		found[u] = 1;
		
		// generate distances of the vertices,
		for( w = 0; w < MAX_VERTICES; w++ ) {
			
			// the vertices in 'unvisited set'
			if( found[w] == 0 ) {
				
				// if the path through u is shorter,
				if( distance[u] + graph[u][w] < distance[w] ) {
					
					// update the distance info
					distance[w] = distance[u] + graph[u][w];
				}
			}
		}
	}
	
	printf("%d\n", distance[eVertex]);
}

/*
	function: ���� found���� ����, distance���� ���� ���� ������ �ε����� ��ȯ 
	input	: distance(int[]) : �����������κ����� �ִܰ�θ� ��� �迭 
			  found(int[]) : �湮�� ������ ǥ���ϴ� �迭
	output	: (int)
	Note    : dijkstra �Լ��� ���� �����Լ�. 
*/
int choose(int distance[], int found[]) {
	
	// define variables
	int i, min, minpos;
	
	// initialize min & minpos 
	min = INF;
	minpos = -1;
	
	// get index of vertex
	// which have the smallest distance & not found
	for( i = 0; i < MAX_VERTICES; i++ ) {
		if( distance[i] < min && found[i] == 0) {
			min = distance[i];
			minpos = i;
		}
	}
	
	// return the index
	return minpos;
}

/*
	function: �׷����� ��� ��� ���� �ִܰŸ������ ��� (by Floyd Algorithm) 
	input	: graph(int[][MAX_VERTICES]) : �׷��� ������� (call by reference)
	output	: (NULL)
*/
void floyd(int graph[][MAX_VERTICES]) {
	
	// define a distance matrix
	int dMatrix[MAX_VERTICES][MAX_VERTICES];
	
	// define index variables
	int i, j, k;
	
	// initialize the distance matrix
	for( i = 0; i < MAX_VERTICES; i++ ) {
		for( j = 0; j < MAX_VERTICES; j++ ) {
			dMatrix[i][j] = graph[i][j];
		}
	}
	
	// generate distance matrix (by Floyd algorithm)
	for( k = 0; k < MAX_VERTICES; k++ ) {
		for( i = 0; i < MAX_VERTICES; i++ ) {
			for( j = 0; j < MAX_VERTICES; j++ ) {
				if( dMatrix[i][j] > dMatrix[i][k] + dMatrix[k][j] ) {
					dMatrix[i][j] = dMatrix[i][k] + dMatrix[k][j];
				}
			}
		}
	}
	
	// print the distance matrix
	printf("    [S] [A] [B] [C] [D] [E] [F] [G] [H]\n");
	for( i = 0; i < MAX_VERTICES; i++ ) {
		printf("[%c] ", i == 0 ? 83 : i + 64);
		for( j = 0; j < MAX_VERTICES; j++ ) {
			printf("%3d ", dMatrix[i][j]);
		}
		printf("\n");
	}
}

/*
	function: �����Լ�
	input   : (NULL)
	output  : (NULL)
	Note    : �Է��Լ��� ����ó���� �ټ� ������ �� ������ ������� ����.
*/
int main() {

	// adjacency matrix of the graph
	int myGraph[MAX_VERTICES][MAX_VERTICES] = {
		
		// S    A    B    C    D    E    F    G    H
		{  0,   7, INF, INF, INF, INF,   4, INF, INF}, // S
		{  7,   0,   5, INF, INF,   2, INF, INF, INF}, // A
		{INF,   5,   0,   4, INF, INF, INF, INF, INF}, // B
		{INF, INF,   4,   0,   2, INF, INF, INF,   6}, // C
		{INF, INF, INF,   2,   0,   3, INF,   8, INF}, // D
		{INF,   2, INF, INF,   3,   0,  11, INF, INF}, // E
		{  4, INF, INF, INF, INF,  11,   0,   9, INF}, // F
		{INF, INF, INF, INF,   8, INF,   9,   0,   1}, // G
		{INF, INF, INF,   6, INF, INF, INF,   1,   0}  // H
	};
	
	// input alphabet of end vertex for (1) Dijkstra
	char input;
	
	printf("input end vertex: ");
	input = getchar();
	
	if( input == 83 ) {
		printf("-> distance of S to S: ");
		dijkstra(myGraph, 0, 0);
	} else if( input >= 65 && input <=72 ) {
		printf("-> distance of S to %c: ", input);
		dijkstra(myGraph, 0, input - 64);
	} else {
		printf("-> invalid input\n");
	}
	
	printf("\n");
	
	// print the shortest distance matrix by Floyd algorithm
	printf("distance matrix from Floyd algorithm:\n");
	floyd(myGraph);
	
	// terminate program
	return 0;
}
