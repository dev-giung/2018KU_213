#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// student ����ü ���� 
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
	function: ���߿��Ḯ��Ʈ�� ��Ҹ� ����
	Note	: 
	input	: 
	output	: 
*/
void dinsert_node() {
	
	// something
}

/*
	function: ���� ���� n�� ������ ���
	Note	:
	input	:
	output	: (NULL)
*/
void displayHigh(student *phead, int n) {
	
	// something
}

/*
	function: ���� ���� n�� ������ ���
	Note	:
	input	:
	output	: (NULL)
*/
void displayLow(student *phead, int n) {
	
	// something
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
	
	// something
	
	// ���α׷� ���� 
	return 0;
}
