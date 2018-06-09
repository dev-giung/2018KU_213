#define DAYS_FOR_WEEK 5

/*
*
*	Structures
*
*/
typedef struct TimeTableNode {
	
	// Data Field
	double sTime;
	double eTime;
	int posIndex;
	char name[20];
	
	// Link Field
	struct TimeTableNode *llink;
	struct TimeTableNode *rlink;
	
} TimeTableNode;

/*
*
*	Global Variables
*
*/
TimeTableNode myTimeTable[DAYS_FOR_WEEK];

/*
*
*	Time Table Functions
*
*/
void initialize_TTList(TimeTableNode *phead);
TimeTableNode *create_TTNode(double sTime, double eTime, int posIndex, char name[]);
void insert_TTNode(TimeTableNode *phead, TimeTableNode *new_node);
void remove_TTNode(TimeTableNode *phead, TimeTableNode *removed);
void display_TTList(TimeTableNode *phead);
void loadTXT_TimeTable(TimeTableNode myTT[DAYS_FOR_WEEK]);
