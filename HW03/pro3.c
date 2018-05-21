#include <stdio.h>

#define MAX_VERTICES 9
#define INF 1000

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
}
