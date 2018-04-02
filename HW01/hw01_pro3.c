#include <stdio.h>

/*
	function: 배열의 값을 출력.
	input	: int 형 배열 포인터 (call by reference)
	output	: (Null)
*/
void printArray(int arr[][10]) {
	
	// 콘솔 화면 출력 
	int i, j;
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n"); // Row 줄바꿈 
	}
	printf("\n");
}

/*
	function: 시작좌표를 기준으로 인접한 0을 모두 재귀적으로 1로 변경. 
			  상하좌우의 0을 찾아 재귀 호출하며, 인접한 0이 없을 경우에 재귀가 종료됨.
	note	: Out of Memory의 우려가 있으나 현재 프로그램에서는 고려하지 않음.
	input	: arr(int [][10]) : 데이터가 입력된 2차원배열 (call by reference)
			  row(int) : 시작점의 Row 번호 
			  col(int) : 시작점의 Column 번호 
	output	: (Null) 
*/
void makeOne(int arr[][10], int row, int col) {
	
	// 배열의 index를 벗어나는 경우 종료 
	if(row > 9 || col > 9 || row < 0 || col < 0) {
		return;
	} else if(arr[row][col] == 0) {
		// 표적 좌표의 값이 0인 경우 1로 바꾼 후, 인접좌표 재귀호출 
		arr[row][col] = 1;
		makeOne(arr, row + 1, col); // down
		makeOne(arr, row - 1, col); // up
		makeOne(arr, row, col + 1); // right
		makeOne(arr, row, col - 1); // left
	}
}

/*
	function: main 함수
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	// 데이터 입력 
	int arr[10][10] = {
		{2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2},
		{2,2,2,0,0,0,0,2,2,2},
		{2,2,2,2,0,0,0,2,2,2},
		{2,2,2,2,0,0,0,2,2,2},
		{2,2,2,2,0,0,0,0,2,2},
		{2,2,2,2,0,2,2,2,2,2},
		{2,2,2,2,0,2,2,2,2,2},
		{2,2,2,2,0,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2}
	};
	
	// 초기행렬 출력 
	printf("[Initial Array]\n");
	printArray(arr);
	
	// 결과행렬 출력 
	printf("[Result Array]\n");
	makeOne(arr, 4, 5); // 4행 5열 위치부터 시작 
	printArray(arr);
	
	// 프로그램 종료 
	return 0;
}
