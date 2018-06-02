#include <stdio.h>
#include <malloc.h>

#define DAYS_FOR_WEEK 5
#define TRUE 1
#define FALSE 0
 
typedef double Time;

typedef struct Space {
	
	// Building ID & Name
	int id;
	char * name;

	// Facility Info
	int is_cafe;
	int is_lounge;
	int is_convenience;
	int is_vendingMac;
	int is_copyMac;
	int is_anyOther;
	 
} Space;

typedef struct TimeTableNode {

	// Data Field
    Time sTime;
    Time eTime;
    Space  pos;
	
	// Link Field
    struct TimeTableNode *llink;
    struct TimeTableNode *rlink;

} TimeTableNode;

typedef struct TimeTableType {
	
	// List Array
	TimeTableNode day_list[DAYS_FOR_WEEK];
	
} TimeTableType;

void display_Space(Space mySpace) {
	
	printf("%d, %s, %d\n", mySpace.id, mySpace.name, mySpace.is_cafe);
}

/*
	Functions for the Time Table
	- functions for the basic linked list (initialize, insert/remove node, etc.)
	- functions for the time table (save/load data, print table, etc.)
*/

void initialize_TTL(TimeTableNode *phead) {
	
	phead->llink = phead;
	phead->rlink = phead;
}

void display_TTL(TimeTableNode *phead) {
	
	TimeTableNode *p;
	for(p = phead->rlink; p != phead; p = p->rlink) {
		printf("--------------------\n");
		//printf("%x\n", p->llink);
		printf("Time : %2.2f ~ %2.2f\n", p->sTime, p->eTime);
		display_Space(p->pos);
		//printf("Pos ID: %d\n", p->Pos);
		//printf("%x\n", p->rlink);
		printf("--------------------\n");
	}
}

void insert_TTN(TimeTableNode *phead, TimeTableNode *new_node) {
	
	TimeTableNode *pre_node = phead;
	
	while(pre_node->rlink != phead) {
		pre_node = pre_node->rlink;
	}
	
	if(pre_node->eTime > new_node->sTime) {
		//printf("일정은 겹칠 수 없음.\n");
		return;
	} else {
		new_node->llink = pre_node;
		new_node->rlink = pre_node->rlink;
		pre_node->rlink->llink = new_node;
		pre_node->rlink = new_node;	
	}
}

void remove_TTN(TimeTableNode *head, TimeTableNode *removed) {
	
	if(removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

TimeTableNode *create_TTN(Time sTime, Time eTime, Space pos) {
	
	TimeTableNode *new_node = NULL;
	new_node = (TimeTableNode *)malloc(sizeof(TimeTableNode));
	
	new_node->sTime = sTime;
	new_node->eTime = eTime;
	new_node->pos = pos;
	
	new_node->llink = NULL;
	new_node->rlink = NULL;
}

int main() {
	
	TimeTableType myTimeTable;
	int i = 0;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		initialize_TTL(&myTimeTable.day_list[i]);
	}
	
	Space tempSpace1 = {1, "건물이름_1", TRUE, TRUE, FALSE, FALSE, FALSE, FALSE};
	Space tempSpace2 = {2, "건물이름_2", TRUE, TRUE, FALSE, FALSE, FALSE, FALSE};
	Space tempSpace3 = {3, "건물이름_3", TRUE, TRUE, FALSE, FALSE, FALSE, FALSE};
	
	insert_TTN(&myTimeTable.day_list[0], create_TTN(12.0, 13.8, tempSpace1));
	insert_TTN(&myTimeTable.day_list[0], create_TTN(14.0, 15.0, tempSpace2));
	insert_TTN(&myTimeTable.day_list[0], create_TTN(15.1, 17.9, tempSpace3));
	
	display_TTL(&myTimeTable.day_list[0]);
	
	return 0;
}
