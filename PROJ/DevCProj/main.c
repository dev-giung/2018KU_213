#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "graphHandle.h"
#include "spaceHandle.h"
#include "timeTableHandle.h"

#define LECTURE_REST 0.25            // 강의 사이 시간은 15분 이걸 소수로 환산

void suggest_schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * g);
double rest_time(TimeTableNode * ttl);
void give_up(TimeTableNode * phead, TimeTableNode * removed, double between_time);
void utility(Space SpaceInfo[SPACE_NUMBER], int ID);
void utility_list(Space sp);
int daily_lecture_num(TimeTableNode * ttl);


char * day[DAYS_FOR_WEEK] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};


int main() {

	int i;
	
	// load campus graph data
	initialize_Graph(&myCampusGraph);
	loadTXT_Graph(&myCampusGraph);
	
	// load space data
	loadTXT_SpaceInfo(SpaceInfo);
	
	// load time table data
	for ( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		initialize_TTList(&myTimeTable[i]);
	}
	loadTXT_TimeTable(myTimeTable);
   
	
	for (i = 0; i < DAYS_FOR_WEEK; i++) {
	    printf("< %d > < BEGIN >\n", i);
	    display_TTList(&myTimeTable[i]);
		printf("< %d > < END >\n", i);
	}
	
	printf("\n\n\n");
	
	//suggest_schedule(myTimeTable, SpaceInfo, &myCampusGraph);
	
	checkVal_Schedule(myTimeTable, SpaceInfo, myCampusGraph);
	
	return 0;
	
}

void checkVal_Schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * myCampusGraph) {
	
	int i;
	double moveTime;
	double restTime;
	
	for( i = 0; i < DAYS_FOR_WEEK; i++ ) {
		
		printf("check validity of %s's time table...\n", day[i]);
		
		TimeTableNode * head_node = &myTimeTable[i];
		TimeTableNode * curr_node = head_node->rlink;
		
		while( curr_node != NULL && curr_node->rlink != head_node ) {
			
			restTime = ( curr_node->rlink->sTime - curr_node->eTime ) * 60.0;
			printf("restTime: %f\n", restTime);
			moveTime = getDistance_Path( myCampusGraph, get_Path( myCampusGraph, curr_node->rlink->posIndex, curr_node->posIndex ) );
			printf("moveTime: %f\n", moveTime);
			
			if( restTime < moveTime ) {
				
				//printf("%s\n", curr_node->name);
				printf("문제발견!\n");
			}
			
			curr_node = curr_node->rlink;
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

void utility(Space SpaceInfo[SPACE_NUMBER], int ID) {         // 건물 내 이용 시설 관련 함수
   int choose;
   do {
      printf("건물 내 시설을 이용하시겠습니까? 예 : 1 아니오 : 0\n 둘 중 하나 선택 -> ");
      scanf("%d", &choose);
         if (choose == 0) {
            return;
         }
         else if (choose == 1) {
            printf("%s 내 이용가능한 시설들\n", SpaceInfo[ID].name);
            utility_list(SpaceInfo[ID]);
            break;
         }
         else {
            printf("잘못된 입력입니다. 다시 선택해주세요.\n");
         }
      
   } while (choose != 0 && choose != 1);
}

void utility_list(Space sp) {
   if (sp.is_cafe == 1) {
      printf("카페\n");
   }

   if (sp.is_convenience == 1) {
      printf("편의점\n");
   }
   
   if (sp.is_copyMac == 1) {
      printf("복사기\n");
   }
   if (sp.is_lounge == 1) {
      printf("라운지\n");
   }

   if (sp.is_vendingMac == 1) {
      printf("자판기\n");
   }
}
