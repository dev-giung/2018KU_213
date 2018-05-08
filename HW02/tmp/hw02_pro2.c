#include <stdio.h>
#include <stdlib.h>

typedef struct Point2D {
	int rowPos;
	int colPos;
} Point2D;

typedef struct StackNode {
	Point2D item;
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

void push(LinkedStackType *s, Point2D item) {
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

Point2D pop(LinkedStackType *s) {
	if( is_empty(s) ) {
		printf("스택이 비어있음\n");
		exit(1);
	} else {
		StackNode *temp = s -> top;
		Point2D item = temp -> item;
		s -> top = s -> top -> link;
		free(temp);
		return item;
	}
}

void printPath(LinkedStackType *s) {
	
	Point2D data;
	if( is_empty(s) ) {
		return;
	} else {
		data = pop(s);
		printPath(s);
		printf("(row:%2d, col:%2d) -> ", data.rowPos, data.colPos);
	}
}

void stackWay(LinkedStackType *s, int map[][10], Point2D cur) {
	
	int row = cur.rowPos;
	int col = cur.colPos;
	
	Point2D tmp;
	
	if( row + 1 < 10 && map[row + 1][col] == 0 ) {
		printf("push (row: %d, col: %d)\n", row + 1, col);
		
		tmp.rowPos = row + 1;
		tmp.colPos = col;
		push(s, tmp);
	}
	
	if( row - 1 > -1 && map[row - 1][col] == 0 ) {
		printf("push (row: %d, col: %d)\n", row - 1, col);
		
		tmp.rowPos = row - 1;
		tmp.colPos = col;
		push(s, tmp);
	}
	
	if( col - 1 > -1 && map[row][col - 1] == 0 ) {
		printf("push (row: %d, col: %d)\n", row, col - 1);
		
		tmp.rowPos = row;
		tmp.colPos = col - 1;
		push(s, tmp);
	}
	
	if( col + 1 < 10 && map[row][col + 1] == 0 ) {
		printf("push (row: %d, col: %d)\n", row, col + 1);
		
		tmp.rowPos = row;
		tmp.colPos = col + 1;
		push(s, tmp);
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
	
	Point2D current;
	current.rowPos = 1;
	current.colPos = 0;
	
	LinkedStackType s;
	LinkedStackType path;
	init(&s);
	init(&path);
	
	while(1) {
		
		if(current.rowPos == 8 && current.colPos == 9) {
			break;
		}
		stackWay(&s, maze, current);
		maze[current.rowPos][current.colPos] = 2;
		current = pop(&s);
		push(&path, current);
		printf("pop (row: %d, col: %d)\n", current.rowPos, current.colPos);
	}
	
	printf("\nResult Path:\n");
	printPath(&path);
	printf("finish");
}
