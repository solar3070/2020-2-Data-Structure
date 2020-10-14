#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int number;
    struct ListNode *link;
} ListNode;

// 반복을 이용하여 노드리스트 출력
void displayList1(ListNode *head)
{
    ListNode *temp = head;
    while (temp != NULL) {
        printf("%d->", temp->number);
        temp = temp->link;
    }
}

// 순환을 이용하여 노드리스트 출력
void displayList2(ListNode *head)
{
    if (head == NULL)
        return;
    printf("%d->", head->number);
    displayList2(head->link);
}

int main()
{
    ListNode *head, *newNode, *temp;

    // head -> 10, NULL
    newNode = (ListNode *)malloc(sizeof(ListNode *));
    newNode->number = 10;
    newNode->link = NULL;
    head = newNode;

    // head -> 10 -> 20, NULL
    newNode = (ListNode *)malloc(sizeof(ListNode *));
    newNode->number = 20;
    newNode->link = NULL;
    head->link = newNode;

    // head -> 10 -> 20 -> 30, NULL
    newNode = (ListNode *)malloc(sizeof(ListNode *));
    newNode->number = 30;
    newNode->link = NULL;
    head->link->link = newNode;

    // head -> 10 -> 20 -> 30 -> 44, NULL
    newNode = (ListNode *)malloc(sizeof(ListNode *));
    newNode->number = 44;
    newNode->link = NULL;
    temp = head;
    while (temp->link != NULL)
        temp = temp->link;
    temp->link = newNode;

    // head -> 1 -> 10 -> 20 -> 30 -> 44, NULL
    newNode = (ListNode *)malloc(sizeof(ListNode *));
    newNode->number = 1;
    newNode->link = head;
    head = newNode;

	displayList1(head);
	printf("\n");
	displayList2(head);
}