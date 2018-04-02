#include <stdio.h>
#include <string.h> 

// �Է� ���ڿ��� �ִ� ���� 
#define MAX_LENGTH 100

/*
	function: �� ���� a, b�� swap
	input	: a(char *) : ����1 (call by reference)
			  b(char *) : ����2 (call by reference) 
	output	: (Null)
*/
void swap(char *a, char *b) {
	
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	function: ���ڿ��� ��������� ������ 
	note01	: 1����Ʈ ����(���ĺ�, ���� ��)�� �ƴ� 2����Ʈ ����(�ѱ� ��)�� �̷���� ���ڿ���
			  ������ �Լ��� ����ؾ� �ϳ� ���� ���α׷������� ������� ����.
	note02	: Out of Memory�� ����� ������ ���� ���α׷������� ������� ����.
	input	: str(char *) : ������ ���ڿ� (call by reference)
			  i(int) : ���ڿ� ���� index 
			  j(int) : ���ڿ� �� index 
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
	function: main �Լ�
	input	: (Null)
	output	: (Null)
*/
int main() {
	
	char mystr[MAX_LENGTH];
	
	// ���ڿ� �Է� 
	printf("input(original) >> ");
	scanf("%s", mystr);
	
	// ���ڿ� ������ ��� 
	reverseString(mystr, 0, strlen(mystr) - 1);
	printf("output(reverse) >> %s", mystr);
	
	// ���α׷� ���� 
	return 0;
}
