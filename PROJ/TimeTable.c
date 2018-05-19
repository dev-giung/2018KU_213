#include <stdio.h>
#include <malloc.h>

typedef double Time;

typedef struct Space {
	
	int ID; // 장소고유번호
	 
} Space;

typedef struct TimeTableNode {

	// Data Field
    Time sTime; // 일정시작시간
    Time eTime; // 일정종료시간
    Space  Pos; // 일정진행장소
	
	// Link Field
    struct TimeTableNode *llink; // 이전일정
    struct TimeTableNode *rlink; // 다음일정

} TimeTableNode;

/*
	Functions for 
*/

void initialize_TTL(TimeTableNode *phead) {
	
	phead->llink = phead;
	phead->rlink = phead;
	
}

void display_TTL(TimeTableNode *phead) {
	
	TimeTableNode *p;
	for(p = phead->rlink; p != phead; p = p->rlink) {
		printf("-----\n");
		//printf("%x\n", p->llink);
		printf("%f ~ %f\n", p->sTime, p->eTime);
		printf("%d\n", p->Pos);
		//printf("%x\n", p->rlink);
		printf("-----\n");
	}
}

void insert_TTN(TimeTableNode *pre_node, TimeTableNode *new_node) {
	
	new_node->llink = pre_node;
	new_node->rlink = pre_node->rlink;
	pre_node->rlink->llink = new_node;
	pre_node->rlink = new_node;
}

void remove_TTN(TimeTableNode *head, TimeTableNode *removed) {
	
	if(removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

TimeTableNode *create_TTN(Time sTime, Time eTime, Space Pos) {
	
	TimeTableNode *new_node = NULL;
	new_node = (TimeTableNode *)malloc(sizeof(TimeTableNode));
	
	new_node->sTime = sTime;
	new_node->eTime = eTime;
	new_node->Pos = Pos;
	
	new_node->llink = NULL;
	new_node->rlink = NULL;
}

int main() {
	
	TimeTableNode mylist;
	initialize_TTL(&mylist);
	
	Space tempSpace = {1};
	insert_TTN(&mylist, create_TTN(12.0, 13.0, tempSpace));
	insert_TTN(&mylist, create_TTN(14.0, 15.0, tempSpace));
	insert_TTN(&mylist, create_TTN(16.0, 17.0, tempSpace));
	
	display_TTL(&mylist);
	
	return 0;
}
