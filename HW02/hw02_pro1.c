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
	Note	: llink, rlink ��� �ڱ��ڽ��� ����Ű���� �� 
	input	: student�� ������ (call by reference) 
	output	: (NULL)
*/
void init(student *phead) {
	
	(phead -> llink) = phead;
	(phead -> rlink) = phead;
}

/*
	function: ���߿��Ḯ��Ʈ�� ��Ҹ� ����
	Note	: ��ҵ��� score ���� ���������� �ǵ��� ������. 
	input	: student�� ������ (call by reference) 
	output	: (NULL)
*/
void dinsert_node(student *phead, student *new_node) {
	
	// cur_node �����ʹ� head���� ����Ŵ 
	student *cur_node = phead;
	
	while(1) {
		
		// ������(���� score ����) ����� ��� while�� ���� 
		if(cur_node -> rlink == phead) {
			break;
		}
		
		// ���� ��ġ(���� ��Һ��� score�� ū ��ġ) ã�� ��� while�� ���� 
		if(cur_node -> rlink -> score < new_node -> score) {
			break;
		}
		
		// ���� ��Ҹ� ����Ŵ.
		cur_node = cur_node -> rlink;
	}
	
	// ��� ���� 
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
	Note	: n�� ��ü ������ ������ Ŭ �ÿ��� �ִ¸�ŭ(��ü ������)�� ��� �� ������ �޼��� ��� 
	input	: student�� ������ (call by reference) 
	output	: (NULL)
*/
void displayHigh(student *phead, int n) {
	
	student *p = phead;
	int cnt = n;
	
	while(cnt) {
		p = p -> rlink;
		if(p == phead) {
			printf("��� �����͸� ����Ͽ����ϴ�. ���� %d���� �����ʹ� ��µ��� �ʽ��ϴ�.", cnt);
			break;
		} else {
			printf("< |%x| %d |%x| >\n", p -> llink, p -> score, p -> rlink);
		}
		cnt--;
	}
	printf("\n");
}

/*
	function: ���� ���� n�� ������ ���
	Note	: n�� ��ü ������ ������ Ŭ �ÿ��� �ִ¸�ŭ(��ü ������)�� ��� �� ������ �޼��� ��� 
	input	: student�� ������ (call by reference) 
	output	: (NULL)
*/
void displayLow(student *phead, int n) {
	
	student *p = phead;
	int cnt = n;
	
	while(cnt) {
		p = p -> llink;
		if(p == phead) {
			printf("��� �����͸� ����Ͽ����ϴ�. ���� %d���� �����ʹ� ��µ��� �ʽ��ϴ�.", cnt);
			break;
		} else {
			printf("< |%x| %d |%x| >\n", p -> llink, p -> score, p -> rlink);
		}
		cnt--;
	}
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
	student head_node;
	student *data[100];
	int index = 0;
	
	// �����õ弳�� 
	srand(time(NULL));

	// ����Ʈ �ʱ�ȭ
	init(&head_node);
	
	
	
	// ���α׷� ���� 
	return 0;
}
