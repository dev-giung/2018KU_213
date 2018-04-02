#include <stdio.h>
#include <string.h> 

// 입력 문자열의 최대 길이 
#define MAX_LENGTH 100

/*
	function: 두 변수 a, b를 swap
	input	: a(char *) : 변수1 (call by reference)
			  b(char *) : 변수2 (call by reference) 
	output	: (Null)
*/
void swap(char *a, char *b) {
	
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	function: 문자열을 재귀적으로 뒤집음 
	note01	: 1바이트 문자(알파벳, 숫자 등)가 아닌 2바이트 문자(한글 등)로 이루어진 문자열은
			  별도의 함수를 사용해야 하나 현재 프로그램에서는 고려하지 않음.
	note02	: Out of Memory의 우려가 있으나 현재 프로그램에서는 고려하지 않음.
	input	: str(char *) : 뒤집을 문자열 (call by reference)
			  i(int) : 문자열 시작 index 
			  j(int) : 문자열 끝 index 
	output	: (Null)
*/
void reverseString(char *str, int i, int j) {
	 
	if(i > j) {
		return;
	}
	
	swap(&str[i], &str[j]);
	reverseString(str, i + 1, j - 1);
}

/*
	function: main 함수
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	char mystr[MAX_LENGTH];
	
	// 문자열 입력 
	printf("input(original) >> ");
	scanf("%s", mystr);
	
	// 문자열 뒤집고 출력 
	reverseString(mystr, 0, strlen(mystr) - 1);
	printf("output(reverse) >> %s", mystr);
	
	// 프로그램 종료 
	return 0;
}
