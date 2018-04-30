#include <stdio.h>
#include <stdlib.h>
#define VISITED 2					// 방문한 지점에 VISITED로 설정
#define BACKTRACKED 3				// 어느 곳으로도 더 이상 나아갈 곳이 없다면 그 지점엔 BACKTRACKED로 설정(다시 돌아가야 하므로)


typedef struct Point2D {				// 2차원 배열 상의 X,Y 좌로 설정
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


int is_right(int maze[][10], int xpos, int ypos, StackType * s) {									// 위치 탐색 적절성 판단하는 함수1
	if (xpos < 0 || ypos < 0 || xpos>9 || ypos>9) { return 0; }
	if (maze[xpos][ypos] != 1 && maze[xpos][ypos] != VISITED&&maze[xpos][ypos] != BACKTRACKED) {
		return 1;
	}
	return 0;
}


void find_path(int maze[][10], StackType * s) {					// 문제 2번의 B조건에 맞는 미로 출력하기 위한 함수
	int switch_on[4] = { 0,0,0,0 };								// 아래,위,왼쪽,오른쪽 순서대로 미로 탐색 시 조건에 부합할 때 switch_on하기 위한 배열 선언
	Point p; p.xpos = 1, p.ypos = 0;
	int x = 1, y = 0, state = 0;
	StackType finalStack;init(&finalStack);
	while (1) {
		p = pop(s);												// 미로 탐색 시, 가능한 방향의 좌표를 push하기 전 현재 위치를 먼저 pop해주어야 함
		x = p.xpos;y = p.ypos;state = 0;
		printf("pop : (%d,%d)\n", x, y);						// 현 위치 출력
		push(&finalStack, x, y);
		for (int i = 0;i < 4;i++) { switch_on[i] = 0; }
		if (p.xpos == 8 && p.ypos == 9) break;					// 반복문의 종료 조건. (8,9)에 도달하였으면 탈출.
		maze[x][y] = VISITED;									// pop한 현재 위치를 VISITED로 설정.

		if (is_right(maze, x + 1, y, s)) { state++; switch_on[0] = 1; }		//아래
		if (is_right(maze, x - 1, y, s)) { state++; switch_on[1] = 1; }		//위
		if (is_right(maze, x, y - 1, s)) { state++; switch_on[2] = 1; }		//왼쪽
		if (is_right(maze, x, y + 1, s)) { state++; switch_on[3] = 1; }		//오른쪽


		if (state > 0) {
			if (switch_on[0] == 1) { push(s, x + 1, y);printf("push : (%d,%d)\n", x + 1, y); maze[x + 1][y] = VISITED; }
			if (switch_on[1] == 1) { push(s, x - 1, y);printf("push : (%d,%d)\n", x - 1, y); maze[x - 1][y] = VISITED; }
			if (switch_on[2] == 1) { push(s, x, y - 1);printf("push : (%d,%d)\n", x, y - 1); maze[x][y - 1] = VISITED; }
			if (switch_on[3] == 1) { push(s, x, y + 1);printf("push : (%d,%d)\n", x, y + 1); maze[x][y + 1] = VISITED; }
			/*상당히 비효율적인 코드를 짠 점 죄송합니다 ㅠㅠ 여기서 각 경우 마다 VISITED를 미리 설정해준 이유는 경로 탐색 시
			같은 좌표를 2번 push하는 것을 방지하기 위함입니다. 만약 위의 VISITED를 미리 설정 안해주면 (2,2)가 두 번 push됩니다.*/
		}
		else { maze[x][y] = BACKTRACKED; }			// 어느 방향으로도 탐색 불가능하면 다시 되돌아가야 하므로 현 위치를 BACKTRACKED로 설정
	}

	printf("\n\n입구에서부터 출구까지의 경로 :\n");
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