#include <stdio.h>
#include <stdlib.h>

/*
	VISITED    : �湮�� ����
	BACKTRACKED: �� �̻� �� ���� ���� ���� 
	WAITING    : �� ���� ���� ����
*/
#define VISITED 2
#define BACKTRACKED 3
#define WAITING 4

/*
	Def : Point2D ����ü ����
	Note: 2���� �迭 ���� x, y ��ǥ�� ��Ÿ�� 
*/
typedef struct Point2D {
	
	int xpos;
	int ypos;
} Point;

/*
	Def : StackNode ����ü ����
	Note: ���ó�带 ��Ÿ�� 
*/
typedef struct StackNode {
	
	// Data Field: Point2D
	Point p;
	
	// Link Field
	struct Stack *link;
} StackNode;

/*
	Def : StackType ����ü ����
	Note: ���ó����� ���� ������ ��Ÿ��
*/
typedef struct StackType {
	
	// top �����ʹ� �������� ���� ���ó�带 ����Ŵ 
	StackNode *top;
} StackType;

/*
	function: ������ �ʱ�ȭ 
	Note	: ������ top �����Ͱ� NULL�� ����Ű�� �� 
	input	: StackType�� ������ (call by reference) 
	output	: (NULL)
*/
void init(StackType *s) {
	
	s->top = NULL;
}

/*
	fuction: ������ ����ִ��� Ȯ��
	Note   : ��������� 1�� ��ȯ
	input  : StackType�� ������ (call by reference) 
	output : int 
*/
int is_empty(StackType *s) {
	
	return ( s->top == NULL );
}

/*
	function: ������ push �Լ� 
	Note    : ���ÿ� ���ο� ���ó�带 push�� 
	input   : s(StackType *) : ���ó�尡 ���Ե� ���� (call by reference)
			  xpos(int) : ���Ե� ���ó���� ���κ��� 
			  ypos(int) : ���Ե� ���ó���� ���κ���
	output  : (NULL)
*/
void push(StackType *s, int xpos, int ypos) {
	
	// ���ο� ���ó�� �޸� �Ҵ� 
	StackNode *new_node = (StackNode*)malloc(sizeof(StackNode));
	
	if (new_node == NULL) {
		
		// �޸� �Ҵ��� ����� �Ǿ����� Ȯ�� 
		fprintf(stderr, "error!");
		return;
	} else {
		
		// ���ο� ���ó�� ���κ��� �Է� 
		new_node->p.xpos = xpos;
		new_node->p.ypos = ypos;
		new_node->link = s->top;
		
		// ���ο� ���ó�带 ���ÿ� ���� 
		s->top = new_node;
	}
}

/*
	function: ������ pop �Լ� 
	Note    : ���ÿ� ���������� ���� ���ó�带 pop��
	input   : StackType�� ������ (call by reference) 
	output  : Point
*/
Point pop(StackType * s) {
	
	if ( !(is_empty(s)) ) {
		
		// removed ������ ������ �ֻ�ܿ� ��ġ�� ��� ����Ŵ 
		StackNode *removed = s->top;
		
		// tmp(Point)�� ������� ���κ��� ���� 
		Point tmp;
		tmp.xpos = removed->p.xpos;
		tmp.ypos = removed->p.ypos;
		
		// ����� ���ÿ��� ���� 
		s->top = s->top->link;
		free(removed);
		
		// tmp(����尡 �����ִ� Point ��) ��ȯ 
		return tmp;
	}
}

/*
	function: ��� Ž���� ��ġ�� ������ �Ǵ��ϴ� �Լ�
	Note    : 
	input   : maze(int[][10]) : �迭�� ������ �̷� 
			  xpos(int) : �̷ο����� x��ǥ 
			  ypos(int) : �̷ο����� y��ǥ 
	output  : int
*/
int is_right(int maze[][10], int xpos, int ypos) {
	
	if ( xpos < 0 || ypos < 0 || xpos > 9 || ypos > 9 ) {
		
		// �����ġ�� �迭�� index�� �Ѿ�� 0�� ��ȯ 
		return 0;
	}
	
	if ( maze[xpos][ypos] == 0 || maze[xpos][ypos] == WAITING ) {
		
		// �����ġ�� ��ȿ�ϸ�(0�̰ų� WAITING�̸�) 1�� ��ȯ 
		return 1;
	}
	
	// �����ġ�� ��ȿ���� ������(1�̰ų� VISITED�ų� BACKTRACKED�̸�) 0�� ��ȯ 
	return 0;
}

/*
	function: �̷��� ��θ� Ž�� �� ����ϴ� �Լ� 
	Note    : Ž�� ������ �Ʒ�, ��, ����, �������� 
	input   : maze(int[][10]) : �迭�� ������ �̷�
			  s(StackType *) : ��ġ����(���)�� ���̴� ���� 
	output  : (NULL)
*/
void find_path(int maze[][10], StackType * s) {
	
	// Ž�� ������ ��ȿ���� ��Ÿ���� ����
	// [0]: ��, [1]: ��, [2]: ��, [3]: �� 
	int switch_on[4] = { 0 };
	
	// ����ġ�� ��Ÿ���� Point ����
	// ������ (1, 0)���� �ʱ�ȭ 
	Point p;
	p.xpos = 1, p.ypos = 0;
	
	int x = 1, y = 0, state = 0;								// ���� x, y�� ���� ����ü ���� p�� x��ǥ, y��ǥ�� �ǹ��ϰ� ���� state�� �̷�Ž�� �� ��,��,��,�� ������ ���ް����� �������� ��Ÿ���� ���� ����
	
	StackType finalStack;
	
	init(&finalStack);						// finalStack�� ���� �̷��� ������� ��¿� �̿�� ����
	while (1) {
		p = pop(s);												// �̷� Ž�� ��, ������ ������ ��ǥ�� push�ϱ� �� ���� ��ġ�� ���� pop���־�� ��. �� �� �� ��ġ�� p�� ����
		x = p.xpos;y = p.ypos;state = 0;						// p�� x,y ��ǥ�� ���� x,y�� ����. �� �̵����� state�� 0���� �ʱ�ȭ.
		printf("pop : (%d,%d)\n", x, y);						// �� ��ġ ���
		push(&finalStack, x, y);								// pop�� ��ǥ���� finalStack�� push. �̷��� ���� ��� ��� �� �湮�� ��, �� pop�� ��ǥ���� 
		int i;
		for (i = 0;i < 4;i++) { switch_on[i] = 0; }			// �� �̵�����(�ݺ�����) switch_on �迭�� �� ��Ҵ� 0���� �ʱ�ȭ.
		if (p.xpos == 8 && p.ypos == 9) break;					// �ݺ����� ���� ����. (8,9)�� �����Ͽ����� Ż��.
		maze[x][y] = VISITED;									// pop�� ���� ��ġ�� VISITED�� ����.

		if (is_right(maze, x + 1, y)) { state++; switch_on[0] = 1; }		//�Ʒ�
		if (is_right(maze, x - 1, y)) { state++; switch_on[1] = 1; }		//��
		if (is_right(maze, x, y - 1)) { state++; switch_on[2] = 1; }		//����
		if (is_right(maze, x, y + 1)) { state++; switch_on[3] = 1; }		//������


		if (state > 0) {
			if (switch_on[0] == 1) { if (maze[x + 1][y] != WAITING) { push(s, x + 1, y);printf("push : (%d,%d)\n", x + 1, y); } maze[x + 1][y] = WAITING; }
			if (switch_on[1] == 1) { if (maze[x - 1][y] != WAITING) { push(s, x - 1, y);printf("push : (%d,%d)\n", x - 1, y); } maze[x - 1][y] = WAITING; }
			if (switch_on[2] == 1) { if(maze[x][y - 1] != WAITING){ push(s, x, y - 1);printf("push : (%d,%d)\n", x, y - 1); } maze[x][y - 1] = WAITING;	}
			if (switch_on[3] == 1) { if (maze[x][y + 1] != WAITING) { push(s, x, y + 1);printf("push : (%d,%d)\n", x, y + 1); } maze[x][y + 1] = WAITING; }
			/*�� ��� ���� WAITING ������ �������� ������ ��� Ž�� ��
			���� ��ǥ�� 2�� push�ϴ� ���� �����ϱ� �����Դϴ�.*/
		}
		else { maze[x][y] = BACKTRACKED; }			// ��� �������ε� Ž�� �Ұ����ϸ� �ٽ� �ǵ��ư��� �ϹǷ� �� ��ġ�� BACKTRACKED�� ����
	}

	StackType copy;init(&copy);						// copy�� finalStack�� ���� ��ǥ���� �������� ������ ����.
	StackNode * tmp = (&finalStack)->top;			
	while (tmp != NULL) {
		push(&copy, tmp->p.xpos, tmp->p.ypos);		// finalStack�� �������� ���ʷ� copy�� push
		tmp = tmp->link;
	}

	tmp = (&copy)->top;								// ��� ������ tmp�� copy�� ����� ���, �� ���� ����Ű���� ����. �� �� tmp�� ����Ű�� ���� (1,0)�� �� ����
	while (tmp->link != NULL) {						// ������ ��忡 ������ ������ �ݺ�. ������ ��忡 ���� �� ����
		printf("(%d, %d) -> ", tmp->p.xpos, tmp->p.ypos);
		tmp = tmp->link;
	}

	printf("(%d, %d)\n", tmp->p.xpos, tmp->p.ypos);		// ������ ��ǥ (8,9) ���

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
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 0,0,0,0,1,0,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,1 },
		{ 1,0,1,1,1,0,0,1,0,1 },
		{ 1,0,0,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,1,0,0,1,0,1 },
		{ 1,0,1,0,0,0,0,1,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	};
	
	// �̷��� ��� Ž���� ���� ���� ���� 
	StackType s;
	
	// ���� �ʱ�ȭ 
	init(&s);
	
	// ������ (1, 0) push ��,
	push(&s, 1, 0);
	
	// ��� Ž�� �� ��� 
	find_path(maze, &s);
}
