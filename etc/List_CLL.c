/*
	Example of Circular Linked List.
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

ListNode *create_node(element data, ListNode *link) {
	
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL) {
		printf("메모리 할당 에러\n");
		exit(1);
	}
	new_node -> data = data;
	new_node -> link = link;
	return(new_node);
}

void insert_first(ListNode **phead, ListNode *node) {
	
	if(*phead == NULL) {
		*phead = node;
		node -> link = node;
	} else {
		node -> link = (*phead) -> link;
		(*phead) -> link = node;
	}
}

void insert_last(ListNode **phead, ListNode *node) {
	
	if(*phead == NULL) {
		*phead = node;
		node -> link = node;
	} else {
		node -> link = (*phead) -> link;
		(*phead) -> link = node;
		*phead = node;
	}
}

void display(ListNode *head) {
	
	ListNode *p;
	if(head == NULL) {
		return;
	}
	
	p = head;
	do {
		printf("%d -> ", p -> data);
		p = p -> link;
	} while(p != head);
	printf("\n");
}

main() {
	
	ListNode *list1 = NULL;
	
	insert_first(&list1, create_node(10, NULL));
	insert_first(&list1, create_node(20, NULL));
	insert_first(&list1, create_node(30, NULL));
	display(list1);
}
