#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode *llink, *rlink;
} DListNode;

void init(DListNode* phead)
{
	phead->llink = phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
	DListNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}

void dinsert(DListNode *before, element data)
{
	DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
	newNode->data = data;
	newNode->llink = before;
	newNode->rlink = before->rlink;
	before->rlink->llink = newNode;
	before->rlink = newNode;
}

void ddelete(DListNode* head, DListNode* removed)
{
	if (head == removed) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

void print_reverse_dlist(DListNode *head)
{
	DListNode *p;
	for (p = head->llink; p != head; p = p->llink)
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}

DListNode* search(DListNode *head, element data)
{
	DListNode *p;
	for (p = head->rlink; p != head; p = p->rlink)
		if (p->data == data)
			return p;
	return NULL;
}

int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	DListNode *s; element data; //search함수 테스트용
	init(head);
	printf("추가 단계\n");
	
	// 처음에 삽입
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);
	
	// 뒤에 삽입하려면?
	dinsert(head->llink, 99);
	print_dlist(head);
	
	printf("삭제 단계\n");
	// 앞에것을 삭제 
	ddelete(head, head->rlink);
	print_dlist(head);
	
	// 뒤에것을 삭제 
	ddelete(head, head->llink);
	print_dlist(head);
	
	printf("역순 출력\n");
	print_reverse_dlist(head);
	
	printf("search 함수 테스트\n");
	scanf("%d", &data);
	s = search(head, data);
	if (s == NULL)
		printf("일치하는 값이 없음\n");
	else
		printf("%d\n", s->data);

	free(head);
	return 0;
}