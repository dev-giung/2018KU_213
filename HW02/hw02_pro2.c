#include <stdio.h>
#include <stdlib.h>

#define VISITED 2 // 방문한 지점은 VISITED로 표시

/*
	Def : Point2D 구조체 정의
	Note: 2차원 배열 상의 row, col 좌표를 나타냄 
*/
typedef struct Point2D {
	
	// row index 
	int rowPos;
	
	// col index
	int colPos;
} Point2D;

/*
	Def : StackNode 구조체 정의
	Note: Point2D 형 아이템을 가진 스택노드를 나타냄 
*/
typedef struct StackNode {
	
	// Data Field
	Point2D item;
	
	// Link Field
	struct StackNode *link;
} StackNode;

/*
	Def : LinkedStackType 구조체 정의
	Note: 스택노드들이 쌓인 스택을 나타냄
*/
typedef struct LinkedStackType {
	
	// 최상단의 스택노드를 가리키는 포인터 
	StackNode *top;
} LinkedStackType;

/*
	function: 스택을 초기화 
	Note	: 스택의 top 포인터가 NULL을 가리키게 함 
	input	: LinkedStackType형 포인터 (call by reference) 
	output	: (NULL)
*/
void init(LinkedStackType *s) {
	
	s -> top = NULL;
}

/*
	fuction: 스택이 비어있는지 확인
	Note   : 비어있으면 1을 반환 
	input  : LinkedStackType형 포인터 (call by reference) 
	output : int 
*/
int is_empty(LinkedStackType *s) {
	
	return (s -> top == NULL);
}

/*
	function: 스택의 push 함수 
	Note    : 스택에 새로운 스택노드를 push 및 콘솔출력(선택사항)
	input   : s(LinkedStackType *) : 스택노드가 쌓일 스택 (call by reference)
			  item(Point2D) : 삽입될 스택노드의 내부변수
			  n(int) : push 과정의 콘솔출력여부 결정
	output  : (NULL)
*/
void push(LinkedStackType *s, Point2D item, int n) {
	
	// 새로운 스택노드 메모리 할당
	StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
	
	if(new_node == NULL) {
		
		// 메모리 할당에러 체크 
		printf("메모리 할당에러\n");
		return;
	} else {
		
		// 새로운 스택노드 내부변수 입력 
		new_node -> item = item;
		new_node -> link = s -> top;
		
		// 새로운 스택노드를 스택에 쌓음 
		s -> top = new_node;
		
		// n이 1이면 push 과정 콘솔출력 
		if(n) {
			printf("push (row:%2d, col:%2d)\n", item.rowPos, item.colPos);
		}
	}
}

/*
	function: 스택의 pop 함수 
	Note    : 스택 최상단의 스택노드를 pop 및 콘솔출력(선택사항) 
	input   : s(LinkedStackType *) : 스택노드가 쌓인 스택 (call by reference)
			  n(int) : pop 과정의 콘솔출력여부 결정 
	output  : Point
*/
Point2D pop(LinkedStackType *s, int n) {
	
	if( is_empty(s) ) {
		
		// 빈 스택은 pop할 수 없음 
		printf("스택이 비어있음\n");
		exit(1);
	} else {
		
		// 스택 최상단의 노드가 pop의 대상 
		StackNode *removed_node = s -> top;
		
		// 대상노드의 내부변수 item에 저장 
		Point2D item = removed_node -> item;
		
		// 대상노드 스택에서 삭제 
		s -> top = s -> top -> link;
		free(removed_node);
		
		// n이 1이면 pop 과정 콘솔출력 
		if(n) {
			printf(" pop (row:%2d, col:%2d)\n", item.rowPos, item.colPos);
		}
		
		// 대상노드가 갖고있던 내부변수 반환 
		return item;
	}
}

/*
	function: 현재위치와 인접하고 이동가능한 위치를 스택에 push하는 함수 
	Note    : 이동가능성은 해당 위치의 저장값(0인 경우에만 이동 가능)과 index 값의 유효성으로 판별 
	input   : s(LinkedStackType *) : 이동가능위치 쌓아두는 스택 (call by reference)
			  map(int[][10]) : 배열로 구성된 미로
			  current(Point2D) : 현재위치 
	output  : (NULL) 
*/
void stackWay(LinkedStackType *s, int map[][10], Point2D current) {
	
	// 현재위치의 row값, col값 
	int row = current.rowPos;
	int col = current.colPos;
	
	// 이동가능한 위치를 저장할 변수 
	Point2D next;
	
	if( row + 1 < 10 && map[row + 1][col] == 0 ) {
		
		// 아래쪽으로 이동가능하면 아래쪽의 좌표 push & 콘솔출력 
		next.rowPos = row + 1;
		next.colPos = col;
		push(s, next, 1);
	}
	
	if( row - 1 > -1 && map[row - 1][col] == 0 ) {
		
		// 위쪽으로 이동가능하면 위쪽의 좌표 push & 콘솔출력 
		next.rowPos = row - 1;
		next.colPos = col;
		push(s, next, 1);
	}
	
	if( col - 1 > -1 && map[row][col - 1] == 0 ) {
		
		// 왼쪽으로 이동가능하면 왼쪽의 좌표 push & 콘솔출력 
		next.rowPos = row;
		next.colPos = col - 1;
		push(s, next, 1);
	}
	
	if( col + 1 < 10 && map[row][col + 1] == 0 ) {
		
		// 오른쪽으로 이동가능하면 오른쪽의 좌표 push & 콘솔출력 
		next.rowPos = row;
		next.colPos = col + 1;
		push(s, next, 1);
	}
}

/*
	function: 미로배열의 경로탐색과정과 탐색한 경로를 출력하는 함수 
	Note    : 경로탐색 과정에서의 push/pop 과정을 콘솔에 출력함 로 
	input   : s_temp(LinkedStackType) : push/pop이 반복되며 경로를 탐색하는 스택
			  s_path(LinkedStackType *) : 지나온 위치가 순차적으로 저장되는 스택 (call by reference)
			  map(int[][10]) : 배열로 구성된 미로 
			  start(Point2D) : 경로탐색의 시작점
			  finish(Point2D) : 경로탐색의 도착점 
	output  : (NULL)
*/
void findPath(LinkedStackType s_temp, LinkedStackType *s_path, int map[][10], Point2D start, Point2D finish) {
	
	// 현재위치를 시작점으로 지정 
	Point2D current = start;
	
	while(1) {
		
		// 경로저장스택(s_path)에 현재위치를 저장 (출력 X)
		push(s_path, current, 0);
		
		// 현재위치가 도착점이면 탐색종료 
		if(current.colPos == finish.colPos && current.rowPos == finish.rowPos) {
			break;
		}
		
		// 현재위치를 VISITED로 표시 
		map[current.rowPos][current.colPos] = VISITED;
		
		// 현재위치에서 이동가능한 위치를 경로탐색스택(s_temp)에 저장 
		stackWay(&s_temp, map, current);
		
		// 경로탐색스택에 마지막으로 저장된 위치를 pop하여 현재위치에 저장 
		current = pop(&s_temp, 1);
	}
}

/*
	function: 스택의 요소를 역순으로(먼저 쌓인것을 우선으로) 콘솔에 출력하는 함수 
	Note    : 스택은 LIFO이므로, 재귀적으로 구성하여 먼저 쌓인 요소가 먼저 출력되도록 함
	input   : LinkedStackType형 포인터 (call by reference)
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
	
	// 시작점과 끝점 지정 
	Point2D start = {1, 0};
	Point2D finish = {8, 9};
	
	// 스택 선언 및 초기화
	// temp : 경로탐색스택
	// path : 경로저장스택
	LinkedStackType temp;
	LinkedStackType path;
	init(&temp);
	init(&path);
	
	// 경로 탐색 
	findPath(temp, &path, maze, start, finish);
	
	// 경로 출력 
	printf("\nResult Path:\n");
	printPath(&path);
	printf("finish");
	
	// 프로그램 종료 
	return 0;
}
