//#ifndef __TIMETABLEHANDLE_H__
//#define __TIMETABLEHANDLE_H__
#define DAYS_FOR_WEEK 5
//char * TimeTableFileName = "TimeTable_info.txt";
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


TimeTableNode myTimeTable[DAYS_FOR_WEEK];


void initialize_TTList(TimeTableNode *phead);
TimeTableNode *create_TTNode(double sTime, double eTime, int posIndex);
void insert_TTNode(TimeTableNode *phead, TimeTableNode *new_node);
void remove_TTNode(TimeTableNode *phead, TimeTableNode *removed);
void display_TTList(TimeTableNode *phead);
void loadTXT_TimeTable(TimeTableNode myTT[DAYS_FOR_WEEK]);


//#endif
