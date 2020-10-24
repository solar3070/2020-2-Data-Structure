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

void print_list(ListNode *head)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("����Ʈ��\n");
}

int is_in_list(ListNode *head, element item)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == item)
			return 1;
	return 0;
}

int get_length(ListNode *head)
{
	ListNode *p;
	int len = 0;
	for (p = head; p != NULL; p = p->link)
		len++;
	return len;
}

int get_total(ListNode *head)
{
	ListNode *p;
	int total = 0;
	for (p = head; p != NULL; p = p->link)
		total += p->data;
	return total;
}

element get_entry(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;
	if (pos < 0 || pos >= get_length(head))
		error("��ġ ����");
	for (i = 0; i < pos; i++)
		p = p->link;
	return p->data;
}

ListNode *insert_next(ListNode *head, ListNode *pre, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = pre->link;
	pre->link = newNode;
	return head;
}

ListNode *insert_first(ListNode *head, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}

ListNode *insert_last(ListNode *head, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *p = head;
	newNode->data = value;
	newNode->link = NULL;
	if (head == NULL)
		head = newNode;
	else {
		while (p->link != NULL)
			p = p->link;
		p->link = newNode;
	}
	return head;
}

ListNode *insert_pos(ListNode *head, int pos, element value) //��
{
	ListNode *p = head;
	int i;
	if (pos < 0 || pos > get_length(head)) 
		error("��ġ ����");
	else if (pos == 0)
		return insert_first(head, value);
	else {
		for (i = 0; i < pos - 1; i++)
			p = p->link;
		return insert_next(head, p, value); 
	}
}

ListNode *delete_next(ListNode *head, ListNode *pre)
{
	ListNode *temp = pre->link;
	pre->link = temp->link;
	free(temp);
	return head;
}

ListNode *delete_first(ListNode *head)
{
	ListNode *temp = head;
	if (head == NULL)
		error("������ �׸��� ����");
	head = temp->link;
	free(temp);
	return head;
}

ListNode *delete_last(ListNode *head)
{
	ListNode *temp = head;
	ListNode *prev;
	if (head == NULL)
		error("������ �׸��� ����");
	else if (head->link == NULL) {
		head == NULL;
		free(temp);
	}
	else {
		while (temp->link != NULL) {
			prev = temp;
			temp = temp->link;
		}
		prev->link = NULL;
		free(temp);
	}
	return head;
}

ListNode *delete_pos(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;
	if (pos < 0 || pos >= get_length(head))
		error("��ġ ����");
	else if (pos == 0)
		return delete_first(head);
	else {
		for (i = 0; i < pos - 1; i++)
			p = p->link;
		return delete_next(head, p);
	}
}

ListNode *delete_by_key(ListNode *head, element key)
{	
	ListNode *p;
	int pos = 0;
	for (p = head; p != NULL; p = p->link) {
		if (p->data == key)
			return delete_pos(head, pos);
		pos++;
	}
	printf("%d���� ���� ���� �������� �ʴ´�\n", key);
	return head;
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
		return head1;
	}
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
	ListNode *list1 = NULL, *list2 = NULL, *list3;
	element is_in, key, value;
	int pos;
	
	//list1 = 30->20->10->�� �����. �̶� 10, 20, 30�� ������ ��带 �����Ѵ�.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1�� ���
	printf("list1 = ");
	print_list(list1);
	
	//list1�� �� �� ��带 �����Ѵ�. ��, list1 = 20->10->
	list1 = delete_first(list1);
	// list1�� ���
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44->�� �����. �̶� 11, 22, 33, 44�� ������ ��带 �����Ѵ�.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	// list2�� ���
	printf("list2 = ");
	print_list(list2);

	// list2�� �� �� ��带 �����Ѵ�. ��, list2 = 11->22->33->
	list2 = delete_last(list2);
	// list2�� ���
	printf("list2 = ");
	print_list(list2);

	//list2�� �������� �ٲ� ����Ʈ�� list3�� ����Ű�� �Ѵ�. list3 = 33->22->11->�� �����.
	list3 = reverse(list2);
	//list3�� ����Ѵ�.
	printf("list3 = ");
	print_list(list3);

	// list1 = 20->10->33->22->11->�� �����. ��, list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�.
	list1 = concat(list1, list3);
	//list1�� ����Ѵ�. 
	printf("list1 = ");
	print_list(list1);
 
	printf("\n[���� �߰��� �Լ� �׽�Ʈ(list1 �̿�)]\n");

	printf("���� ���� Ȯ���� ��: ");
	scanf("%d", &is_in);
	if (is_in_list(list1, is_in))
		printf("%d�� ����Ʈ�� �ִ�\n", is_in);
	else
		printf("%d�� ����Ʈ�� ����\n", is_in);

	printf("����Ʈ�� ����� ���� %d\n", get_length(list1));

	printf("����Ʈ�� ��� ����� ���� %d\n", get_total(list1));

	printf("���� �˰� ���� ����� �ε���: ");
	scanf("%d", &pos);
	printf("�ε����� %d�� ����� ���� %d\n", pos, get_entry(list1, pos));
	
	printf("���� �ְ� ���� ����� �ε���: ");
	scanf("%d", &pos);
	printf("���� ��: ");
	scanf("%d", &value);
	list1 = insert_pos(list1, pos, value);
	printf("list1 = ");
	print_list(list1);
	
	printf("���� �����ϰ� ���� ����� �ε���: ");
	scanf("%d", &pos);
	list1 = delete_pos(list1, pos);
	printf("list1 = ");
	print_list(list1);
	
	printf("�����ϰ� ���� ��: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1);
} 