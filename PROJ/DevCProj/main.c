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
			printf("\n미구현...");
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
		
		printf("=== %s 시간표의 유효성을 검사합니다.\n", day[i]);
		
		TimeTableNode * head_node = &myTimeTable[i];
		TimeTableNode * curr_node = head_node->rlink;
		
		while( curr_node != NULL && curr_node->rlink != head_node ) {
			
			tempPath = get_Path( myCampusGraph, curr_node->rlink->posIndex, curr_node->posIndex );
			
			printf("= (%02d : %02d) %s ", (int)curr_node->sTime, (int)(curr_node->sTime - (int)curr_node->sTime) * 60, curr_node->name);
			printf(">> (%02d : %02d) %s \n", (int)curr_node->rlink->sTime, (int)(curr_node->rlink->sTime - (int)curr_node->rlink->sTime) * 60, curr_node->rlink->name);
			
			printf("  - 이동경로: ");
			display_namedPath(tempPath);
			
			restTime = ( curr_node->rlink->sTime - curr_node->eTime ) * 60.0;
			printf("  - 여유시간: %2.0f분\n", restTime);
			
			moveTime = getDistance_Path( myCampusGraph, tempPath );
			printf("  - 이동시간: %2.0f분\n", moveTime);
			
			if( restTime < moveTime ) {
				
				num++;
				printf("    - 문제발견! 여유시간보다 이동시간이 깁니다.\n");
				printf("    - 계속 검사하려면 아무 키나 누르세요...\n");
				getch();
			} else {
				
				sleep(1);
			} 
			
			curr_node = curr_node->rlink;
		}
		
		printf("=== %s end\n\n", day[i]);
	}
	
	printf("총 %d개의 유효하지 않은 계획이 존재합니다.\n\n", num);
	printf("메인화면으로 돌아가려면 아무 키나 누르세요...");
	
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
		
		printf("=== %s 공강시간을 검사합니다.\n", day[i]);
		
		TimeTableNode * head_node = &myTimeTable[i];
		TimeTableNode * curr_node = head_node->rlink;
		
		while( curr_node != NULL && curr_node->rlink != head_node ) {
			
			tempPath = get_Path( myCampusGraph, curr_node->rlink->posIndex, curr_node->posIndex );
			
			printf("= (%02d : %02d) %s ", (int)curr_node->sTime, (int)(curr_node->sTime - (int)curr_node->sTime) * 60, curr_node->name);
			printf(">> (%02d : %02d) %s \n", (int)curr_node->rlink->sTime, (int)(curr_node->rlink->sTime - (int)curr_node->rlink->sTime) * 60, curr_node->rlink->name);
			
			printf("  - 이동경로: ");
			display_namedPath(tempPath);
			
			restTime = ( curr_node->rlink->sTime - curr_node->eTime ) * 60.0;
			printf("  - 여유시간: %2.0f분\n", restTime);
			
			moveTime = getDistance_Path( myCampusGraph, tempPath );
			printf("  - 이동시간: %2.0f분\n", moveTime);
			
			if( restTime < moveTime ) {
				
				num++;
				printf("    - 문제발견! 여유시간보다 이동시간이 깁니다.\n");
				printf("    - 무시하고 진행하려면 아무 키나 누르세요...\n");
				getch();
				
			} else if( restTime - moveTime >= 20 ) {
				
				printf("    - %2.0f분의 여유시간이 감지되었습니다.\n", restTime - moveTime);
				printf("    - 여유시간을 보낼 경유지를 선택하세요.\n");
				printf("        1. 카페\n");
				printf("        2. 편의점\n");
				printf("        3. 복사기\n");
				printf("        4. 라운지\n");
				printf("        5. 자판기\n");
				printf("        9. 아무것도 하지 않음\n");
				printf("    - Select : ");
				scanf("%d", &selection);
				
				findStopover(SpaceInfo, myCampusGraph, curr_node->posIndex, curr_node->rlink->posIndex, selection, restTime);
				
			} else if( restTime - moveTime >= 5 ) {
				
				printf("    - %2.0f분의 여유시간이 감지되었습니다.\n", restTime - moveTime);
				utility(SpaceInfo, curr_node->posIndex);
				utility(SpaceInfo, curr_node->rlink->posIndex);
				
			}  else {
				
				sleep(1);
			} 
			
			curr_node = curr_node->rlink;
		}
		
		printf("=== %s end\n\n", day[i]);
	}
	
	printf("총 %d개의 유효하지 않은 계획이 존재합니다.\n\n", num);
	printf("메인화면으로 돌아가려면 아무 키나 누르세요...");
	
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

void utility(Space SpaceInfo[SPACE_NUMBER], int ID) {         // 건물 내 이용 시설 관련 함수
   int choose;
   do {
      printf("    - %s 내 시설을 이용하시겠습니까? (예 : 1 / 아니오 : 0)\n", SpaceInfo[ID].name);
      printf("    - Select : ");
      scanf("%d", &choose);
         if (choose == 0) {
            return;
         }
         else if (choose == 1) {
            printf("    - %s 내 이용가능한 시설들\n", SpaceInfo[ID].name);
            utility_list(SpaceInfo[ID]);
            break;
         }
         else {
            printf("    - 잘못된 입력입니다. 다시 선택해주세요.\n");
         }
      
   } while (choose != 0 && choose != 1);
}

void utility_list(Space sp) {
	
   if (sp.is_cafe == 1) {
      printf("      - 카페\n");
   }

   if (sp.is_convenience == 1) {
      printf("      - 편의점\n");
   }
   
   if (sp.is_copyMac == 1) {
      printf("      - 복사기\n");
   }
   
   if (sp.is_lounge == 1) {
      printf("      - 라운지\n");
   }

   if (sp.is_vendingMac == 1) {
      printf("      - 자판기\n");
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
						printf("    - 다음의 경로를 통해 카페를 %2d분 동안 이용할 수 있습니다.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - 최대 %2d분 동안 카페 이용...\n", tmpTime);
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
						printf("    - 다음의 경로를 통해 편의점을 %2d분 동안 이용할 수 있습니다.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - 최대 %2d분 동안 편의점 이용...\n", tmpTime);
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
						printf("    - 다음의 경로를 통해 복사기를 %2d분 동안 이용할 수 있습니다.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - 최대 %2d분 동안 복사기 이용...\n", tmpTime);
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
						printf("    - 다음의 경로를 통해 라운지를 %2d분 동안 이용할 수 있습니다.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - 최대 %2d분 동안 라운지 이용...\n", tmpTime);
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
						printf("    - 다음의 경로를 통해 자판기를 %2d분 동안 이용할 수 있습니다.\n", tmpTime);
						printf("      - ");
						display_namedPath(tmpPath_1);
						printf("      - 최대 %2d분 동안 자판기 이용...\n", tmpTime);
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
	printf("┌──────────");
	printf("──────────");
	printf("──────────┐\n");
}

void UI_downLine() {
	printf("└──────────");
	printf("──────────");
	printf("──────────┘\n");
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
	printf("│        Sample Program        │\n");
	UI_downLine();
	UI_upLine();
	printf("│  1. 시간표 입력하기          │\n");
	printf("│  2. 시간표 불러오기          │\n");
	printf("│  9. 프로그램 종료            │\n");
	UI_downLine();
	UI_upLine();
	printf("│  Select:                     │\n");
	UI_downLine();
	
	gotoxy(12, 10);
}

void UI_SecondMain() {
	UI_upLine();
	printf("│        Sample Program        │\n");
	UI_downLine();
	UI_upLine();
	printf("│  1. 시간표 유효성 검사하기   │\n");
	printf("│  2. 공강에 일정 추가하기     │\n");
	printf("│  9. 프로그램 종료            │\n");
	UI_downLine();
	UI_upLine();
	printf("│  Select:                     │\n");
	UI_downLine();
	
	gotoxy(12, 10);
}

void gotoxy(int x, int y) {
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
