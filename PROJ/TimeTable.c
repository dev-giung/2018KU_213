#include <stdio.h>
#include <malloc.h>

typedef double Time;

typedef struct Space {
	
	int ID; // ��Ұ�����ȣ
	 
} Space;

typedef struct TimeTableNode {

	// Data Field
    Time sTime; // �������۽ð�
    Time eTime; // ��������ð�
    Space  Pos; // �����������
	
	// Link Field
    struct TimeTableNode *llink; // ��������
    struct TimeTableNode *rlink; // ��������

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
		printf("Time  : %2.2f ~ %2.2f\n", p->sTime, p->eTime);
		printf("Pos ID: %d\n", p->Pos);
		//printf("%x\n", p->rlink);
		printf("-----\n");
	}
}

void insert_TTN(TimeTableNode *phead, TimeTableNode *new_node) {
	
	TimeTableNode *pre_node = phead;
	
	while(pre_node->rlink != phead) {
		pre_node = pre_node->rlink;
	}
	
	if(pre_node->eTime > new_node->sTime) {
		//printf("������ ��ĥ �� ����.\n");
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
	
	Space tempSpace1 = {1};
	Space tempSpace2 = {2};
	Space tempSpace3 = {3};
	insert_TTN(&mylist, create_TTN(12.0, 13.8, tempSpace1));
	insert_TTN(&mylist, create_TTN(14.0, 15.0, tempSpace2));
	insert_TTN(&mylist, create_TTN(15.1, 17.9, tempSpace3));
	
	display_TTL(&mylist);
	
	return 0;
}