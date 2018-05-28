#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number = 0;

typedef struct node {
	int studentID;
	char name[100];
	int grade;
	struct node *left, *right;
}treeNode;

void preorder(treeNode * root) {
	if (root) {
		printf("%d	%s	%d\n", root->studentID, root->name, root->grade);
		preorder(root->left);
		preorder(root->right);
	}
}

void search(treeNode ** root, int grade) {

	treeNode * temp = (*root);	

	while (temp != NULL) {
		printf("%d\n", temp->grade);
		if (grade == temp->grade) {
			return;
		}
		else if (grade < temp->grade) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}

	printf("입력한 성적이 존재하지 않습니다.\n");

	return;
}


void insert_node_grade(treeNode **root, int studentID, char * name, int grade) {
	treeNode *p, *t; // p는 부모노드, t는 현재노드
	treeNode *n; // n은 새로운 노드 
	t = *root; p = NULL;
	while (t != NULL) {
		if (grade == t->grade) return;
		p = t;
		if (grade < t->grade) t = t->left;
		else t = t->right;
	}
	n = (treeNode *)malloc(sizeof(treeNode));
	if (n == NULL) return;
	n->studentID = studentID;
	strcpy(n->name, name);
	n->grade = grade;
	n->left = n->right = NULL;

	if (p != NULL)
		if (grade < p->grade) p->left = n;
		else p->right = n;
	else *root = n;
}


void delete_node(treeNode ** root, int grade) {
	treeNode *p, *child, *succ, *succ_p, *t;
	// grade를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;
	// grade를 갖는 노드 t를 탐색
	while (t != NULL&&t->grade != grade) {
		p = t;
		t = (grade < t->grade) ? t->left : t->right;
	}
	// 탐색이 종료된 시점에 t가 NULL이면 트리 안에 grade가 없음

	if (t == NULL) {
		printf("해당 성적이 트리에 존재하지 않습니다.");
		return;
	}

	// 첫번째 경우 : 단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL;
	}
	// 두번째 경우 : 하나의 자식노드만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}

	// 세번째 경우 : 두개의 자식을 가지는 경우
	else {
		// 왼쪽 서브트리에서 후계자를 찾음
		// 왼쪽 서브트리에서 가장 작은 값
		succ_p = t;
		succ = t->left;
		// 후계자를 찾아서 계속 오른쪽으로 이동
		while (succ->right != NULL) {
			succ_p = succ;
			succ = succ->right;
		}
		// 후속자의 부모와 자식을 연결
		if (succ_p->right == succ) { succ_p->right = succ->left; }
		else { succ_p->left = succ->left; }

		// 후속자가 가진 정보들을 현재 노드에 대입
		t->studentID = succ->studentID;
		strcpy(t->name, succ->name);
		t->grade = succ->grade;
		// 후속자 삭제
		t = succ;
	}

	
	
	free(t);

}


void binary_sorting(int check[100],int arr[100],int i,int j) {				// bst 노드 삽입 시, 단순 성적순이 아닌 이진탐색법과 같이 구현.
	int k = (i + j) / 2;
	if (check[k] == 1) {
		return;
	}
	else {
		arr[number++] = k; check[k] = 1;
	}

	binary_sorting(check, arr, i, k);
	binary_sorting(check, arr, k , j);
	
}

int main() {

	treeNode * root= NULL;

	treeNode treeArr[100];				// 파일의 내용을 불러와 저장할 노드 구조체 배열

	int i = 0,j=99;
	int grade = 0;
	int student_number;					// 파일의 학번을 저장하는데 사용될 변수
	char name[100];						// 파일의 학생 이름을 저장하는데 사용될 변수

	int arr[100];int check[100];		// binary_sorting 함수에 이용될 두 개의 배열
	for (i = 0;i < 100;i++) {		// arr엔 오름차순의 성적 값을, check는 0으로 초기화
		arr[i] = i;
		check[i] = 0;
	}

	binary_sorting(check, arr, 0, 99);		// FILE 구조체 변수 fp


	FILE * fp = NULL;

	if ((fp=fopen("Student_info.txt", "r"))==NULL) {
		fprintf(stderr, "해당 파일이 존재하지 않습니다.");
		return -1;
	}
	
	i = 0;
	while (EOF != fscanf(fp, "%d	%[^\n]s", &student_number, &name)) {
		treeArr[i].grade = grade++;
		strcpy(treeArr[i].name, name);
		treeArr[i].studentID = student_number;
		i++;
	}
	// 학생 정보를 읽을 때마다, treeNode 구조체 배열인 treeArr의 첫번째 index부터 차례대로 저장
	for (i = 0;i < 100;i++) {
		int k = arr[i];
		insert_node_grade(&root, treeArr[k].studentID, treeArr[k].name, treeArr[k].grade);
	}
	// binary_sorting의 결과에 의해 만들어진 순서대로 노드들을 BST에 삽입
	printf("bst 전위순회 결과\n");
	preorder(root);
	
	
	int temp;
	printf("찾을 학생의 성적을 입력하세요 : ");	 // 입력 받은 값을 key값으로 탐색 진행
	scanf("%d", &temp);
	search(&root, temp);
	


	printf("bst의 삭제연산\n");	 // 노드의 삭제연산 진행 각 경우를 전위순회로 출력

	printf("1. 삭제하려는 노드가 단말 노드일 경우 : ");
	printf("2015120189	OH,Chan Young	2\n");
	delete_node(&root, 2); 
	preorder(root);


	printf("2. 삭제하려는 노드가 하나의 서브 트리만 가지고 있는 경우 : ");
	printf("2017320127	PYUN,Jang Wook	59\n");
	delete_node(&root, 59);
	preorder(root);

	printf("3. 삭제하려는 노드가 두개의 서브트리를 갖고 있는 경우 : ");
	printf("2013250581	CHOI ,SEOKHWAN	15\n");
	delete_node(&root, 15);
	preorder(root);
	
}
