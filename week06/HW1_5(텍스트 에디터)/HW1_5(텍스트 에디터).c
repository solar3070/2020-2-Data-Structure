#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100

// 1) 
typedef struct {
	char line[MAX_CHAR_PER_LINE];
} element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode; 

void display_te(ListNode *head) // text editor 를 위해 변경 // 2)
{
	ListNode *p = head;
	int i;

	printf("---------text edited---------\n");
	for (i = 1; p != NULL; i++) {
		printf("(%d) %s", i, p->data.line);
		p = p->link;
	}
}

// 나머지 함수들 정의를 그대로 여기에
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode *head, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 동적 메모리 할당을 통해 새로운 노드 p 생성
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert_last(ListNode *head, element value)
{
	ListNode *temp = head;
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = p;
	}
	return head;
}

ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) error("삭제할 항목이 없음");
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode *head) 
{
	ListNode *temp = head;
	ListNode *prevTemp; // 삭제 노드 전 노드의 link를 NULL로 바꾸기 위해 필요
	if (head == NULL) error("삭제할 항목이 없음");
	if (head->link == NULL) {
		free(temp);
		head = NULL;
	}
	else {
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		free(temp);
		prevTemp->link = NULL;
	}
	return head;
}

ListNode* reverse(ListNode *head)
{
	ListNode *p, *q, *r;

	p = head;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

ListNode* concat(ListNode *head1, ListNode *head2) 
{
	ListNode *p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}

// 단순 연결 리스트에 존재하는 노드의 수를 반환 
int get_length(ListNode *head)
{
	ListNode *p = head;
	int length = 0;

	while (p != NULL) {
		length++;
		p = p->link;
	}
	return length;
}

// pos 위치(0이 첫 번째 노드)에 있는 노드의 data를 반환
element get_entry(ListNode *head, int pos) 
{
	ListNode *p;
	int i = 0;
	if (pos < 0 || pos >= get_length(head))
		error("위치 오류");
	p = head;
	while (i++ < pos)
		p = p->link;
	return p->data;
}

// pos 위치에 value를 갖는 노드를 추가 
ListNode* insert_pos(ListNode *head, int pos, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("위치 오류");

	if (pos == 0)
		head = insert_first(head, value);
	else if (pos == get_length(head))
		head = insert_last(head, value);
	else {
		p->data = value;
		temp = head;
		while (i++ < pos) {
			prevTemp = temp;
			temp = temp->link;
		}
		p->link = temp;
		prevTemp->link = p;
	}
	return head;
}

// pos 위치의 노드를 삭제 
ListNode * delete_pos(ListNode *head, int pos)
{
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("위치 오류");

	if (pos == 0)
		head = delete_first(head);
	else if (pos == get_length(head))
		head = delete_last(head);
	else {
		temp = head;
		while (i++ < pos) {
			prevTemp = temp;
			temp = temp->link;
		}
		prevTemp->link = temp->link;
		free(temp);
	}
	return head;
}

char askChoice(void) {
	char choice;
	printf("------------------------------\n"); 
	printf("a: 텍스트 끝에 라인 추가\n"); 
	printf("i: 라인 번호로 라인 추가\n"); 
	printf("d: 라인 번호로 라인 삭제\n"); 
	printf("v: 라인 번호로 해당 라인 출력\n"); 
	printf("p: 전체 텍스트 출력\n"); 
	printf("q: 끝\n");

	printf("메뉴 선택: ");
	scanf("%c", &choice);
	return choice;
}

int main(void) // 3)
{
	ListNode *list = NULL;
	char choice;
	int lineNb;
	element newElement;

	while ((choice = askChoice()) != 'q') {
		switch (choice) {
		case 'a':
			printf("텍스트 끝에 삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("삽입할 라인 번호: ");
			scanf("%d", &lineNb);

			printf("삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_pos(list, lineNb - 1, newElement);
			display_te(list);
			break;
		case 'd':
			printf("삭제할 라인 번호: ");
			scanf("%d", &lineNb);

			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("출력할 라인 번호: ");
			scanf("%d", &lineNb);

			printf("(%d) %s", lineNb, get_entry(list, lineNb - 1).line);
			break;
		case 'p':
			display_te(list);
		}
		fflush(stdin);
	}
} 