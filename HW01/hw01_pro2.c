#include <stdio.h>

// �Է� ���ڿ��� �ִ� ���� 
#define MAX_LENGTH 100

/*
	function: ���ڿ��� �̷�� ���ڸ� ��������� ����� ��� 
	note01	: 1����Ʈ ����(���ĺ�, ���� ��)�� �ƴ� 2����Ʈ ����(�ѱ� ��)�� �̷���� ���ڿ���
			  ������ �Լ��� ����ؾ� �ϳ� ���� ���α׷������� ������� ����.
	note02	: Out of Memory�� ����� ������ ���� ���α׷������� ������� ����.
	input	: char �� ������ (call by reference)
	output	: (Null)
*/
void printReverse(char *str) {
	 
	if(*str != '\0') { // ���ڿ��� ������ Ȯ�� 
		printReverse(str + 1); // ���ȣ�� 
		printf("%c", *str); // ��� 
	}
}

/*
	function: main �Լ�
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	char input[MAX_LENGTH];
	
	// ���ڿ� �Է� 
	printf("input(original) >> ");
	scanf("%s", input);
	
	// ���ڿ� ������ ��� 
	printf("output(reverse) >> ");
	printReverse(input);
	
	// ���α׷� ���� 
	return 0;
}
