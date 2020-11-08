#include <stdio.h>
#include <stdlib.h>

// 자기 참조 구조체의 정의(선언)
typedef struct ListNode {
	int number;
	struct ListNode *link;
} ListNode;

// 반복을 이용하여 노드리스트를 출력
// 힌트: temp를 head부터 시작하여 전진하면서 temp가 가리키는 number를 출력. temp가 NULL이 될때까지.
void displayList1(ListNode *head)
{
	ListNode *temp = head;

	while (1) {
		printf("%d ", temp->number);

		if (temp->link == NULL)
			return;

		temp = temp->link;
	} 
}

// 순환을 이용하여 노드리스트를 출력
void displayList2(ListNode *head)
{
	ListNode *temp = head;

	printf("%d ", temp->number);

	if (temp->link == NULL)
		return;
	displayList2(temp->link);
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