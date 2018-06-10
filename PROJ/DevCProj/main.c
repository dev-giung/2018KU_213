#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "graphHandle.h"
#include "spaceHandle.h"
#include "timeTableHandle.h"

#define LECTURE_REST 0.25            // ���� ���� �ð��� 15�� �̰� �Ҽ��� ȯ��

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
	
	/*
	for (i = 0; i < DAYS_FOR_WEEK; i++) {
	    printf("< %d > < BEGIN >\n", i);
	    display_TTList(&myTimeTable[i]);
		printf("< %d > < END >\n", i);
	}

	printf("\n\n\n");
	*/
	
	//suggest_schedule(myTimeTable, SpaceInfo, &myCampusGraph);
	
	i = checkVal_Schedule(myTimeTable, SpaceInfo, &myCampusGraph);
	
	return 0;
	
}

/*
*
*	check validity of the time table...
*
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
			
			printf(">> %s -> %s\n", curr_node->name, curr_node->rlink->name);
			
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
	
	printf("�� %d���� ��ȿ���� ���� ��ȹ�� �����մϴ�.", num);

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

void suggest_schedule(TimeTableNode myTimeTable[DAYS_FOR_WEEK], Space SpaceInfo[SPACE_NUMBER], GraphType * g) {
	
   int i,j;
   int lecture_num;                                    // �׳� ���� ��
   int distance;                                       // ���� ��ġ�� ���� ���� ��ġ�� �ִܰ��(�ð�) ������ ����
   double moveTime;                                    // distance�� ���� �ǹ��� data type�� �ٸ� ����
   double between_time;                                 // ���� ������ ���� ���� ������ ���� �ð�
   double restTime;                                    // ���� ���� �̵� �� ���� �Ǵ� ���� �ð�(������ �� �ַ� ���)
   Path myPath;


   for (i = 0;i < DAYS_FOR_WEEK;i++) {                        // ��ȭ����� 5��

      printf("%s\n",day[i]);                              // �׳��� ����

      TimeTableNode * ttl = (&myTimeTable[i])->rlink;            // ù ������ ����Ű�� ������

      lecture_num = daily_lecture_num(&myTimeTable[i]);         // �ش� ������ ���� ��
      j = 1;

      while (j<=lecture_num) {      


         between_time = rest_time(ttl);

         if (between_time != -1) {                        // ������ ������ �ƴ� ���� �ǹ�. -1�� ������ ����
            if (between_time == LECTURE_REST) {               // ���̾ ���� ���� ��
               //myPath = get_Path(g, ttl->posIndex, ttl->rlink->posIndex);   // �ִܰ�� ���ϱ�(������ ������ ��� ǥ�ð� display_path���� �Ųٷ� ��Ÿ���ִ��󱸿�)
               myPath = get_Path(g, ttl->rlink->posIndex, ttl->posIndex);
               distance = getDistance_Path(g, myPath);         // �ִܽð� ���ϱ�
               moveTime = distance;                     // ����
               if (moveTime >= (int)(LECTURE_REST*60)) {               // ���ʿ� 15���� �Ѿ�� ��ζ��
                  between_time += ttl->rlink->eTime - ttl->rlink->sTime;      // ����ϰ� �� ���� �糢��(�ظ��ؼ� �����ϴ� ��������) �߰��Ǵ� ���� �ð� Ȯ��
                  give_up(ttl,ttl->rlink,between_time);
               }
               else {
                  restTime = between_time*60 - moveTime;      // ���� �� ����� ���� �ð� ���
                  printf("�������� �̵����� ���� �ð� : %d��\n", (int)(between_time * 60));
                  printf("�ִܰ�η� �̵����� �� �ɸ��� �ð� : %d��\n", distance);
                  display_Path(myPath);
                  printf("�̵� �� ���� �Ǵ� �����ð� : %d��\n", (int)(restTime));
                  
               }



            }
            else if (between_time > LECTURE_REST) {
               //myPath = get_Path(g, ttl->posIndex, ttl->rlink->posIndex);   // �ִܰ�� ���ϱ�
               myPath = get_Path(g, ttl->rlink->posIndex, ttl->posIndex);
               distance = getDistance_Path(g, myPath);         // �ִܽð� ���ϱ�
               moveTime = distance;                     // ����
               if (moveTime >= (int)(LECTURE_REST * 60)) {               // ���ʿ� 15���� �Ѿ�� ��ζ��
                  between_time += ttl->rlink->eTime - ttl->rlink->sTime;      // ����ϰ� �� ���� �糢��(�ظ��ؼ� �����ϴ� ��������) �߰��Ǵ� ���� �ð� Ȯ��
                  give_up(ttl, ttl->rlink, between_time);
               }
               else {
                  restTime = between_time * 60 - moveTime;      // ���� �� ����� ���� �ð� ���
                  printf("�������� �̵����� ���� �ð� : %d��\n", (int)(between_time * 60));
                  printf("�ִܰ�η� �̵����� �� �ɸ��� �ð� : %d��\n", distance);
                  display_Path(myPath);
                  printf("�̵� �� ���� �Ǵ� �����ð� : %d��\n", (int)(restTime));

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
   printf("���� �ð� �糢���� �ϰڽ��ϴ�\n�� Ȯ���� �ð� : ");
   printf("%.2f\n", between_time);
}

double rest_time(TimeTableNode * ttl) {                     // ���� ������ ���� ���������� �����ð��� ��ȯ�ϴ� �Լ�
   if (ttl->rlink != NULL) {
      return ttl->rlink->sTime - ttl->eTime;
   }

   return -1;
}

void utility(Space SpaceInfo[SPACE_NUMBER], int ID) {         // �ǹ� �� �̿� �ü� ���� �Լ�
   int choose;
   do {
      printf("�ǹ� �� �ü��� �̿��Ͻðڽ��ϱ�? �� : 1 �ƴϿ� : 0\n �� �� �ϳ� ���� -> ");
      scanf("%d", &choose);
         if (choose == 0) {
            return;
         }
         else if (choose == 1) {
            printf("%s �� �̿밡���� �ü���\n", SpaceInfo[ID].name);
            utility_list(SpaceInfo[ID]);
            break;
         }
         else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
         }
      
   } while (choose != 0 && choose != 1);
}

void utility_list(Space sp) {
   if (sp.is_cafe == 1) {
      printf("ī��\n");
   }

   if (sp.is_convenience == 1) {
      printf("������\n");
   }
   
   if (sp.is_copyMac == 1) {
      printf("�����\n");
   }
   if (sp.is_lounge == 1) {
      printf("�����\n");
   }

   if (sp.is_vendingMac == 1) {
      printf("���Ǳ�\n");
   }
}
