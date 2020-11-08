#include <stdio.h>
#include <stdlib.h>

// �ڱ� ���� ����ü�� ����(����)
typedef struct ListNode {
	int number;
	struct ListNode *link;
} ListNode;

// �ݺ��� �̿��Ͽ� ��帮��Ʈ�� ���
// ��Ʈ: temp�� head���� �����Ͽ� �����ϸ鼭 temp�� ����Ű�� number�� ���. temp�� NULL�� �ɶ�����.
void displayList1(ListNode *head)
{
	ListNode *temp = head;
	while (temp != NULL) {
		printf("%d->", temp->number);
		temp = temp->link;
	} 
}

// ��ȯ�� �̿��Ͽ� ��帮��Ʈ�� ���
void displayList2(ListNode *head)
{
	if (head == NULL)
		return;
	printf("%d->", head->number);
	displayList2(head->link);
} 

int main(void)
{
	ListNode *head, *newNode, *temp;

	newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->number = 10;
	newNode->link = NULL;
	head = newNode;

	newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;
	head->link = newNode;

	newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;
	head->link->link = newNode;

	newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;
	temp = head;
	while (temp->link != NULL)
		temp = temp->link;
	temp->link = newNode;

	newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = head;
	head = newNode;

	displayList1(head);
	printf("\n");
	displayList2(head); 
	printf("\n");
}