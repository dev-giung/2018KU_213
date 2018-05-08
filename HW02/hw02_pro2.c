#include <stdio.h>
#include <stdlib.h>
#define VISITED 2					// 방문한 지점에 VISITED로 설정
#define BACKTRACKED 3				// 어느 곳으로도 더 이상 나아갈 곳이 없다면 그 지점엔 BACKTRACKED로 설정(다시 돌아가야 하므로)
#define WAITING 4					// 상하좌우 탐색 시 나아갈 위치가 존재한다면 그 지점에 도달하기 전 미리 WAITING으로 표시

typedef struct Point2D {				// 2차원 배열 상의 X,Y 좌표 설정
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

void push(StackType * s, int xpos, int ypos) {									// 스택의 push 함수. 매개변수로 전달된 xpos와 ypos는 2차원 좌표를 저장할 스택의 특성 상 각각 x좌표 y좌표를 의미
	StackNode * new_node = (StackNode*)malloc(sizeof(StackNode));
	if (new_node == NULL) { fprintf(stderr, "error!");return; }
	else {
		new_node->p.xpos = xpos;
		new_node->p.ypos = ypos;
		new_node->link = s->top;
		s->top = new_node;
	}
}

Point pop(StackType * s) {														// 스택의 pop 함수. 스택의 가장 앞 노드를 제거 후, 반환.
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


int is_right(int maze[][10], int xpos, int ypos, StackType * s) {									// 위치 탐색시 적절성 판단하는 함수
	if (xpos < 0 || ypos < 0 || xpos>9 || ypos>9) { return 0; }										// 위치가 배열의 범위를 넘어서면 0을 반환
	if (maze[xpos][ypos]==0||maze[xpos][ypos]==WAITING) {											// 위치가 1이거나 VISITED 및 BACKTRACKED 어느 것도 아닌 0 혹은 WAITING 일 때에만 1을 반환
		return 1;
	}
	return 0;
}


void find_path(int maze[][10], StackType * s) {					// 미로의 경로를 탐색 및 출력하기 위한 함수
	int switch_on[4] = { 0,0,0,0 };								// 아래,위,왼쪽,오른쪽 순서대로 미로 탐색 시 조건에 부합할 때 switch_on하기 위한 배열 선언
	Point p; p.xpos = 1, p.ypos = 0;							// 구조체 변수 p는 미로 탐색 시 현 위치를 저장하기 위한 변수
	int x = 1, y = 0, state = 0;								// 변수 x, y는 위의 구조체 변수 p의 x좌표, y좌표를 의미하고 변수 state는 미로탐색 시 상,하,좌,우 각각이 도달가능한 곳인지를 나타내기 위한 변수
	StackType finalStack;init(&finalStack);						// finalStack은 이후 미로의 최종경로 출력에 이용될 스택
	while (1) {
		p = pop(s);												// 미로 탐색 시, 가능한 방향의 좌표를 push하기 전 현재 위치를 먼저 pop해주어야 함. 그 후 현 위치를 p에 저장
		x = p.xpos;y = p.ypos;state = 0;						// p의 x,y 좌표를 변수 x,y에 저장. 매 이동마다 state는 0으로 초기화.
		printf("pop : (%d,%d)\n", x, y);						// 현 위치 출력
		push(&finalStack, x, y);								// pop한 좌표들을 finalStack에 push. 미로의 최종 경로 출력 시 방문한 곳, 즉 pop한 좌표들을 
		for (int i = 0;i < 4;i++) { switch_on[i] = 0; }			// 매 이동마다(반복마다) switch_on 배열의 각 요소는 0으로 초기화.
		if (p.xpos == 8 && p.ypos == 9) break;					// 반복문의 종료 조건. (8,9)에 도달하였으면 탈출.
		maze[x][y] = VISITED;									// pop한 현재 위치를 VISITED로 설정.

		if (is_right(maze, x + 1, y, s)) { state++; switch_on[0] = 1; }		//아래
		if (is_right(maze, x - 1, y, s)) { state++; switch_on[1] = 1; }		//위
		if (is_right(maze, x, y - 1, s)) { state++; switch_on[2] = 1; }		//왼쪽
		if (is_right(maze, x, y + 1, s)) { state++; switch_on[3] = 1; }		//오른쪽


		if (state > 0) {
			if (switch_on[0] == 1) { if (maze[x + 1][y] != WAITING) { push(s, x + 1, y);printf("push : (%d,%d)\n", x + 1, y); } maze[x + 1][y] = WAITING; }
			if (switch_on[1] == 1) { if (maze[x - 1][y] != WAITING) { push(s, x - 1, y);printf("push : (%d,%d)\n", x - 1, y); } maze[x - 1][y] = WAITING; }
			if (switch_on[2] == 1) { if(maze[x][y - 1] != WAITING){ push(s, x, y - 1);printf("push : (%d,%d)\n", x, y - 1); } maze[x][y - 1] = WAITING;	}
			if (switch_on[3] == 1) { if (maze[x][y + 1] != WAITING) { push(s, x, y + 1);printf("push : (%d,%d)\n", x, y + 1); } maze[x][y + 1] = WAITING; }
			/*각 경우 마다 WAITING 조건을 설정해준 이유는 경로 탐색 시
			같은 좌표를 2번 push하는 것을 방지하기 위함입니다.*/
		}
		else { maze[x][y] = BACKTRACKED; }			// 어느 방향으로도 탐색 불가능하면 다시 되돌아가야 하므로 현 위치를 BACKTRACKED로 설정
	}

	StackType copy;init(&copy);						// copy는 finalStack에 쌓인 좌표들을 역순으로 저장할 스택.
	StackNode * tmp = (&finalStack)->top;			
	while (tmp != NULL) {
		push(&copy, tmp->p.xpos, tmp->p.ypos);		// finalStack의 꼭대기부터 차례로 copy에 push
		tmp = tmp->link;
	}

	tmp = (&copy)->top;								// 노드 포인터 tmp를 copy의 꼭대기 노드, 맨 앞을 가리키도록 설정. 이 때 tmp가 가리키는 노드는 (1,0)이 될 것임
	while (tmp->link != NULL) {						// 마지막 노드에 도달할 때까지 반복. 마지막 노드에 도달 시 종료
		printf("(%d, %d) -> ", tmp->p.xpos, tmp->p.ypos);
		tmp = tmp->link;
	}

	printf("(%d, %d)\n", tmp->p.xpos, tmp->p.ypos);		// 마지막 좌표 (8,9) 출력

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

	StackType s;				// 미로의 경로 탐색에 이용될 스택. 현 위치를 pop 및 도달 가능한 곳의 좌표들을 수시로 push 하면서 경로를 찾아갈 때 이용될 메인 스택.
	init(&s);					// 스택의 초기화
	push(&s, 1, 0);				// 시작점 (1,0)부터 push
	find_path(maze, &s);		// 경로 탐색 및 출력
}