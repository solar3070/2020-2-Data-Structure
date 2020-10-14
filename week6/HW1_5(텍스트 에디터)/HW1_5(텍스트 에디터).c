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

void display_te(ListNode *head) // text editor �� ���� ���� // 2)
{
	ListNode *p = head;
	int i;

	printf("---------text edited---------\n");
	for (i = 1; p != NULL; i++) {
		printf("(%d) %s", i, p->data.line);
		p = p->link;
	}
}

// ������ �Լ��� ���Ǹ� �״�� ���⿡
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode *head, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // ���� �޸� �Ҵ��� ���� ���ο� ��� p ����
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
	if (head == NULL) error("������ �׸��� ����");
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode *head) 
{
	ListNode *temp = head;
	ListNode *prevTemp; // ���� ��� �� ����� link�� NULL�� �ٲٱ� ���� �ʿ�
	if (head == NULL) error("������ �׸��� ����");
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

// �ܼ� ���� ����Ʈ�� �����ϴ� ����� ���� ��ȯ 
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

// pos ��ġ(0�� ù ��° ���)�� �ִ� ����� data�� ��ȯ
element get_entry(ListNode *head, int pos) 
{
	ListNode *p;
	int i = 0;
	if (pos < 0 || pos >= get_length(head))
		error("��ġ ����");
	p = head;
	while (i++ < pos)
		p = p->link;
	return p->data;
}

// pos ��ġ�� value�� ���� ��带 �߰� 
ListNode* insert_pos(ListNode *head, int pos, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("��ġ ����");

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

// pos ��ġ�� ��带 ���� 
ListNode * delete_pos(ListNode *head, int pos)
{
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("��ġ ����");

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
	printf("a: �ؽ�Ʈ ���� ���� �߰�\n"); 
	printf("i: ���� ��ȣ�� ���� �߰�\n"); 
	printf("d: ���� ��ȣ�� ���� ����\n"); 
	printf("v: ���� ��ȣ�� �ش� ���� ���\n"); 
	printf("p: ��ü �ؽ�Ʈ ���\n"); 
	printf("q: ��\n");

	printf("�޴� ����: ");
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
			printf("�ؽ�Ʈ ���� ������ ����: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);

			printf("������ ����: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_pos(list, lineNb - 1, newElement);
			display_te(list);
			break;
		case 'd':
			printf("������ ���� ��ȣ: ");
			scanf("%d", &lineNb);

			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("����� ���� ��ȣ: ");
			scanf("%d", &lineNb);

			printf("(%d) %s", lineNb, get_entry(list, lineNb - 1).line);
			break;
		case 'p':
			display_te(list);
		}
		fflush(stdin);
	}
} 