#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "timeTableHandle.h"

/*
*
*	File Name
*
*/
char * TimeTableFileName = "TimeTable_info.txt";

/*
*
*	Time Table Functions
*
*/
void initialize_TTList(TimeTableNode *phead) {
	
	phead->llink = phead;
	phead->rlink = phead;
	
}

TimeTableNode *create_TTNode(double sTime, double eTime, int posIndex) {

	TimeTableNode *new_node = NULL;

	new_node = (TimeTableNode *)malloc(sizeof(TimeTableNode));
	
	new_node->sTime = sTime;
	new_node->eTime = eTime;
	new_node->posIndex = posIndex;

	new_node->llink = NULL;
	new_node->rlink = NULL;
	
	return new_node;

}

void insert_TTNode(TimeTableNode *phead, TimeTableNode *new_node) {

	TimeTableNode *pre_node = phead;
	
	while ( pre_node->rlink != phead ) {
		pre_node = pre_node->rlink;
	}

	if ( pre_node->eTime > new_node->sTime ) {
		//printf("ÀÏÁ¤Àº °ãÄ¥ ¼ö ¾øÀ½.\n");
		return;
	} else {
		new_node->llink = pre_node;
		new_node->rlink = pre_node->rlink;
		pre_node->rlink->llink = new_node;
		pre_node->rlink = new_node;
	}

}

void remove_TTNode(TimeTableNode *phead, TimeTableNode *removed) {

	if ( removed == phead ) {
		return;
	}

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);

}

void display_TTList(TimeTableNode *phead) {

	TimeTableNode *p;

	for ( p = phead->rlink; p != phead; p = p->rlink ) {

		printf("--------------------\n");
		//printf("%x\n", p->llink);
		printf("Time : %2.2f ~ %2.2f\n", p->sTime, p->eTime);
		printf("Pos ID: %d\n", p->posIndex);
		//printf("%x\n", p->rlink);
		printf("--------------------\n");
	}

}

/*
*
*	File Handler Functions
*
*/
void loadTXT_TimeTable(TimeTableNode myTT[DAYS_FOR_WEEK]) {

	FILE * myTimeTableFile = NULL;

	int i, j, num;
	int temp[5] = { 0 };
	char tempString[100];

	if ( (myTimeTableFile = fopen(TimeTableFileName, "r")) == NULL ) {
		printf("Error : Cannot find the file <%s>", TimeTableFileName);
		return;
	}

	for ( j = 0; j < DAYS_FOR_WEEK; j++ ) {
		
		fscanf(myTimeTableFile, "#%d %s\n", &num, &tempString);

		for ( i = 0; i < num; i++ ) {
			fscanf(myTimeTableFile, "%d:%d\t%d:%d\t%d\t%s\n", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &tempString);
			insert_TTNode(&myTT[j], create_TTNode(temp[0] + temp[1] / 60.0, temp[2] + temp[3] / 60.0, temp[4]));
			
			// TODO: load <name> variable from text file...
		}
		
		fscanf(myTimeTableFile, "\n");
	}
	
	fclose(myTimeTableFile);
	
}

