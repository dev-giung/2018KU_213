#define MAX_VERTICES 34
#define INF 10000

/*
*
*	Structures
*
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

typedef struct Path {
	
	// Data Field
	int point;
	
	// Link Field
	struct Path * link;
	
} Path;

/*
*
*	Global Variables
*
*/
GraphType myCampusGraph;

/*
*
*	Graph & Path Functions
*
*/
void insert_Path(Path * p, int point);
int getDistance_Path(GraphType * g, Path p);
void display_Path(Path p);
void initialize_Graph(GraphType * g);
void insertEdge_Graph(GraphType * g, int u, int v, int weight);
void display_Graph(GraphType * g);
int get_Weight(GraphType * g, int sVertex, int eVertex);
Path get_Path(GraphType * g, int sVertex, int eVertex);
int choose(int distance[], int found[]);
void loadTXT_Graph(GraphType * myCG);
