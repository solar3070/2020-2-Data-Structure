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

void print_list(ListNode *head)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
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
ListNode * delete_by_key(ListNode *head, int key) 
{
	ListNode *temp = head;
	ListNode *prevTemp = NULL;
	int pos = 0;

	if (!is_in_list(head, key)) 
		error("�������� �ʴ� ��");

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

int main(void)
{
	ListNode *list1 = NULL, *list2 = NULL, *list3;
	int item, pos, key, value;

	//list1 = 30->20->10->�� �����. �̶� 10, 20, 30�� ������ ��带 �����Ѵ�.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30); 
	// list1�� ���
	printf("list1 = ");
	print_list(list1); 

	//list1�� �� �� ��带 �����Ѵ� ��, list1 = 20->30-> 
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
	//list3�� ���
	printf("list3 = ");
	print_list(list3); 

	// list1 = 20->30->33->22->11->�� �����. ��, list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�.
	list1 = concat(list1, list3);
	//list1�� ����Ѵ�. 
	printf("list1 = ");
	print_list(list1); 

	printf("ã�� �������� �Է��Ͻÿ�: ");
	scanf("%d", &item);
	if (is_in_list(list1, item))
		printf("�������� ����Ʈ�� �ֽ��ϴ�.\n");
	else
		printf("�������� ����Ʈ�� �����ϴ�.\n");

	printf("����Ʈ�� ����� ��: %d\n", get_length(list1));
	printf("����Ʈ�� ��� ���� ���� ��: %d\n", get_total(list1));

	printf("ã�� ����� ��ġ�� �Է��Ͻÿ�(0���� ����): ");
	scanf("%d", &pos);
	printf("%d��° ����� ��: %d\n", pos + 1, get_entry(list1, pos));

	printf("������ ���� �Է��Ͻÿ�: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1); 

	printf("������ ��ġ�� ���� �Է��Ͻÿ�: ");
	scanf("%d %d", &pos, &value);
	list1 = insert_pos(list1, pos, value);
	printf("list1 = ");
	print_list(list1); 

	printf("������ ��ġ�� �Է��Ͻÿ�: ");
	scanf("%d", &pos);
	list1 = delete_pos(list1, pos);
	printf("list1 = ");
	print_list(list1); 
}
