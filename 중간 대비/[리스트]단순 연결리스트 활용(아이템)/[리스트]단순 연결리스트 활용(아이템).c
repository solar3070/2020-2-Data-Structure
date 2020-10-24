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

void display(ListNode *head)
{
	ListNode *p;
	printf("( ");
	for (p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(")\n");
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
		error("위치 오류");
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

ListNode *insert_pos(ListNode *head, int pos, element value) //★
{
	ListNode *p = head;
	int i;
	if (pos < 0 || pos > get_length(head)) 
		error("위치 오류");
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
		error("삭제할 항목이 없음");
	head = temp->link;
	free(temp);
	return head;
}

ListNode *delete_last(ListNode *head)
{
	ListNode *temp = head;
	ListNode *prev;
	if (head == NULL)
		error("삭제할 항목이 없음");
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
		error("위치 오류");
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
	printf("아이템 %d는 보유하고 있지 않습니다.\n", key);
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

// 아이템 추가 함수
ListNode *add_item(ListNode *phead, int new_item)
{
	if (get_total(phead) + new_item > 100)
		printf("최대 무게(100kg) 초과로 아이템 %d를 추가할 수 없음\n", new_item); 
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