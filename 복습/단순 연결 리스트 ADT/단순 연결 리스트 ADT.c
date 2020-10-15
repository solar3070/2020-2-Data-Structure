#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // ��� Ÿ��
	element data;
	struct ListNode *link;
} ListNode;

// ���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert_next(ListNode *head, ListNode *pre, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = pre->link;
	pre->link = newNode;
	return head;
}

ListNode* insert_first(ListNode *head, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}

ListNode* insert_last(ListNode *head, element value)
{
	ListNode *p;
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = NULL;

	if (head == NULL)
		head = newNode;
	else {
		for (p = head; p->link != NULL; p = p->link);
		p->link = newNode;
	}
	return head;
}
// pre�� ����Ű�� ����� ���� ��带 ���� 
ListNode* delete_next(ListNode *head, ListNode *pre)
{
	ListNode *p = pre->link;
	pre->link = p->link;
	free(p);
	return head;
}

ListNode* delete_first(ListNode *head)
{
	ListNode *p = head;
	if (head == NULL) error("������ �׸��� ����");
	head = p->link;
	free(p);
	return head;
}

ListNode* delete_last(ListNode *head)
{
	ListNode *p;
	ListNode *prev;
	if (head == NULL) error("������ �׸��� ����");
	if (head->link == NULL) {
		free(head);
		head = NULL;
	}
	else {
		for (p = head; p->link != NULL; p = p->link)
			prev = p;
		free(p);
		prev->link = NULL;
	}
	return head;
}

void print_list(ListNode *head)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("����Ʈ��\n");
} 

ListNode *search(ListNode *head, element x)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == x)
			return p;
	return NULL;
}

ListNode *concat(ListNode *head1, ListNode *head2)
{
	ListNode *p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		for (p = head1; p->link != NULL; p = p->link);
		p->link = head2;
	}
	return head1;
}

ListNode *reverse(ListNode *head)
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

int main(void)
{
	ListNode *head1 = NULL, *head2;
	int i;
	for (i = 0; i < 5; i++) {
		head1 = insert_last(head1, i * 10);
		print_list(head1);
	}
	head2 = reverse(head1);
	print_list(head2);
	//head2 = insert_pos(head2, 1, 99);
	//print_list(head2);
	head2 = delete_last(head2);
	print_list(head2);
	head1 = NULL;
	head1 = insert_first(head1, 100);
	head1 = insert_first(head1, 200);
	print_list(head1);
	head1 = concat(head1, head2);
	print_list(head1);
} 