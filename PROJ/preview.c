#include <stdio.h>
#include <windows.h>

int main() {
	printFirst();
	
	getchar(); 
}

void printFirst() {
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	printf("��        Sample Program        ��\n");
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	printf("��  1. �ð�ǥ �����Է�          ��\n");
	printf("��  2. �ð�ǥ �ҷ�����          ��\n");
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	printf("��  Select:                     ��\n");
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
	
	gotoxy(12, 9);
}

void gotoxy(int x, int y) {
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
