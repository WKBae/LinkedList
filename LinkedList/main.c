#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* PP 명령어가 검색 대상까지 포함해서 출력할 지 여부, 선언되어있을 경우 입력한 이름의 학생까지 출력 */
#define PP_INCLUSIVE

NODE* inputNode(FILE* fp);
void printNode(FILE* fp, NODE* node);

/* list.h 파일에 선언
extern NODE* createNode();
extern NODE* insertNode(NODE* head, NODE* newNode);
extern NODE* deleteNode(NODE* head, char* nameToDelete);
*/

int inputCommand(NODE** head);

int main() {
	FILE* in = fopen("input.txt", "r");
	NODE *head = NULL, *node;
	while((node = inputNode(in)) != NULL) {
		head = insertNode(head, node);
	}

	while(inputCommand(&head));

	return 0;
}

NODE* inputNode(FILE* fp) {
	NODE* node = createNode();
	int res = fscanf(fp, "%s%d%f%s%s", node->name, &node->st_no, &node->gpa, node->phone, node->province);
	if(res < 5) {
		free(node);
		return NULL;
	}
	node->next = NULL;
	return node;
}

void printNode(FILE* fp, NODE* node) {
	fprintf(fp, "%s %d %.1f %s %s\n", node->name, node->st_no, node->gpa, node->phone, node->province);
}

int inputCommand(NODE** head) {
	char cmd[5];
	printf("Type command> ");
	scanf("%s", cmd);
	
	if(strcmp(cmd, "IN") == 0) {
		*head = insertNode(*head, inputNode(stdin));
	} else if(strcmp(cmd, "PP") == 0) {
		char nameStart[50], nameEnd[50];
		NODE *start, *end;

		scanf("%s%s", nameStart, nameEnd);

		for(start = *head; start != NULL && strcmp(start->name, nameStart) != 0; start = start->next);
		for(end = start; end != NULL && strcmp(end->name, nameEnd) != 0; end = end->next);
#ifdef PP_INCLUSIVE
		end = end->next;
#else
		start = start->next;
#endif

		if(start != NULL && end != NULL) {
			for(; start != end; start = start->next) {
				printf("> ");
				printNode(stdout, start);
			}
		} else {
			printf("Cannot find student ");
			if(start == NULL) {
				puts(nameStart);
			} else {
				puts(nameEnd);
			}
		}
	} else if(strcmp(cmd, "DE") == 0) {
		char name[50];
		
		scanf("%s", name);
		
		deleteNode(*head, name);
	} else if(strcmp(cmd, "PT") == 0) {
		char phone[10];
		int i;
		NODE* np;

		scanf("%s", phone);

		for(np = *head; np != NULL; np = np->next) {
			for(i = 0; i < 3; i++) {
				if(phone[i] != np->phone[i]) {
					break;
				}
			}
			if(i == 3) {
				printf("> ");
				printNode(stdout, np);
			}
		}
	} else if(strcmp(cmd, "PA") == 0) {
		NODE* np;
		for(np = *head; np != NULL; np = np->next) {
			printf("> ");
			printNode(stdout, np);
		}
	} else if(strcmp(cmd, "EX") == 0) {
		return 0;
	}

	fflush(stdin);
	return 1;
}
