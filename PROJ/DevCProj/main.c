#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include "graphHandle.h"
#include "spaceHandle.h"
#include "timeTableHandle.h"

int checkVal_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph);
int getStopover_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph);

void display_namedPath(Path p);
void utility(Space SpaceInfo[SPACE_NUMBER], int ID);
void utility_list(Space sp);
void findStopover(Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph, int sVertex, int eVertex, int type, double restTime);

void UI_upLine();
void UI_downLine();
void UI_clear();
void UI_viewTimeTable();
void UI_FirstMain();
void UI_SecondMain();
void gotoxy(int x, int y);

char * day[DAYS_FOR_WEEK] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};


int main() {

	int i, selection;
	
	// load campus graph data
	initialize_Graph(&myCampusGraph);
	loadTXT_Graph(&myCampusGraph);
	
	// load space data
	loadTXT_SpaceInfo(SpaceInfo);
	
	// First Main 
	UI_FirstMain();
	scanf("%d", &selection);
	UI_clear();
	
	switch(selection) {
		case 1:
			printf("\n�̱���...");
			return 0;
			break;
		case 2:
			for ( i = 0; i < DAYS_FOR_WEEK; i++ ) {
				initialize_TTList(&myTimeTable[i]);
			}
			loadTXT_TimeTable(myTimeTable);
			break;
		case 9:
			return 0;
			break;
	}
	
	// Second Main
	do {
		UI_SecondMain();
		
		if( scanf("%d", &selection) == 0 ) {
			break;
		}
		
		UI_clear();
		
		switch(selection) {
			case 1:
				checkVal_Schedule(myTimeTable, SpaceInfo, &myCampusGraph);
				break;
			case 2:
				getStopover_Schedule(myTimeTable, SpaceInfo, &myCampusGraph);
				break;
			case 9:
				return 0;
				break;
		}
	} while(selection != 9);

	
	return 0;
	
}

/*
*
*	check validity of the time table...
*
*	- print path...
*	- print rest time(between two node) and move time...
*	- return the number of unvalid part...
*
*/
int checkVal_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph) {
	
	int i;
	int num = 0;
	double moveTime;
	double restTime;
	Path tempPath;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		
		printf("=== %s �ð�ǥ�� ��ȿ���� �˻��մϴ�.\n", day[i]);
		
		TimeTableNode * head_node = &myTimeTable[i];
		TimeTableNode * curr_node = head_node->rlink;
		
		while( curr_node != NULL && curr_node->rlink != head_node ) {
			
			tempPath = get_Path( myCampusGraph, curr_node->rlink->posIndex, curr_node->posIndex );
			
			printf("= (%02d : %02d) %s ", (int)curr_node->sTime, (int)(curr_node->sTime - (int)curr_node->sTime) * 60, curr_node->name);
			printf(">> (%02d : %02d) %s \n", (int)curr_node->rlink->sTime, (int)(curr_node->rlink->sTime - (int)curr_node->rlink->sTime) * 60, curr_node->rlink->name);
			
			printf("  - �̵����: ");
			display_namedPath(tempPath);
			
			restTime = ( curr_node->rlink->sTime - curr_node->eTime ) * 60.0;
			printf("  - �����ð�: %2.0f��\n", restTime);
			
			moveTime = getDistance_Path( myCampusGraph, tempPath );
			printf("  - �̵��ð�: %2.0f��\n", moveTime);
			
			if( restTime < moveTime ) {
				
				num++;
				printf("    - �����߰�! �����ð����� �̵��ð��� ��ϴ�.\n");
				printf("    - ��� �˻��Ϸ��� �ƹ� Ű�� ��������...\n");
				getch();
			} else {
				
				sleep(1);
			} 
			
			curr_node = curr_node->rlink;
		}
		
		printf("=== %s end\n\n", day[i]);
	}
	
	printf("�� %d���� ��ȿ���� ���� ��ȹ�� �����մϴ�.\n\n", num);
	printf("����ȭ������ ���ư����� �ƹ� Ű�� ��������...");
	
	getch();
	UI_clear();
	
	return num;
	 
}

/*
*
*	get stopover...
*
*	- print path...
*	- print rest time(between two node) and move time...
*	- give chance to insert stopover...
*
*/
int getStopover_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph) {
	
	int i;
	int selection;
	int num = 0;
	double moveTime;
	double restTime;
	Path tempPath;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		
		printf("=== %s �����ð��� �˻��մϴ�.\n", day[i]);
		
		TimeTableNode * head_node = &myTimeTable[i];
		TimeTableNode * curr_node = head_node->rlink;
		
		while( curr_node != NULL && curr_node->rlink != head_node ) {
			
			tempPath = get_Path( myCampusGraph, curr_node->rlink->posIndex, curr_node->posIndex );
			
			printf("= (%02d : %02d) %s ", (int)curr_node->sTime, (int)(curr_node->sTime - (int)curr_node->sTime) * 60, curr_node->name);
			printf(">> (%02d : %02d) %s \n", (int)curr_node->rlink->sTime, (int)(curr_node->rlink->sTime - (int)curr_node->rlink->sTime) * 60, curr_node->rlink->name);
			
			printf("  - �̵����: ");
			display_namedPath(tempPath);
			
			restTime = ( curr_node->rlink->sTime - curr_node->eTime ) * 60.0;
			printf("  - �����ð�: %2.0f��\n", restTime);
			
			moveTime = getDistance_Path( myCampusGraph, tempPath );
			printf("  - �̵��ð�: %2.0f��\n", moveTime);
			
			if( restTime < moveTime ) {
				
				num++;
				printf("    - �����߰�! �����ð����� �̵��ð��� ��ϴ�.\n");
				printf("    - �����ϰ� �����Ϸ��� �ƹ� Ű�� ��������...\n");
				getch();
				
			} else if( restTime - moveTime >= 20 ) {
				
				printf("    - %2.0f���� �����ð��� �����Ǿ����ϴ�.\n", restTime - moveTime);
				printf("    - �����ð��� ���� �������� �����ϼ���.\n");
				printf("        1. ī��\n");
				printf("        2. ������\n");
				printf("        3. �����\n");
				printf("        4. �����\n");
				printf("        5. ���Ǳ�\n");
				printf("        9. �ƹ��͵� ���� ����\n");
				printf("    - Select : ");
				scanf("%d", &selection);
				
				findStopover(SpaceInfo, myCampusGraph, curr_node->posIndex, curr_node->rlink->posIndex, selection, restTime);
				
			} else if( restTime - moveTime >= 5 ) {
				
				printf("    - %2.0f���� �����ð��� �����Ǿ����ϴ�.\n", restTime - moveTime);
				utility(SpaceInfo, curr_node->posIndex);
				utility(SpaceInfo, curr_node->rlink->posIndex);
				
			}  else {
				
				sleep(1);
			} 
			
			curr_node = curr_node->rlink;
		}
		
		printf("=== %s end\n\n", day[i]);
	}
	
	printf("�� %d���� ��ȿ���� ���� ��ȹ�� �����մϴ�.\n\n", num);
	printf("����ȭ������ ���ư����� �ƹ� Ű�� ��������...");
	
	getch();
	UI_clear();
	
	return num;
	 
}

void display_namedPath(Path p) {
	
	Path * cur_node = &p;
	
	while ( cur_node != NULL ) {
		printf("%s -> ", SpaceInfo[cur_node->point].name);
		cur_node = cur_node->link;
	}
	printf("END\n");
	
}

void utility(Space SpaceInfo[SPACE_NUMBER], int ID) {         // �ǹ� �� �̿� �ü� ���� �Լ�
   int choose;
   do {
      printf("    - %s �� �ü��� �̿��Ͻðڽ��ϱ�? (�� : 1 / �ƴϿ� : 0)\n", SpaceInfo[ID].name);
      printf("    - Select : ");
      scanf("%d", &choose);
         if (choose == 0) {
            return;
         }
         else if (choose == 1) {
            printf("    - %s �� �̿밡���� �ü���\n", SpaceInfo[ID].name);
            utility_list(SpaceInfo[ID]);
            break;
         }
         else {
            printf("    - �߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
         }
      
   } while (choose != 0 && choose != 1);
}

void utility_list(Space sp) {
	
   if (sp.is_cafe == 1) {
      printf("      - ī��\n");
   }

   if (sp.is_convenience == 1) {
      printf("      - ������\n");
   }
   
   if (sp.is_copyMac == 1) {
      printf("      - �����\n");
   }
   
   if (sp.is_lounge == 1) {
      printf("      - �����\n");
   }

   if (sp.is_vendingMac == 1) {
      printf("      - ���Ǳ�\n");
   }
   
}

void findStopover(Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph, int sVertex, int eVertex, int type, double restTime) {
	
	int i;
	Path tmpPath_1;
	Path tmpPath_2;
	int tmpTime;
	
	
	if( type == 9 ) {
		return;
	}
	
	for( i = 0; i < SPACE_NUMBER; i++ ) {
		
		switch(type) {
			case 1: // cafe
				if( SpaceInfo[i].is_cafe == 1 ) {
					tmpPath_1 = get_Path(myCampusGraph, i, sVertex);
					tmpPath_2 = get_Path(myCampusGraph, eVertex, i);
					tmpTime = restTime - getDistance_Path(myCampusGraph, tmpPath_1) - getDistance_Path(myCampusGraph, tmpPath_2);
					
					if( tmpTime >= 20 ) {
						printf("    - ������ ��θ� ���� ī�並 %2d�� ���� �̿��� �� �ֽ��ϴ�.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - �ִ� %2d�� ���� ī�� �̿�...\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_2);
					}
				}
				break;
			case 2: // convenience
				if( SpaceInfo[i].is_convenience == 1 ) {
					tmpPath_1 = get_Path(myCampusGraph, i, sVertex);
					tmpPath_2 = get_Path(myCampusGraph, eVertex, i);
					tmpTime = restTime - getDistance_Path(myCampusGraph, tmpPath_1) - getDistance_Path(myCampusGraph, tmpPath_2);
					
					if( tmpTime >= 3 && tmpTime <= 10 ) {
						printf("    - ������ ��θ� ���� �������� %2d�� ���� �̿��� �� �ֽ��ϴ�.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - �ִ� %2d�� ���� ������ �̿�...\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_2);
					}
				}
				break;
			case 3: // copyMac
				if( SpaceInfo[i].is_copyMac == 1 ) {
					tmpPath_1 = get_Path(myCampusGraph, i, sVertex);
					tmpPath_2 = get_Path(myCampusGraph, eVertex, i);
					tmpTime = restTime - getDistance_Path(myCampusGraph, tmpPath_1) - getDistance_Path(myCampusGraph, tmpPath_2);
					
					if( tmpTime >= 3 && tmpTime <= 10 ) {
						printf("    - ������ ��θ� ���� ����⸦ %2d�� ���� �̿��� �� �ֽ��ϴ�.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - �ִ� %2d�� ���� ����� �̿�...\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_2);
					}
				}
				break;
			case 4: // lounge
				if( SpaceInfo[i].is_lounge == 1 ) {
					tmpPath_1 = get_Path(myCampusGraph, i, sVertex);
					tmpPath_2 = get_Path(myCampusGraph, eVertex, i);
					tmpTime = restTime - getDistance_Path(myCampusGraph, tmpPath_1) - getDistance_Path(myCampusGraph, tmpPath_2);
					
					if( tmpTime >= 20 ) {
						printf("    - ������ ��θ� ���� ������� %2d�� ���� �̿��� �� �ֽ��ϴ�.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - �ִ� %2d�� ���� ����� �̿�...\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_2);
					}
				}
				break;
			case 5: // vendingMac
				if( SpaceInfo[i].is_vendingMac == 1 ) {
					tmpPath_1 = get_Path(myCampusGraph, i, sVertex);
					tmpPath_2 = get_Path(myCampusGraph, eVertex, i);
					tmpTime = restTime - getDistance_Path(myCampusGraph, tmpPath_1) - getDistance_Path(myCampusGraph, tmpPath_2);
					
					if( tmpTime >= 3 && tmpTime <= 10 ) {
						printf("    - ������ ��θ� ���� ���Ǳ⸦ %2d�� ���� �̿��� �� �ֽ��ϴ�.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - �ִ� %2d�� ���� ���Ǳ� �̿�...\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_2);
					}
				}
				break;
		}
		
	}
}

/*
*
*	display user interface...
*
*/
void UI_upLine() {
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
}

void UI_downLine() {
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
}

void UI_clear() {
	system("cls");
}

void UI_viewTimeTable() {
	int i;
	
	for (i = 0; i < DAYS_FOR_WEEK; i++) {
	    printf("< %d > < BEGIN >\n", i);
	    display_TTList(&myTimeTable[i]);
		printf("< %d > < END >\n", i);
	}

	printf("\n\n\n");
	
} 

void UI_FirstMain() {
	UI_upLine();
	printf("��        Sample Program        ��\n");
	UI_downLine();
	UI_upLine();
	printf("��  1. �ð�ǥ �Է��ϱ�          ��\n");
	printf("��  2. �ð�ǥ �ҷ�����          ��\n");
	printf("��  9. ���α׷� ����            ��\n");
	UI_downLine();
	UI_upLine();
	printf("��  Select:                     ��\n");
	UI_downLine();
	
	gotoxy(12, 10);
}

void UI_SecondMain() {
	UI_upLine();
	printf("��        Sample Program        ��\n");
	UI_downLine();
	UI_upLine();
	printf("��  1. �ð�ǥ ��ȿ�� �˻��ϱ�   ��\n");
	printf("��  2. ������ ���� �߰��ϱ�     ��\n");
	printf("��  9. ���α׷� ����            ��\n");
	UI_downLine();
	UI_upLine();
	printf("��  Select:                     ��\n");
	UI_downLine();
	
	gotoxy(12, 10);
}

void gotoxy(int x, int y) {
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
