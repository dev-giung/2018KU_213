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
	function: ���߿��Ḯ��Ʈ�� �ʱ�ȭ 
	Note	: 
	input	: 
	output	: (NULL)
*/
void init(student *phead) {
	
	(phead -> llink) = phead;
	(phead -> rlink) = phead;
}

/*
	function: ���߿��Ḯ��Ʈ�� ��Ҹ� ����
	Note	: ��ҵ��� score ���� ���������� �ǵ��� ������. 
	input	: 
	output	: 
*/
void dinsert_node(student *phead, student *new_node) {
	
	student *cur_node = phead;
	
	while(1) {
		
		if(cur_node -> rlink == phead) {
			break;
		}
		
		if(cur_node -> rlink -> score < new_node -> score) {
			break;
		}
		
		cur_node = cur_node -> rlink;
	}
	
	( new_node -> llink ) = cur_node;
	( new_node -> rlink ) = ( cur_node -> rlink );
	( ( cur_node -> rlink ) -> llink ) = new_node;
	( cur_node -> rlink ) = new_node;
}

void display(student *phead) {
	student *p;
	for(p = phead -> rlink; p != phead; p = p -> rlink) {
		printf("< |%x| %d |%x| >\n", p -> llink, p -> score, p -> rlink);
	}
	printf("\n");
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
	
	// ���α׷� ���� 
	return 0;
}
