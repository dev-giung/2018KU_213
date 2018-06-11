#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include "graphHandle.h"
#include "spaceHandle.h"
#include "timeTableHandle.h"

#define LECTURE_REST 0.25            // 강의 사이 시간은 15분 이걸 소수로 환산

void UI_upLine();
void UI_downLine();
void UI_clear();
void UI_viewTimeTable();
void UI_firstMain();
void gotoxy(int x, int y);

int checkVal_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph);
void display_namedPath(Path p);

void suggest_schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * g);
double rest_time(TimeTableNode * ttl);
void give_up(TimeTableNode * phead, TimeTableNode * removed, double between_time);
void utility(Space SpaceInfo[SPACE_NUMBER], int ID);
void utility_list(Space sp);
int daily_lecture_num(TimeTableNode * ttl);


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
			
			printf(">> %s -> %s\n", curr_node->name, curr_node->rlink->name);
			
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
			
			printf(">> %s -> %s\n", curr_node->name, curr_node->rlink->name);
			
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

void suggest_schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * g) {
	
   int i,j;
   int lecture_num;                                    // 그날 수업 수
   int distance;                                       // 현재 위치와 다음 수업 위치간 최단경로(시간) 저장할 변수
   double moveTime;                                    // distance와 같은 의미의 data type만 다른 변수
   double between_time;                                 // 다음 수업과 현재 수업 사이의 여유 시간
   double restTime;                                    // 다음 수업 이동 후 남게 되는 여유 시간(연강일 때 주로 사용)
   Path myPath;


   for (i = 0;i < DAYS_FOR_WEEK;i++) {                        // 월화수목금 5일

      printf("%s\n",day[i]);                              // 그날의 요일

      TimeTableNode * ttl = (&myTimeTable[i])->rlink;            // 첫 수업을 가리키는 포인터

      lecture_num = daily_lecture_num(&myTimeTable[i]);         // 해당 요일의 강의 수
      j = 1;

      while (j<=lecture_num) {      


         between_time = rest_time(ttl);

         if (between_time != -1) {                        // 마지막 수업이 아닐 때를 의미. -1은 마지막 수업
            if (between_time == LECTURE_REST) {               // 연이어서 강의 있을 때
               //myPath = get_Path(g, ttl->posIndex, ttl->rlink->posIndex);   // 최단경로 구하기(시작점 끝점의 경로 표시가 display_path에선 거꾸로 나타나있더라구요)
               myPath = get_Path(g, ttl->rlink->posIndex, ttl->posIndex);
               distance = getDistance_Path(g, myPath);         // 최단시간 구하기
               moveTime = distance;                     // 대입
               if (moveTime >= (int)(LECTURE_REST*60)) {               // 애초에 15분을 넘어서는 경로라면
                  between_time += ttl->rlink->eTime - ttl->rlink->sTime;      // 깔끔하게 담 수업 재끼고(왠만해선 삭제하는 방향으로) 추가되는 여유 시간 확보
                  give_up(ttl,ttl->rlink,between_time);
               }
               else {
                  restTime = between_time*60 - moveTime;      // 도착 후 생기는 여유 시간 계산
                  printf("다음수업 이동까지 남은 시간 : %d분\n", (int)(between_time * 60));
                  printf("최단경로로 이동했을 시 걸리는 시간 : %d분\n", distance);
                  display_Path(myPath);
                  printf("이동 후 남게 되는 여유시간 : %d분\n", (int)(restTime));
                  
               }



            }
            else if (between_time > LECTURE_REST) {
               //myPath = get_Path(g, ttl->posIndex, ttl->rlink->posIndex);   // 최단경로 구하기
               myPath = get_Path(g, ttl->rlink->posIndex, ttl->posIndex);
               distance = getDistance_Path(g, myPath);         // 최단시간 구하기
               moveTime = distance;                     // 대입
               if (moveTime >= (int)(LECTURE_REST * 60)) {               // 애초에 15분을 넘어서는 경로라면
                  between_time += ttl->rlink->eTime - ttl->rlink->sTime;      // 깔끔하게 담 수업 재끼고(왠만해선 삭제하는 방향으로) 추가되는 여유 시간 확보
                  give_up(ttl, ttl->rlink, between_time);
               }
               else {
                  restTime = between_time * 60 - moveTime;      // 도착 후 생기는 여유 시간 계산
                  printf("다음수업 이동까지 남은 시간 : %d분\n", (int)(between_time * 60));
                  printf("최단경로로 이동했을 시 걸리는 시간 : %d분\n", distance);
                  display_Path(myPath);
                  printf("이동 후 남게 되는 여유시간 : %d분\n", (int)(restTime));

               }
            }
         }

         ttl = ttl->rlink;
         j++;
      }

   }
}

int daily_lecture_num(TimeTableNode * ttl) {
   TimeTableNode * tmp = ttl;
   int daily_lecture = 0;
   while (tmp->rlink != ttl) {
      daily_lecture++;
      tmp = tmp->rlink;
   }

   return daily_lecture;
}

void give_up(TimeTableNode * phead, TimeTableNode * removed,double between_time) {
   remove_TTNode(phead, removed);
   printf("다음 시간 재끼도록 하겠습니다\n총 확보된 시간 : ");
   printf("%.2f\n", between_time);
}

double rest_time(TimeTableNode * ttl) {                     // 현재 수업과 다음 수업까지의 여유시간을 반환하는 함수
   if (ttl->rlink != NULL) {
      return ttl->rlink->sTime - ttl->eTime;
   }

   return -1;
}
