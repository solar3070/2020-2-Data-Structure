#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode *head, int value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // ���� �޸� �Ҵ��� ���� ���ο� ��� p ����
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert_last(ListNode *head, int value)
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

void display(ListNode *head)
{
	ListNode *p;

	printf("( ");
	for (p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(")\n");
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

// item �� ����Ʈ�� ������ 1 �� �ƴϸ� 0 �� ��ȯ 
int is_in_list(ListNode *head, element item) 
{
	ListNode *p = head;
	while (p != NULL) {
		if (p->data == item) return 1;
		p = p->link;
	}
	return 0;
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

// �ܼ����Ḯ��Ʈ�� ��� ������ ���� ���� ���� ��ȯ 
int get_total(ListNode *head) 
{
	ListNode *p = head;
	int total = 0;

	while (p != NULL) {
		total += p->data;
		p = p->link;
	}
	return total;
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

// key���� ��� ����
ListNode* delete_by_key(ListNode *head, int key) 
{
	ListNode *temp = head;
	ListNode *prevTemp = NULL;
	int pos = 0;

	if (!is_in_list(head, key)) {
		printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�\n", key);
		return head;
	}

	while (temp != NULL) {
		if (temp->data == key) 
			if (pos == 0)
				return head = delete_first(head);
			else if (pos == get_length(head) - 1) 
				return head = delete_last(head);
			else {
				prevTemp->link = temp->link;
				free(temp);
				return head;
			}
			prevTemp = temp;
			temp = temp->link;
			pos++;
	}
	return head;
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
ListNode* delete_pos(ListNode *head, int pos)
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

ListNode* add_item(ListNode *phead, int new_item)
{
	ListNode *p = phead;
	int weight = 0;

	while (p != NULL) {
		weight += p->data;
		p = p->link;
	}
	if (weight + new_item > 100) {
		printf("�ִ� ���� (100kg) �ʰ��� ������ %d�� �߰��� �� ����\n", new_item);
		return phead;
	}
	else
		return phead = insert_first(phead, new_item);
}

int main(void)
{
	ListNode *list = NULL;
	char choice;
	int weight;

	printf("enter a(dd), d(elete) or q(uit): ");
	scanf("%c", &choice);

	while (choice != 'q') {
		printf("enter the weight of the item: ");
		scanf("%d", &weight);

		if (choice == 'a')
			list = add_item(list, weight);
		else
			list = delete_by_key(list, weight);
		display(list);

		while (getchar() != '\n');
		printf("enter a(dd), d(elete) or q(uit): ");
		scanf("%c", &choice);
	} 
}
