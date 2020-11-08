#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode *link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head) // Ʋ��
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head->link);
	printf("����Ʈ�� ��\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
		head = node;		// (3)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
     ListNode *temp;
     if (head == NULL) {
          printf("����Ʈ�� ��� ������ ����\n");
          return NULL;
     } 

     else if (head == head->link) {  // �� �ϳ��� ��尡 �������� 
          temp = head;
          head = NULL;
          free(temp);
     }
    else {
          temp = head->link;
          head->link = temp->link;
          free(temp);
     }
	return head;
}

// ����Ʈ�� ������ ��� ���� �� ����� ��ȯ
ListNode* delete_last(ListNode* head)
{
	ListNode *temp;

	if (head == NULL) {
		printf("����Ʈ�� ����־� ������ ����\n");
		return NULL;
	}
	else if (head == head->link) { // ��尡 �ϳ�
		temp = head;
		free(temp);
		head = NULL;
	}
	else {
		temp = head->link;
		while (temp->link != head) 
			temp = temp->link;
		temp->link = head->link;
		free(head);
		head = temp;
	}
	return head;
}

// ����Ʈ�� ���� ��ȯ
int get_size(ListNode* head)
{
	ListNode *p;
	int len = 0;

	if (head == NULL)
		return 0;

	p = head->link;
	do {
		len++;
		p = p->link;
	} while (p != head->link);
	return len;
} 

// data�� ������ �ִ� ù ��° ��带 ã�Ƽ� ��ȯ
ListNode* search(ListNode* head, element data)
{
	ListNode *p;

	if (head == NULL)
		return NULL;

	p = head->link;
	do {
		if (p->data == data) {
			p->link = p;
			return p;
		}
		p = p->link;
	} while (p != head->link);
	return NULL;
}   

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode *head = NULL;
	element data;

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

	printf("Enter a data: ");
	scanf("%d", &data);
	head = search(head, data);
	print_list(head);

	free(head);
	return 0;
}
