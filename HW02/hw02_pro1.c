#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// student 구조체 정의 
typedef struct student {
	
	// Data Field
	char name[100];
	int student_number;
	int score;
	
	// Link Field
	struct student *llink;
	struct student *rlink;
	
} student;

/*
	function: 이중연결리스트를 초기화 
	Note	: 
	input	: 
	output	: (NULL)
*/
void init(student *phead) {
	
	(phead -> llink) = phead;
	(phead -> rlink) = phead;
	phead -> score = 100;
}

/*
	function: 이중연결리스트에 요소를 삽입
	Note	: 요소들의 score 값이 내림차순이 되도록 삽입함. 
	input	: 
	output	: 
*/
void dinsert_node(student *before, student *new_node) {
	
	while(1) {
		if(before -> rlink == before) {
			break;
		}
		if(new_node -> score > before -> rlink -> score) {
			break;
		} else {
			before = before -> rlink;
		}
	}
	
	( new_node -> llink ) = before;
	( new_node -> rlink ) = ( before -> rlink );
	( ( before -> rlink ) -> llink ) = new_node;
	( before -> rlink ) = new_node;
}

void display(student *phead) {
	student *p;
	for(p = phead -> rlink; p != phead; p = p -> rlink) {
		printf("< |%x| %d |%x| >\n", p -> llink, p -> score, p -> rlink);
	}
	printf("\n");
}

/*
	function: 성적 상위 n명 데이터 출력
	Note	:
	input	:
	output	: (NULL)
*/
void displayHigh(student *phead, int n) {
	
	// something
}

/*
	function: 성적 하위 n명 데이터 출력
	Note	:
	input	:
	output	: (NULL)
*/
void displayLow(student *phead, int n) {
	
	// something
}

/*
	function: main 함수
	Note	: 데이터 파일의 서식이 적절하지 못하면 오류가 발생하나 고려하지 않음.
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	FILE *f = NULL;
	
	// Student_info.txt 데이터 파일 불러오기 
	if( (f = fopen("Student_info.txt", "r")) == NULL ) {
		
		// 불러오지 못하면 Error 출력 및 프로그램 종료 
		printf("Error: Student_info.txt 파일을 찾을 수 없습니다.");
		return 1;
	}
	
	student head_node;
	student *data[10];
	int i;
	
	init(&head_node);
	display(&head_node);
	
	data[0] = (student *)malloc(sizeof(student));
	data[0] -> score = 10;
	dinsert_node(&head_node, data[0]);
	display(&head_node);
	
	data[1] = (student *)malloc(sizeof(student));
	data[1] -> score = 20;
	dinsert_node(&head_node, data[1]);
	display(&head_node);
	
	data[2] = (student *)malloc(sizeof(student));
	data[2] -> score = 5;
	dinsert_node(&head_node, data[2]);
	display(&head_node);
	
	display(&head_node);
	
	// 프로그램 종료 
	return 0;
}
