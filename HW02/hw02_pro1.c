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
			printf("< %d\t%s\t%3d >\n", p -> student_number, p -> name, p -> score);
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
			printf("< %d\t%s\t%3d >\n", p -> student_number, p -> name, p -> score);
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
	int input_sn;
	char input_name[100];
	int index = 0;
	
	// �����õ弳�� 
	srand(time(NULL));

	// ����Ʈ �ʱ�ȭ
	init(&head_node);
	
	// ������ ���� ��� ���� �����͸� ���߿��Ḯ��Ʈ�� ���� 
	while(EOF != fscanf(f, "%d	%[^\n]s", &input_sn, &input_name)) {
		
		// �޸� Ȯ�� 
		data[index] = (student *)malloc(sizeof(student));
		
		// student_number���� ���Ϸκ����� �й��� �־���
		data[index] -> student_number = input_sn;
		
		// name���� ���Ϸκ����� �̸��� �־��� 
		strcpy(data[index] -> name, input_name);
		
		// score���� 0 ~ 100 ������ �־���
		data[index] -> score = rand() % 101;
		
		// ���κ����� ��� �Էµ� ��带 ����Ʈ�� ����
		dinsert_node(&head_node, data[index]);
		
		index++;
	}
	
	// ���� ���� 10���� ���� ���
	printf("���� ���� 10���� <�й� �̸� ����>: \n");
	displayHigh(&head_node, 10);
	
	// ���� ���� 10���� ���� ���
	printf("���� ���� 10���� <�й� �̸� ����>: \n");
	displayLow(&head_node, 10);
	
	// ���α׷� ����
	return 0;
}
