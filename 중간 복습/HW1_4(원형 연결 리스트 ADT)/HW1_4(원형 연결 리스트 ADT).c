#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 
 element data;
struct ListNode *link;
} ListNode;

void print_list(ListNode* head) 
{
	ListNode *p;
	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head->link);
	printf("����Ʈ��\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = data;
	if (head == NULL) {
		head = newNode;
		newNode->link = newNode;
	}
	else {
		newNode->link = head->link;
		head->link = newNode;
	}
	return head;
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = data;
	if (head == NULL) {
		head = newNode;
		newNode->link = newNode;
	}
	else {
		newNode->link = head->link;
		head->link = newNode;
		head = newNode;
	}
	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode *p;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) {
		p = head;
		free(p);
		head = NULL;
	}
	else {
		p = head->link;
		head->link = p->link;
		free(p);
	}
	return head;
}

ListNode* delete_last(ListNode* head)
{
	ListNode *p;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) {
		p = head;
		free(p);
		head = NULL;
	}
	else {
		p = head->link;
		while (p->link != head)
			p = p->link;
		p->link = head->link;
		free(head);
		head = p;
	}
	return head;
}

ListNode* search(ListNode* head, element data)
{
	ListNode *p;
	if (head == NULL) {
		printf("����Ʈ�� ��� ����\n");
		return NULL;
	}
	p = head->link;
	do {
		if (p->data == data) 
			return p;
		p = p->link;
	} while (p != head->link);
	return NULL;
}

int get_size(ListNode* head)
{
	ListNode *p;
	int size = 0;

	if (head == NULL) return 0;

	p = head->link;
	do {
		size++;
		p = p->link;
	} while (p != head->link);
	return size;
}

int main(void)
{
	ListNode *head = NULL;
	ListNode *s; element data; // search�Լ� �׽�Ʈ��

	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);
	head = insert_last(head, 30);
	print_list(head);
	head = insert_last(head, 40);
	print_list(head);

	head = insert_first(head, 10);
	print_list(head);

	head = delete_first(head);
	print_list(head);

	head = delete_last(head);
	print_list(head);

	printf("����Ʈ�� ���̴� %d\n", get_size(head));
	
	printf("search �Լ� �׽�Ʈ\n");
	scanf("%d", &data);
	s = search(head, data);
	if (s == NULL)
		printf("��ġ�ϴ� ���� ����\n");
	else
		printf("%d\n", s->data);

	return 0;
} 