#include <stdio.h>
#include <windows.h>

void print_upLine() {
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
}

void print_downLine() {
	printf("����������������������");
	printf("��������������������");
	printf("����������������������\n");
}

void printFirst() {
	print_upLine();
	printf("��        Sample Program        ��\n");
	print_downLine();
	print_upLine();
	printf("��  1. �ð�ǥ ��ȿ���˻�        ��\n");
	printf("��  2. �ð�ǥ �ҷ�����          ��\n");
	print_downLine();
	print_upLine();
	printf("��  Select:                     ��\n");
	print_downLine();
	
	gotoxy(12, 9);
}

void gotoxy(int x, int y) {
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {
	printFirst();
	
	getchar();
	
	return 0;
}
