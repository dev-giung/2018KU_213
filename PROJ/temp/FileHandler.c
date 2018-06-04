/*
	FileHandler.c contains functions for file saving & loading.
	- Space_info.txt
	- Input_TimeTable.txt
*/

#include <stdio.h>
#include <malloc.h>

/*
	Constants
*/
#define SPACE_NUMBER 18
#define DAYS_FOR_WEEK 5

/*
	Structures
*/
typedef struct Space {
	
	// Building ID & Name
	int id;
	char name[20];

	// Facility Info
	int is_cafe;
	int is_lounge;
	int is_convenience;
	int is_vendingMac;
	int is_copyMac;
	 
} Space;

typedef struct TimeTableNode {

	// Data Field
    double sTime;
    double eTime;
    char name[20];
    int indexPos;
	
	// Link Field
    struct TimeTableNode *llink;
    struct TimeTableNode *rlink;

} TimeTableNode;

typedef struct TimeTableType {
	
	// List Array
	TimeTableNode day_list[DAYS_FOR_WEEK];
	
} TimeTableType;

/*
	Global Variables
*/
char * SpaceFileName = "Space_info.txt";
Space SpaceInfo[SPACE_NUMBER];

char * TimeTableFileName = "Input_TimeTable.txt";
TimeTableType myTimeTable;

/*
	File Handler Functions
*/
void loadTXT_SpaceInfo(Space * mySpaceArray, int N) {
	
	FILE * mySpaceFile = NULL;
	int index = 0;
	
	if( (mySpaceFile = fopen(SpaceFileName, "r")) == NULL ) {
		
		printf("Error : Cannot find the file <%s>", SpaceFileName);
		return;
	}
	
	for( index = 0; index < N; index++ ) {
		
		fscanf( mySpaceFile, "%d\t%s\t%d\t%d\t%d\t%d\t%d", 
			&mySpaceArray[index].id, &mySpaceArray[index].name, &mySpaceArray[index].is_cafe, 
			&mySpaceArray[index].is_lounge, &mySpaceArray[index].is_convenience, 
			&mySpaceArray[index].is_vendingMac, &mySpaceArray[index].is_copyMac
		);
	}
}

void loadTXT_TimeTable(TimeTableType myTTList) {
	
	FILE * myTimeTableFile = NULL;
	
	int index, N;
	int sTimeH, sTimeM, eTimeH, eTimeM;
	
	if( (myTimeTableFile = fopen(TimeTableFileName, "r")) == NULL ) {
		
		printf("Error : Cannot find the file <%s>", TimeTableFileName);
		return;
	}
	
	while( 1 ) {
		
		if( fscanf( myTimeTableFile, "#%d", &N) == EOF ) {
			break;
		}
		
		for( index = 0; index < N; index++ ) {
			
			fscanf( myTimeTableFile, "%d:%d\t%d:%d\t%s\t%d",
				&sTimeH, &sTimeM, &eTimeH, &eTimeM,
				&myTimeTable.day_list[index].name,
				&myTimeTable.day_list[index].indexPos
			);
			
			myTimeTable.day_list[index].sTime = sTimeH + sTimeM / 60;
			myTimeTable.day_list[index].eTime = eTimeH + eTimeM / 60;
		}
	}
}

/*
	Time Table Functions
*/
void initialize_TimeTableType(TimeTableType myTT) {
	
	int i;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		
		initialize_TTL(&myTT.day_list[i]);
	}
}

void initialize_TTL(TimeTableNode *phead) {
	
	phead->llink = phead;
	phead->rlink = phead;
}

void display_TimeTableType(TimeTableType myTT) {
	
	int i;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		
		printf("[ %d ]\n", i);
		display_TTL(myTT.day_list[i]);
	}
}

void display_TTL(TimeTableNode *phead) {
	
	TimeTableNode *p;
	for(p = phead->rlink; p != phead; p = p->rlink) {
		printf("--------------------\n");
		//printf("%x\n", p->llink);
		printf("Time : %2.2f ~ %2.2f\n", p->sTime, p->eTime);
		printf("Space ID : %d\n", p->indexPos);
		//printf("%x\n", p->rlink);
		printf("--------------------\n");
	}
}

/*
	Temporary Functions
*/
void print_SpaceInfo(Space * mySpaceArray, int N) {
	
	int index = 0;
	
	for( index = 0; index < N; index++ ) {
		
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", 
			mySpaceArray[index].id, &mySpaceArray[index].name, mySpaceArray[index].is_cafe, 
			mySpaceArray[index].is_lounge, mySpaceArray[index].is_convenience, 
			mySpaceArray[index].is_vendingMac, mySpaceArray[index].is_copyMac
		);
	}
}

int main() {
	
	loadTXT_SpaceInfo(SpaceInfo, SPACE_NUMBER);
	print_SpaceInfo(SpaceInfo, SPACE_NUMBER);
	
	loadTXT_TimeTable(myTimeTable);
	print_TimeTable(myTimeTable);
	
	return 0;
}
