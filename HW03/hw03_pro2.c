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

	printf("�Է��� ������ �������� �ʽ��ϴ�.\n");

	return;
}


void insert_node_grade(treeNode **root, int studentID, char * name, int grade) {
	treeNode *p, *t; // p�� �θ���, t�� ������
	treeNode *n; // n�� ���ο� ��� 
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
	// grade�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = *root;
	// grade�� ���� ��� t�� Ž��
	while (t != NULL&&t->grade != grade) {
		p = t;
		t = (grade < t->grade) ? t->left : t->right;
	}
	// Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� grade�� ����

	if (t == NULL) {
		printf("�ش� ������ Ʈ���� �������� �ʽ��ϴ�.");
		return;
	}

	// ù��° ��� : �ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL;
	}
	// �ι�° ��� : �ϳ��� �ڽĳ�常 ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}

	// ����° ��� : �ΰ��� �ڽ��� ������ ���
	else {
		// ���� ����Ʈ������ �İ��ڸ� ã��
		// ���� ����Ʈ������ ���� ���� ��
		succ_p = t;
		succ = t->left;
		// �İ��ڸ� ã�Ƽ� ��� ���������� �̵�
		while (succ->right != NULL) {
			succ_p = succ;
			succ = succ->right;
		}
		// �ļ����� �θ�� �ڽ��� ����
		if (succ_p->right == succ) { succ_p->right = succ->left; }
		else { succ_p->left = succ->left; }

		// �ļ��ڰ� ���� �������� ���� ��忡 ����
		t->studentID = succ->studentID;
		strcpy(t->name, succ->name);
		t->grade = succ->grade;
		// �ļ��� ����
		t = succ;
	}

	
	
	free(t);

}


void binary_sorting(int check[100],int arr[100],int i,int j) {				// bst ��� ���� ��, �ܼ� �������� �ƴ� ����Ž������ ���� ����.
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

	treeNode treeArr[100];				// ������ ������ �ҷ��� ������ ��� ����ü �迭

	int i = 0,j=99;
	int grade = 0;
	int student_number;					// ������ �й��� �����ϴµ� ���� ����
	char name[100];						// ������ �л� �̸��� �����ϴµ� ���� ����

	int arr[100];int check[100];		// binary_sorting �Լ��� �̿�� �� ���� �迭
	for (i = 0;i < 100;i++) {		// arr�� ���������� ���� ����, check�� 0���� �ʱ�ȭ
		arr[i] = i;
		check[i] = 0;
	}

	binary_sorting(check, arr, 0, 99);		// FILE ����ü ���� fp


	FILE * fp = NULL;

	if ((fp=fopen("Student_info.txt", "r"))==NULL) {
		fprintf(stderr, "�ش� ������ �������� �ʽ��ϴ�.");
		return -1;
	}
	
	i = 0;
	while (EOF != fscanf(fp, "%d	%[^\n]s", &student_number, &name)) {
		treeArr[i].grade = grade++;
		strcpy(treeArr[i].name, name);
		treeArr[i].studentID = student_number;
		i++;
	}
	// �л� ������ ���� ������, treeNode ����ü �迭�� treeArr�� ù��° index���� ���ʴ�� ����
	for (i = 0;i < 100;i++) {
		int k = arr[i];
		insert_node_grade(&root, treeArr[k].studentID, treeArr[k].name, treeArr[k].grade);
	}
	// binary_sorting�� ����� ���� ������� ������� ������ BST�� ����
	printf("bst ������ȸ ���\n");
	preorder(root);
	
	
	int temp;
	printf("ã�� �л��� ������ �Է��ϼ��� : ");	 // �Է� ���� ���� key������ Ž�� ����
	scanf("%d", &temp);
	search(&root, temp);
	


	printf("bst�� ��������\n");	 // ����� �������� ���� �� ��츦 ������ȸ�� ���

	printf("1. �����Ϸ��� ��尡 �ܸ� ����� ��� : ");
	printf("2015120189	OH,Chan Young	2\n");
	delete_node(&root, 2); 
	preorder(root);


	printf("2. �����Ϸ��� ��尡 �ϳ��� ���� Ʈ���� ������ �ִ� ��� : ");
	printf("2017320127	PYUN,Jang Wook	59\n");
	delete_node(&root, 59);
	preorder(root);

	printf("3. �����Ϸ��� ��尡 �ΰ��� ����Ʈ���� ���� �ִ� ��� : ");
	printf("2013250581	CHOI ,SEOKHWAN	15\n");
	delete_node(&root, 15);
	preorder(root);
	
}
