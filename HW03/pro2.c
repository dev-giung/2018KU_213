
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

	printf("입력한 학번이 존재하지 않습니다.\n");

	return;
}

void insert_node(treeNode **root, int studentID,char * name,int grade) {
	treeNode *p, *t; // p는 부모노드, t는 현재노드
	treeNode *n; // n은 새로운 노드 
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
		printf("해당 학번이 트리에 존재하지 않습니다.");
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
		fprintf(stderr, "해당 파일이 존재하지 않습니다.");
		return -1;
	}
	
	while (EOF != fscanf(fp,"%d	%[^\n]s", &student_number, &name)) {
		insert_node(&root, student_number, name, grade++);
	}
	
	preorder(root);
	
	int temp;
	printf("찾을 학생의 학번을 입력하세요 : ");
	scanf("%d", &temp);
	search(&root, temp);
	


	printf("삭제연산\n");

	printf("1. 삭제하려는 노드가 단말 노드일 경우 : ");
	printf("2013160132	LEE,Gunsoo\n");
	delete_node(&root, 2013160132);
	preorder(root);


	printf("2. 삭제하려는 하나의 서브 트리만 가지고 있는 경우 : ");
	printf("2015160040	CHO,JeongDae\n");
	delete_node(&root, 2015160040);
	preorder(root);

	printf("3. 삭제하려는 노드가 두개의 서브트리를 갖고 있는 경우 : ");
	printf("2012270085	KIM,taehyeong\n");
	delete_node(&root, 2012270085);
	preorder(root);
	
}
