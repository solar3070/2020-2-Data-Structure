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
// ����Ʈ ó���� ��� ����
ListNode* insert_first(ListNode *head, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}
// ����Ʈ �������� ��� ����
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
// ����Ʈ ó�� ��� ����
ListNode* delete_first(ListNode *head)
{
	ListNode *p = head;
	if (head == NULL) error("������ �׸��� ����");
	head = p->link;
	free(p);
	return head;
}
// ����Ʈ ������ ��� ����
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
// ����Ʈ ���
void display(ListNode *head)
{
	ListNode *p;
	printf("( ");
	for (p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(")\n");
} 
// �� �˻� �� �ش� ��� ��ȯ
ListNode *search(ListNode *head, element x)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == x)
			return p;
	return NULL;
}
// ����Ʈ 2�� ����
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
// ����Ʈ �ݴ�� 
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
// �������� ����Ʈ�� ������ 1, ������ 0 ��ȯ
int is_in_list(ListNode *head, element item)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == item) return 1;
	return 0;
}
// ����Ʈ�� �����ϴ� ��� �� ��ȯ
int get_length(ListNode *head)
{
	ListNode *p;
	int len = 0;
	for (p = head; p != NULL; p = p->link)
		len++;
	return len;
}
// ����Ʈ�� ��� ���� ���� �� ��ȯ
int get_total(ListNode *head)
{
	ListNode *p;
	int sum = 0;
	for (p = head; p != NULL; p = p->link)
		sum += p->data;
	return sum;
}
// pos ��ġ�� �ִ� ����� �� ��ȯ
element get_entry(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("��ġ ����"); // head�� NULL�̸� ���⼭ �ɷ���

	for (i = 0; i < pos; i++)
		p = p->link;
	return p->data;
}
// insert_next �̿��Ͽ� pos ��ġ�� value�� ���� ��� �߰�
ListNode *insert_pos(ListNode *head, int pos, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *p = head;
	int i;

	if (pos < 0 || pos > get_length(head)) error("��ġ ����"); // pos = get_length(head) �� �� ���� ����

	if (pos == 0) 
		return insert_first(head, value);
	else {
		for (i = 0; i < pos - 1; i++) // p�� pos ������ ����Ŵ
			p = p->link;
		return insert_next(head, p, value);
	}
}
// delete_next �̿��Ͽ� pos ��ġ ��� ����
ListNode *delete_pos(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("��ġ ����"); // head�� NULL�̸� ���⼭ �ɷ���

	if (pos == 0)
		return delete_first(head); // pos�� ���������� �Էµȴٰ� ����, ���� �������� ������ �� head�� NULL�̸� delete_first�Լ����� �ɷ���
	else {
		for (i = 0; i < pos - 1; i++) 
			p = p->link;
		return delete_next(head, p);
	}
}
// delete_pos �̿��Ͽ� key���� ã�� �ش� ���� ���� ��� ����
ListNode *delete_by_key(ListNode *head, element key)
{
	ListNode *p = head;
	int pos = 0;

	while (p != NULL) {
		if (p->data == key) 
				 return delete_pos(head, pos);
		p = p->link;
		pos++;
	}
	printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�.\n", key);
	return head;
}
// ������ �߰� �Լ�
ListNode *add_item(ListNode *phead, int new_item)
{
	if (get_total(phead) + new_item > 100)
		printf("�ִ� ����(100kg) �ʰ��� ������ %d�� �߰��� �� ����\n", new_item); 
	else 
		phead = insert_first(phead, new_item);
	return phead;
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