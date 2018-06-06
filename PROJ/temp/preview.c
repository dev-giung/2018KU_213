#include <stdio.h>
#include <windows.h>

int main() {
	printFirst();
	
	getchar(); 
}

void printFirst() {
	printf("┌──────────");
	printf("──────────");
	printf("──────────┐\n");
	printf("│        Sample Program        │\n");
	printf("└──────────");
	printf("──────────");
	printf("──────────┘\n");
	printf("┌──────────");
	printf("──────────");
	printf("──────────┐\n");
	printf("│  1. 시간표 새로입력          │\n");
	printf("│  2. 시간표 불러오기          │\n");
	printf("└──────────");
	printf("──────────");
	printf("──────────┘\n");
	printf("┌──────────");
	printf("──────────");
	printf("──────────┐\n");
	printf("│  Select:                     │\n");
	printf("└──────────");
	printf("──────────");
	printf("──────────┘\n");
	
	gotoxy(12, 9);
}

void gotoxy(int x, int y) {
    COORD Pos = { x-1, y-1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
