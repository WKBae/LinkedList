#include "list.h"
#include <stdlib.h>
#include <string.h>

/* 외부에 노출하지 않음 */
static NODE* findPosition(NODE* head, NODE* newNode);

NODE* createNode() {
	NODE* node = (NODE*) malloc(sizeof(NODE));
	return node;
}

NODE* insertNode(NODE* head, NODE* newNode) {
	if(!newNode) {
		return head;
	}

	if(head) {
		NODE* prev = findPosition(head, newNode);
		if(prev) {
			newNode->next = prev->next;
			prev->next = newNode;
		} else {
			newNode->next = head;
			head = newNode;
		}
	} else {
		head = newNode;
	}
	// return new head node
	return head;
}

NODE* deleteNode(NODE* head, char* nameToDelete) {
	if(head == NULL) {
		return head;
	} else if(strcmp(head->name, nameToDelete) == 0) {
		NODE* newHead = head->next;
		free(head);
		return newHead;
	} else {
		head->next = deleteNode(head->next, nameToDelete);
		return head;
	}
}
NODE* findPosition(NODE* head, NODE* newNode) {
	if(head == NULL) {
		return NULL;
	} else if(strcmp(head->name, newNode->name) > 0) {
		return NULL;
	} else {
		NODE* position = findPosition(head->next, newNode);
		if(position == NULL) {
			position = head;
		}
		return position;
	}
}
