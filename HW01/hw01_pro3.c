#include <stdio.h>

/*
	function: �迭�� ���� ���.
	input	: int �� �迭 ������ (call by reference)
	output	: (Null)
*/
void printArray(int arr[][10]) {
	
	// �ܼ� ȭ�� ��� 
	int i, j;
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n"); // Row �ٹٲ� 
	}
	printf("\n");
}

/*
	function: ������ǥ�� �������� ������ 0�� ��� ��������� 1�� ����. 
			  �����¿��� 0�� ã�� ��� ȣ���ϸ�, ������ 0�� ���� ��쿡 ��Ͱ� �����.
	note	: Out of Memory�� ����� ������ ���� ���α׷������� ������� ����.
	input	: arr(int [][10]) : �����Ͱ� �Էµ� 2�����迭 (call by reference)
			  row(int) : �������� Row ��ȣ 
			  col(int) : �������� Column ��ȣ 
	output	: (Null) 
*/
void makeOne(int arr[][10], int row, int col) {
	
	// �迭�� index�� ����� ��� ���� 
	if(row > 9 || col > 9 || row < 0 || col < 0) {
		return;
	} else if(arr[row][col] == 0) {
		// ǥ�� ��ǥ�� ���� 0�� ��� 1�� �ٲ� ��, ������ǥ ���ȣ�� 
		arr[row][col] = 1;
		makeOne(arr, row + 1, col); // down
		makeOne(arr, row - 1, col); // up
		makeOne(arr, row, col + 1); // right
		makeOne(arr, row, col - 1); // left
	}
}

/*
	function: main �Լ�
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	// ������ �Է� 
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
	
	// �ʱ���� ��� 
	printf("[Initial Array]\n");
	printArray(arr);
	
	// ������ ��� 
	printf("[Result Array]\n");
	makeOne(arr, 4, 5); // 4�� 5�� ��ġ���� ���� 
	printArray(arr);
	
	// ���α׷� ���� 
	return 0;
}
