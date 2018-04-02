#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// student ����ü ���� 
typedef struct student {
	
	// ����ü ���� ���� (108 Byte) 
	char name[100];
	int student_number;
	int score;
} student;

/*
	function: student ����ü �迭 score ������ ��հ��� ����
	input	: s(student[]) : score���� �Էµ� ����ü �迭 (call by reference)
			  n(int) : score���� �� 
	output	: double 
*/
double get_mean(student s[], int n) {
	
	int i = 0;
	double sum = 0;
	
	for(i = 0; i < n; i++) {
		
		// score �� ��� ���ؼ� sum�� ���� 
		sum += s[i].score;
	}
	
	// ��հ�(double) ��ȯ 
	return sum / n;
}

/*
	function: student ����ü �迭 score ������ ǥ���������� ����
	input	: s(student[]) : score���� �Էµ� ����ü �迭 (call by reference)
			  n(int) : score���� ��
	output	: double
*/
double get_deviation(student s[], int n) {
	
	int i = 0;
	double sum = 0;
	
	// ��հ� mean�� ���� 
	double mean = get_mean(s, n);
	
	for(i = 0; i < n; i++) {
		
		// �������� �� ��� ���ؼ� sum�� ���� 
		sum += pow((s[i].score - mean), 2);
	}
	
	// ǥ��������(double) ��ȯ 
	return sqrt(sum / n);
}

/*
	function: student ����ü �迭 �����͸� ��� 
	input	: s(student[]) : ���� �Էµ� ����ü �迭 (call by reference)
			  n(int) : �迭 ������ �� 
	output	: (Null)
*/
void printData(student s[], int n) {
	
	int i = 0;
	
	for(i = 0; i < n; i++) {
		
		// �й� �̸� ���� ������ ��� 
		printf("%d\t%20s\t%d\n", s[i].student_number, s[i].name, s[i].score);
	}
	printf("\n");
}

/*
	function: main �Լ�
	Note	: ������ ������ ������ �������� ���ϸ� ������ �߻��ϳ� ������� ����.
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	FILE *f = NULL;
	
	// Student_info.txt ������ ���� �ҷ����� 
	if( (f = fopen("Student_info.txt", "r")) == NULL ) {
		
		// �ҷ����� ���ϸ� Error ��� �� ���α׷� ���� 
		printf("Error: Student_info.txt ������ ã�� �� �����ϴ�.");
		return 1;
	}
	
	// �������� 
	student students[100];
	char *ptr;
	int index = 0;
	
	// �����õ弳��
	srand(time(NULL));	

	// ������ ���� ��� ���� �����͸� students ����ü �迭�� �Է�
	while(EOF != fscanf(f, "%d	%[^\n]s", &students[index].student_number, &students[index].name)) {
		
		// score���� 0 ~ 100 ���� �� �־���
		students[index].score = rand() % 101;  
		index++;
	}
	
	// �Էµ� ������ ��� 
	printData(students, index);
	
	// �л� �� ��� 
	printf("Number of Students: %d\n", index);
	
	// ������ ��� ��� 
	printf(" mean of scores: %.2f\n", get_mean(students, index));
	
	// ������ ǥ������ ��� 
	printf("stdev of scores: %.2f", get_deviation(students, index));
	
	// ���α׷� ���� 
	return 0;
}
