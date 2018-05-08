#include <stdio.h>
#include <stdlib.h>
#define VISITED 2					// �湮�� ������ VISITED�� ����
#define BACKTRACKED 3				// ��� �����ε� �� �̻� ���ư� ���� ���ٸ� �� ������ BACKTRACKED�� ����(�ٽ� ���ư��� �ϹǷ�)
#define WAITING 4					// �����¿� Ž�� �� ���ư� ��ġ�� �����Ѵٸ� �� ������ �����ϱ� �� �̸� WAITING���� ǥ��

typedef struct Point2D {				// 2���� �迭 ���� X,Y ��ǥ ����
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

void push(StackType * s, int xpos, int ypos) {									// ������ push �Լ�. �Ű������� ���޵� xpos�� ypos�� 2���� ��ǥ�� ������ ������ Ư�� �� ���� x��ǥ y��ǥ�� �ǹ�
	StackNode * new_node = (StackNode*)malloc(sizeof(StackNode));
	if (new_node == NULL) { fprintf(stderr, "error!");return; }
	else {
		new_node->p.xpos = xpos;
		new_node->p.ypos = ypos;
		new_node->link = s->top;
		s->top = new_node;
	}
}

Point pop(StackType * s) {														// ������ pop �Լ�. ������ ���� �� ��带 ���� ��, ��ȯ.
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


int is_right(int maze[][10], int xpos, int ypos, StackType * s) {									// ��ġ Ž���� ������ �Ǵ��ϴ� �Լ�
	if (xpos < 0 || ypos < 0 || xpos>9 || ypos>9) { return 0; }										// ��ġ�� �迭�� ������ �Ѿ�� 0�� ��ȯ
	if (maze[xpos][ypos]==0||maze[xpos][ypos]==WAITING) {											// ��ġ�� 1�̰ų� VISITED �� BACKTRACKED ��� �͵� �ƴ� 0 Ȥ�� WAITING �� ������ 1�� ��ȯ
		return 1;
	}
	return 0;
}


void find_path(int maze[][10], StackType * s) {					// �̷��� ��θ� Ž�� �� ����ϱ� ���� �Լ�
	int switch_on[4] = { 0,0,0,0 };								// �Ʒ�,��,����,������ ������� �̷� Ž�� �� ���ǿ� ������ �� switch_on�ϱ� ���� �迭 ����
	Point p; p.xpos = 1, p.ypos = 0;							// ����ü ���� p�� �̷� Ž�� �� �� ��ġ�� �����ϱ� ���� ����
	int x = 1, y = 0, state = 0;								// ���� x, y�� ���� ����ü ���� p�� x��ǥ, y��ǥ�� �ǹ��ϰ� ���� state�� �̷�Ž�� �� ��,��,��,�� ������ ���ް����� �������� ��Ÿ���� ���� ����
	StackType finalStack;init(&finalStack);						// finalStack�� ���� �̷��� ������� ��¿� �̿�� ����
	while (1) {
		p = pop(s);												// �̷� Ž�� ��, ������ ������ ��ǥ�� push�ϱ� �� ���� ��ġ�� ���� pop���־�� ��. �� �� �� ��ġ�� p�� ����
		x = p.xpos;y = p.ypos;state = 0;						// p�� x,y ��ǥ�� ���� x,y�� ����. �� �̵����� state�� 0���� �ʱ�ȭ.
		printf("pop : (%d,%d)\n", x, y);						// �� ��ġ ���
		push(&finalStack, x, y);								// pop�� ��ǥ���� finalStack�� push. �̷��� ���� ��� ��� �� �湮�� ��, �� pop�� ��ǥ���� 
		for (int i = 0;i < 4;i++) { switch_on[i] = 0; }			// �� �̵�����(�ݺ�����) switch_on �迭�� �� ��Ҵ� 0���� �ʱ�ȭ.
		if (p.xpos == 8 && p.ypos == 9) break;					// �ݺ����� ���� ����. (8,9)�� �����Ͽ����� Ż��.
		maze[x][y] = VISITED;									// pop�� ���� ��ġ�� VISITED�� ����.

		if (is_right(maze, x + 1, y, s)) { state++; switch_on[0] = 1; }		//�Ʒ�
		if (is_right(maze, x - 1, y, s)) { state++; switch_on[1] = 1; }		//��
		if (is_right(maze, x, y - 1, s)) { state++; switch_on[2] = 1; }		//����
		if (is_right(maze, x, y + 1, s)) { state++; switch_on[3] = 1; }		//������


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

	StackType s;				// �̷��� ��� Ž���� �̿�� ����. �� ��ġ�� pop �� ���� ������ ���� ��ǥ���� ���÷� push �ϸ鼭 ��θ� ã�ư� �� �̿�� ���� ����.
	init(&s);					// ������ �ʱ�ȭ
	push(&s, 1, 0);				// ������ (1,0)���� push
	find_path(maze, &s);		// ��� Ž�� �� ���
}