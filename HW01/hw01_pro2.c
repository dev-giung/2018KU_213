#include <stdio.h>

// 입력 문자열의 최대 길이 
#define MAX_LENGTH 100

/*
	function: 문자열을 이루는 문자를 재귀적으로 뒤집어서 출력 
	note01	: 1바이트 문자(알파벳, 숫자 등)가 아닌 2바이트 문자(한글 등)로 이루어진 문자열은
			  별도의 함수를 사용해야 하나 현재 프로그램에서는 고려하지 않음.
	note02	: Out of Memory의 우려가 있으나 현재 프로그램에서는 고려하지 않음.
	input	: char 형 포인터 (call by reference)
	output	: (Null)
*/
void printReverse(char *str) {
	 
	if(*str != '\0') { // 문자열의 끝인지 확인 
		printReverse(str + 1); // 재귀호출 
		printf("%c", *str); // 출력 
	}
}

/*
	function: main 함수
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	char input[MAX_LENGTH];
	
	// 문자열 입력 
	printf("input(original) >> ");
	scanf("%s", input);
	
	// 문자열 뒤집어 출력 
	printf("output(reverse) >> ");
	printReverse(input);
	
	// 프로그램 종료 
	return 0;
}
