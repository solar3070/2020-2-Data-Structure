#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
// ���� ���� ����Ʈ�� ��带 ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) 
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}
// �� ��带 before(head)�� �����ʿ� ����(����Ʈ �� ��, �� �� ���� ����)
void dinsert(DListNode *before, element data)
{
	DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
	newNode->data = data;
	newNode->llink = before;
	newNode->rlink = before->rlink;
	before->rlink->llink = newNode;
	before->rlink = newNode;
}
// ��� removed�� ����
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
// �������� ��ȸ�ϸ鼭 ����� ������ �� ���
void print_reverse_dlist(DListNode *head)
{
	DListNode *p;
	for (p = head->llink; p != head; p = p->llink)
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}
// data�� ���� ��� ��ȯ
DListNode* search(DListNode *head, element data)
{
	DListNode *p;
	for (p = head->rlink; p != head; p = p->rlink) 
		if (p->data == data) 
			return p;
	return NULL;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	DListNode *s; element data; //search�Լ� �׽�Ʈ��
	init(head);
	printf("�߰� �ܰ�\n");
	
	// ó���� ����
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);
	
	// �ڿ� �����Ϸ���?
	dinsert(head->llink, 99);
	print_dlist(head);
	
	printf("���� �ܰ�\n");
	// �տ����� ���� 
	ddelete(head, head->rlink);
	print_dlist(head);
	
	// �ڿ����� ���� 
	ddelete(head, head->llink);
	print_dlist(head);
	
	printf("���� ���\n");
	print_reverse_dlist(head);
	
	printf("search �Լ� �׽�Ʈ\n");
	scanf("%d", &data);
	s = search(head, data);
	if (s == NULL)
		printf("��ġ�ϴ� ���� ����\n");
	else
		printf("%d\n", s->data);

	free(head);
	return 0;
}