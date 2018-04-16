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
		printf("메모리 할당에러\n");
		return;
	} else {
		temp -> item = item;
		temp -> link = s -> top;
		s -> top = temp;
	}
}

int pop(LinkedStackType *s) {
	if( is_empty(s) ) {
		printf("스택이 비어있음\n");
		exit(1);
	} else {
		StackNode *temp = s -> top;
		int item = temp -> item;
		s -> top = s -> top -> link;
		free(temp);
		return item;
	}
}

void stackWay(LinkedStackType *s, int map[][10], int cur) {
	
	int row = cur / 10;
	int col = cur % 10;
	
	if( row + 1 < 10 && map[row + 1][col] == 0 ) {
		printf("push (row: %d, col: %d)\n", row + 1, col);
		push(s, (row + 1) * 10 + col);
	}
	
	if( row - 1 > -1 && map[row - 1][col] == 0 ) {
		printf("push (row: %d, col: %d)\n", row - 1, col);
		push(s, (row - 1) * 10 + col);
	}
	
	if( col - 1 > -1 && map[row][col - 1] == 0 ) {
		printf("push (row: %d, col: %d)\n", row, col - 1);
		push(s, row * 10 + (col - 1));
	}
	
	if( col + 1 < 10 && map[row][col + 1] == 0 ) {
		printf("push (row: %d, col: %d)\n", row, col + 1);
		push(s, row * 10 + (col + 1));
	}
}

/*
	function: main 함수
	Note	: 
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	// 미로 데이터 입력
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
	
	int current = 10;
	
	LinkedStackType s;
	init(&s);
	
	while(1) {
		
		if(current == 89) {
			break;
		}
		stackWay(&s, maze, current);
		maze[current / 10][current % 10] = 2;
		current = pop(&s);
		printf("pop (row: %d, col: %d)\n", current / 10, current % 10);
	}
	
}
