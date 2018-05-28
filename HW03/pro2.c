
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void search(treeNode ** root, int studentID) {

	treeNode * temp = (*root);

	while (temp != NULL) {
		printf("%d %s %d\n", temp->studentID, temp->name, temp->grade);
		if (studentID == temp->studentID) {
			return;
		}
		else if (studentID < temp->studentID) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}

	printf("�Է��� �й��� �������� �ʽ��ϴ�.\n");

	return;
}

void insert_node(treeNode **root, int studentID,char * name,int grade) {
	treeNode *p, *t; // p�� �θ���, t�� ������
	treeNode *n; // n�� ���ο� ��� 
	t = *root; p = NULL;
	while (t != NULL) {
		if (studentID == t->studentID) return; 
		p = t; 
		if (studentID < t->studentID) t = t->left; 
		else t = t->right; 
	}
	n = (treeNode *)malloc(sizeof(treeNode)); 
	if (n == NULL) return; 
	n->studentID = studentID; 
	strcpy(n->name , name);
	n->grade = grade;
	n->left = n->right = NULL;

	if (p != NULL) 
		if (studentID < p->studentID) p->left = n; 
		else p->right = n; 
	else *root = n;
}


void delete_node(treeNode ** root, int studentID) {
	treeNode *p, *child, *succ, *succ_p, *t;
	p = NULL;
	t = *root;

	while (t != NULL&&t->studentID != studentID) {
		p = t;
		t = (studentID < t->studentID) ? t->left : t->right;
	}

	if (t == NULL) {
		printf("�ش� �й��� Ʈ���� �������� �ʽ��ϴ�.");
		return;
	}

	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
			if (p->left == t) p->left = NULL;
			else p->right = NULL;
		}
		else
			*root = NULL;
	}
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t) p->left = child;
			else p->right = child;
		}
		else
			*root = child;
	}
	else {
		succ_p = t;
		succ = t->left;

		while (succ->right != NULL) {
			succ_p = succ;
			succ = succ->right;
		}

		if (succ_p->right == succ) { succ_p->right = succ->left; }
		else { succ_p->left = succ->left; }

		t->studentID = succ->studentID;
		strcpy(t->name, succ->name);
		t->grade = succ->grade;
		t = succ;
	}

	
	
	free(t);

}

int main() {

	treeNode * root=NULL;

	int grade = 0;
	int student_number;
	char name[100];

	FILE * fp = NULL;

	if ((fp=fopen("Student_info.txt", "r"))==NULL) {
		fprintf(stderr, "�ش� ������ �������� �ʽ��ϴ�.");
		return -1;
	}
	
	while (EOF != fscanf(fp,"%d	%[^\n]s", &student_number, &name)) {
		insert_node(&root, student_number, name, grade++);
	}
	
	preorder(root);
	
	int temp;
	printf("ã�� �л��� �й��� �Է��ϼ��� : ");
	scanf("%d", &temp);
	search(&root, temp);
	


	printf("��������\n");

	printf("1. �����Ϸ��� ��尡 �ܸ� ����� ��� : ");
	printf("2013160132	LEE,Gunsoo\n");
	delete_node(&root, 2013160132);
	preorder(root);


	printf("2. �����Ϸ��� �ϳ��� ���� Ʈ���� ������ �ִ� ��� : ");
	printf("2015160040	CHO,JeongDae\n");
	delete_node(&root, 2015160040);
	preorder(root);

	printf("3. �����Ϸ��� ��尡 �ΰ��� ����Ʈ���� ���� �ִ� ��� : ");
	printf("2012270085	KIM,taehyeong\n");
	delete_node(&root, 2012270085);
	preorder(root);
	
}
