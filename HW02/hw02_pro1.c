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
	function: 이중연결리스트에 요소를 삽입
	Note	: 
	input	: 
	output	: 
*/
void dinsert_node() {
	
	// something
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
	
	// something
	
	// 프로그램 종료 
	return 0;
}
