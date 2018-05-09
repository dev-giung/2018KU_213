#include <stdio.h>
#include <stdlib.h>

#define VISITED 2 // �湮�� ������ VISITED�� ǥ��

/*
	Def : Point2D ����ü ����
	Note: 2���� �迭 ���� row, col ��ǥ�� ��Ÿ�� 
*/
typedef struct Point2D {
	
	// row index 
	int rowPos;
	
	// col index
	int colPos;
} Point2D;

/*
	Def : StackNode ����ü ����
	Note: Point2D �� �������� ���� ���ó�带 ��Ÿ�� 
*/
typedef struct StackNode {
	
	// Data Field
	Point2D item;
	
	// Link Field
	struct StackNode *link;
} StackNode;

/*
	Def : LinkedStackType ����ü ����
	Note: ���ó����� ���� ������ ��Ÿ��
*/
typedef struct LinkedStackType {
	
	// �ֻ���� ���ó�带 ����Ű�� ������ 
	StackNode *top;
} LinkedStackType;

/*
	function: ������ �ʱ�ȭ 
	Note	: ������ top �����Ͱ� NULL�� ����Ű�� �� 
	input	: LinkedStackType�� ������ (call by reference) 
	output	: (NULL)
*/
void init(LinkedStackType *s) {
	
	s -> top = NULL;
}

/*
	fuction: ������ ����ִ��� Ȯ��
	Note   : ��������� 1�� ��ȯ 
	input  : LinkedStackType�� ������ (call by reference) 
	output : int 
*/
int is_empty(LinkedStackType *s) {
	
	return (s -> top == NULL);
}

/*
	function: ������ push �Լ� 
	Note    : ���ÿ� ���ο� ���ó�带 push �� �ܼ����(���û���)
	input   : s(LinkedStackType *) : ���ó�尡 ���� ���� (call by reference)
			  item(Point2D) : ���Ե� ���ó���� ���κ���
			  n(int) : push ������ �ܼ���¿��� ����
	output  : (NULL)
*/
void push(LinkedStackType *s, Point2D item, int n) {
	
	// ���ο� ���ó�� �޸� �Ҵ�
	StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
	
	if(new_node == NULL) {
		
		// �޸� �Ҵ翡�� üũ 
		printf("�޸� �Ҵ翡��\n");
		return;
	} else {
		
		// ���ο� ���ó�� ���κ��� �Է� 
		new_node -> item = item;
		new_node -> link = s -> top;
		
		// ���ο� ���ó�带 ���ÿ� ���� 
		s -> top = new_node;
		
		// n�� 1�̸� push ���� �ܼ���� 
		if(n) {
			printf("push (row:%2d, col:%2d)\n", item.rowPos, item.colPos);
		}
	}
}

/*
	function: ������ pop �Լ� 
	Note    : ���� �ֻ���� ���ó�带 pop �� �ܼ����(���û���) 
	input   : s(LinkedStackType *) : ���ó�尡 ���� ���� (call by reference)
			  n(int) : pop ������ �ܼ���¿��� ���� 
	output  : Point
*/
Point2D pop(LinkedStackType *s, int n) {
	
	if( is_empty(s) ) {
		
		// �� ������ pop�� �� ���� 
		printf("������ �������\n");
		exit(1);
	} else {
		
		// ���� �ֻ���� ��尡 pop�� ��� 
		StackNode *removed_node = s -> top;
		
		// ������� ���κ��� item�� ���� 
		Point2D item = removed_node -> item;
		
		// ����� ���ÿ��� ���� 
		s -> top = s -> top -> link;
		free(removed_node);
		
		// n�� 1�̸� pop ���� �ܼ���� 
		if(n) {
			printf(" pop (row:%2d, col:%2d)\n", item.rowPos, item.colPos);
		}
		
		// ����尡 �����ִ� ���κ��� ��ȯ 
		return item;
	}
}

/*
	function: ������ġ�� �����ϰ� �̵������� ��ġ�� ���ÿ� push�ϴ� �Լ� 
	Note    : �̵����ɼ��� �ش� ��ġ�� ���尪(0�� ��쿡�� �̵� ����)�� index ���� ��ȿ������ �Ǻ� 
	input   : s(LinkedStackType *) : �̵�������ġ �׾Ƶδ� ���� (call by reference)
			  map(int[][10]) : �迭�� ������ �̷�
			  current(Point2D) : ������ġ 
	output  : (NULL) 
*/
void stackWay(LinkedStackType *s, int map[][10], Point2D current) {
	
	// ������ġ�� row��, col�� 
	int row = current.rowPos;
	int col = current.colPos;
	
	// �̵������� ��ġ�� ������ ���� 
	Point2D next;
	
	if( row + 1 < 10 && map[row + 1][col] == 0 ) {
		
		// �Ʒ������� �̵������ϸ� �Ʒ����� ��ǥ push & �ܼ���� 
		next.rowPos = row + 1;
		next.colPos = col;
		push(s, next, 1);
	}
	
	if( row - 1 > -1 && map[row - 1][col] == 0 ) {
		
		// �������� �̵������ϸ� ������ ��ǥ push & �ܼ���� 
		next.rowPos = row - 1;
		next.colPos = col;
		push(s, next, 1);
	}
	
	if( col - 1 > -1 && map[row][col - 1] == 0 ) {
		
		// �������� �̵������ϸ� ������ ��ǥ push & �ܼ���� 
		next.rowPos = row;
		next.colPos = col - 1;
		push(s, next, 1);
	}
	
	if( col + 1 < 10 && map[row][col + 1] == 0 ) {
		
		// ���������� �̵������ϸ� �������� ��ǥ push & �ܼ���� 
		next.rowPos = row;
		next.colPos = col + 1;
		push(s, next, 1);
	}
}

/*
	function: �̷ι迭�� ���Ž�������� Ž���� ��θ� ����ϴ� �Լ� 
	Note    : ���Ž�� ���������� push/pop ������ �ֿܼ� ����� �� 
	input   : s_temp(LinkedStackType) : push/pop�� �ݺ��Ǹ� ��θ� Ž���ϴ� ����
			  s_path(LinkedStackType *) : ������ ��ġ�� ���������� ����Ǵ� ���� (call by reference)
			  map(int[][10]) : �迭�� ������ �̷� 
			  start(Point2D) : ���Ž���� ������
			  finish(Point2D) : ���Ž���� ������ 
	output  : (NULL)
*/
void findPath(LinkedStackType s_temp, LinkedStackType *s_path, int map[][10], Point2D start, Point2D finish) {
	
	// ������ġ�� ���������� ���� 
	Point2D current = start;
	
	while(1) {
		
		// ������彺��(s_path)�� ������ġ�� ���� (��� X)
		push(s_path, current, 0);
		
		// ������ġ�� �������̸� Ž������ 
		if(current.colPos == finish.colPos && current.rowPos == finish.rowPos) {
			break;
		}
		
		// ������ġ�� VISITED�� ǥ�� 
		map[current.rowPos][current.colPos] = VISITED;
		
		// ������ġ���� �̵������� ��ġ�� ���Ž������(s_temp)�� ���� 
		stackWay(&s_temp, map, current);
		
		// ���Ž�����ÿ� ���������� ����� ��ġ�� pop�Ͽ� ������ġ�� ���� 
		current = pop(&s_temp, 1);
	}
}

/*
	function: ������ ��Ҹ� ��������(���� ���ΰ��� �켱����) �ֿܼ� ����ϴ� �Լ� 
	Note    : ������ LIFO�̹Ƿ�, ��������� �����Ͽ� ���� ���� ��Ұ� ���� ��µǵ��� ��
	input   : LinkedStackType�� ������ (call by reference)
	output  : (NULL)
*/
void printPath(LinkedStackType *s) {
	
	Point2D data;
	if( is_empty(s) ) {
		return;
	} else {
		data = pop(s, 0);
		printPath(s);
		printf("(row:%2d, col:%2d) -> ", data.rowPos, data.colPos);
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
	
	// �������� ���� ���� 
	Point2D start = {1, 0};
	Point2D finish = {8, 9};
	
	// ���� ���� �� �ʱ�ȭ
	// temp : ���Ž������
	// path : ������彺��
	LinkedStackType temp;
	LinkedStackType path;
	init(&temp);
	init(&path);
	
	// ��� Ž�� 
	findPath(temp, &path, maze, start, finish);
	
	// ��� ��� 
	printf("\nResult Path:\n");
	printPath(&path);
	printf("finish");
	
	// ���α׷� ���� 
	return 0;
}
