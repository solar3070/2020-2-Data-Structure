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

ListNode* insert_first(ListNode *head, int value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}

ListNode* insert_last(ListNode *head, int value)
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

ListNode *search(ListNode *head, int x)
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

// ���⼭���� ���� �߰��� �Լ�
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
/*// pos ��ġ�� value�� ���� ��� �߰�
ListNode *insert_pos(ListNode *head, int pos, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *prev = head;
	int i;

	if (pos < 0 || pos > get_length(head)) error("��ġ ����"); // pos = get_length(head)�� �� ���� ����

	if (pos == 0) 
		head = insert_first(head, value);
	else {
		newNode->data = value;
		for (i = 0; i < pos - 1; i++) // prev�� pos ������ ����Ŵ
			prev = prev->link;
		newNode->link = prev->link;
		prev->link = newNode;
	}
	return head;
}*/
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
/*// pos ��ġ ��� ����
ListNode *delete_pos(ListNode *head, int pos)
{
	ListNode *p = head;
	ListNode *prev;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("��ġ ����"); // head�� NULL�̸� ���⼭ �ɷ���

	if (pos == 0)
		return delete_first(head); // pos�� ���������� �Էµȴٰ� ����, ���� �������� ������ �� head�� NULL�̸� delete_first�Լ����� �ɷ���
	else {
		for (i = 0; i < pos; i++) {
			prev = p;
			p = p->link;
		}
		prev->link = p->link;
		free(p);
	}
	return head;
}*/
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
/*// key���� ã�� �ش� ���� ���� ��� ����
ListNode *delete_by_key(ListNode *head, int key)
{
	ListNode *p = head;
	ListNode *prev;

	while (p != NULL) {
		if (p->data == key) 
			if (p == head) // key�� ù ��° ��忡 �ִ� ���
				 return delete_first(head);
			else {
				prev->link = p->link;
				free(p);
				return head;
			}
		prev = p;
		p = p->link;
	}
	printf("%d���� ���� ���� �������� �ʴ´�\n", key);
	return head;
}*/
// delete_pos �̿��Ͽ� key���� ã�� �ش� ���� ���� ��� ����
ListNode *delete_by_key(ListNode *head, int key)
{
	ListNode *p = head;
	int pos = 0;

	while (p != NULL) {
		if (p->data == key) 
				 return delete_pos(head, pos);
		p = p->link;
		pos++;
	}
	printf("%d���� ���� ���� �������� �ʴ´�\n", key);
	return head;
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
	
	printf("�����ϰ� ���� ��: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1);
	
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