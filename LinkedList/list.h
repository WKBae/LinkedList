#ifndef LIST_H
#define LIST_H

typedef struct node {
	char name[50];
	int st_no;
	float gpa;
	char phone[20];
	char province[30];
	struct node* next;
} NODE;

NODE* createNode();
NODE* insertNode(NODE* head, NODE* newNode);
NODE* deleteNode(NODE* head, char* nameToDelete);

#endif
