#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// student 구조체 정의 
typedef struct student {
	
	// 구조체 변수 정의 (108 Byte) 
	char name[100];
	int student_number;
	int score;
} student;

/*
	function: student 구조체 배열 score 변수의 평균값을 리턴
	input	: s(student[]) : score값이 입력된 구조체 배열 (call by reference)
			  n(int) : score값의 수 
	output	: double 
*/
double get_mean(student s[], int n) {
	
	int i = 0;
	double sum = 0;
	
	for(i = 0; i < n; i++) {
		
		// score 값 모두 더해서 sum에 저장 
		sum += s[i].score;
	}
	
	// 평균값(double) 반환 
	return sum / n;
}

/*
	function: student 구조체 배열 score 변수의 표준편차값을 리턴
	input	: s(student[]) : score값이 입력된 구조체 배열 (call by reference)
			  n(int) : score값의 수
	output	: double
*/
double get_deviation(student s[], int n) {
	
	int i = 0;
	double sum = 0;
	
	// 평균값 mean에 저장 
	double mean = get_mean(s, n);
	
	for(i = 0; i < n; i++) {
		
		// 편차제곱 값 모두 더해서 sum에 저장 
		sum += pow((s[i].score - mean), 2);
	}
	
	// 표준편차값(double) 반환 
	return sqrt(sum / n);
}

/*
	function: student 구조체 배열 데이터를 출력 
	input	: s(student[]) : 값이 입력된 구조체 배열 (call by reference)
			  n(int) : 배열 원소의 수 
	output	: (Null)
*/
void printData(student s[], int n) {
	
	int i = 0;
	
	for(i = 0; i < n; i++) {
		
		// 학번 이름 점수 순으로 출력 
		printf("%d\t%20s\t%d\n", s[i].student_number, s[i].name, s[i].score);
	}
	printf("\n");
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
	
	// 변수선언 
	student students[100];
	char *ptr;
	int index = 0;
	
	// 랜덤시드설정
	srand(time(NULL));	

	// 데이터 파일 모든 행의 데이터를 students 구조체 배열에 입력
	while(EOF != fscanf(f, "%d	%[^\n]s", &students[index].student_number, &students[index].name)) {
		
		// score에는 0 ~ 100 랜덤 값 넣어줌
		students[index].score = rand() % 101;  
		index++;
	}
	
	// 입력된 데이터 출력 
	printData(students, index);
	
	// 학생 수 출력 
	printf("Number of Students: %d\n", index);
	
	// 점수의 평균 출력 
	printf(" mean of scores: %.2f\n", get_mean(students, index));
	
	// 점수의 표준편차 출력 
	printf("stdev of scores: %.2f", get_deviation(students, index));
	
	// 프로그램 종료 
	return 0;
}
