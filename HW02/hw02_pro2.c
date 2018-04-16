#include <stdio.h>

typedef struct StackNode {
	int item;
	struct StackNode *link;
} StackNode;

typedef struct LinkedStackType {
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s) {
	s -> top = NULL;
}

int is_empty(LinkedStackType *s) {
	return (s -> top == NULL);
}

void push(LinkedStackType *s, int item) {
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp == NULL) {
		printf("�޸� �Ҵ翡��\n");
		return;
	} else {
		temp -> item = item;
		temp -> link = s -> top;
		s -> top = temp;
	}
}

int pop(LinkedStackType *s) {
	if( is_empty(s) ) {
		printf("������ �������\n");
		exit(1);
	} else {
		StackNode *temp = s -> top;
		int item = temp -> item;
		s -> top = s -> top -> link;
		free(temp);
		return item;
	}
}

/*
	function: main �Լ�
	Note	: 
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	// �̷� ������ �Է�
	int maze[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	
}
