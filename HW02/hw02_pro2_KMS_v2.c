#include <stdio.h>
#include <stdlib.h>
#define VISITED 2					// �湮�� ������ VISITED�� ����
#define BACKTRACKED 3				// ��� �����ε� �� �̻� ���ư� ���� ���ٸ� �� ������ BACKTRACKED�� ����(�ٽ� ���ư��� �ϹǷ�)


typedef struct Point2D {				// 2���� �迭 ���� X,Y �·� ����
	int xpos;
	int ypos;
}Point;

typedef struct Stack {
	Point p;
	struct Stack * link;
}StackNode;

typedef struct StackType {
	StackNode * top;
}StackType;

void init(StackType * s) {
	s->top = NULL;
}

int is_empty(StackType * s) {
	return s->top == NULL;
}

void push(StackType * s, int xpos, int ypos) {
	StackNode * new_node = (StackNode*)malloc(sizeof(StackNode));
	if (new_node == NULL) { fprintf(stderr, "error!");return; }
	else {
		new_node->p.xpos = xpos;
		new_node->p.ypos = ypos;
		new_node->link = s->top;
		s->top = new_node;
	}
}

Point pop(StackType * s) {
	if (!is_empty(s)) {
		StackNode * removed = s->top;
		Point tmp;
		tmp.xpos = removed->p.xpos;
		tmp.ypos = removed->p.ypos;
		s->top = s->top->link;
		free(removed);
		return tmp;
	}
}


int is_right(int maze[][10], int xpos, int ypos, StackType * s) {									// ��ġ Ž�� ������ �Ǵ��ϴ� �Լ�1
	if (xpos < 0 || ypos < 0 || xpos>9 || ypos>9) { return 0; }
	if (maze[xpos][ypos] != 1 && maze[xpos][ypos] != VISITED&&maze[xpos][ypos] != BACKTRACKED) {
		return 1;
	}
	return 0;
}


void find_path(int maze[][10], StackType * s) {					// ���� 2���� B���ǿ� �´� �̷� ����ϱ� ���� �Լ�
	int switch_on[4] = { 0,0,0,0 };								// �Ʒ�,��,����,������ ������� �̷� Ž�� �� ���ǿ� ������ �� switch_on�ϱ� ���� �迭 ����
	Point p; p.xpos = 1, p.ypos = 0;
	int x = 1, y = 0, state = 0;
	StackType finalStack;init(&finalStack);
	while (1) {
		p = pop(s);												// �̷� Ž�� ��, ������ ������ ��ǥ�� push�ϱ� �� ���� ��ġ�� ���� pop���־�� ��
		x = p.xpos;y = p.ypos;state = 0;
		printf("pop : (%d,%d)\n", x, y);						// �� ��ġ ���
		push(&finalStack, x, y);
		for (int i = 0;i < 4;i++) { switch_on[i] = 0; }
		if (p.xpos == 8 && p.ypos == 9) break;					// �ݺ����� ���� ����. (8,9)�� �����Ͽ����� Ż��.
		maze[x][y] = VISITED;									// pop�� ���� ��ġ�� VISITED�� ����.

		if (is_right(maze, x + 1, y, s)) { state++; switch_on[0] = 1; }		//�Ʒ�
		if (is_right(maze, x - 1, y, s)) { state++; switch_on[1] = 1; }		//��
		if (is_right(maze, x, y - 1, s)) { state++; switch_on[2] = 1; }		//����
		if (is_right(maze, x, y + 1, s)) { state++; switch_on[3] = 1; }		//������


		if (state > 0) {
			if (switch_on[0] == 1) { push(s, x + 1, y);printf("push : (%d,%d)\n", x + 1, y); maze[x + 1][y] = VISITED; }
			if (switch_on[1] == 1) { push(s, x - 1, y);printf("push : (%d,%d)\n", x - 1, y); maze[x - 1][y] = VISITED; }
			if (switch_on[2] == 1) { push(s, x, y - 1);printf("push : (%d,%d)\n", x, y - 1); maze[x][y - 1] = VISITED; }
			if (switch_on[3] == 1) { push(s, x, y + 1);printf("push : (%d,%d)\n", x, y + 1); maze[x][y + 1] = VISITED; }
			/*����� ��ȿ������ �ڵ带 § �� �˼��մϴ� �Ф� ���⼭ �� ��� ���� VISITED�� �̸� �������� ������ ��� Ž�� ��
			���� ��ǥ�� 2�� push�ϴ� ���� �����ϱ� �����Դϴ�. ���� ���� VISITED�� �̸� ���� �����ָ� (2,2)�� �� �� push�˴ϴ�.*/
		}
		else { maze[x][y] = BACKTRACKED; }			// ��� �������ε� Ž�� �Ұ����ϸ� �ٽ� �ǵ��ư��� �ϹǷ� �� ��ġ�� BACKTRACKED�� ����
	}

	printf("\n\n�Ա��������� �ⱸ������ ��� :\n");
	StackType copy;init(&copy);
	StackNode * tmp = (&finalStack)->top;
	while (tmp != NULL) {
		push(&copy, tmp->p.xpos, tmp->p.ypos);
		tmp = tmp->link;
	}

	tmp = (&copy)->top;
	while (tmp != NULL) {
		printf("(%d,%d)\n", tmp->p.xpos, tmp->p.ypos);
		tmp = tmp->link;
	}

}



int main() {
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

	StackType s;
	init(&s);
	push(&s, 1, 0);
	find_path(maze, &s);
}