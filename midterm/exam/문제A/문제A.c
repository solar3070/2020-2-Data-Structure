#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   
} ListNode; 

void display(ListNode *head)
{
	ListNode *p=head;
	while( p != NULL ){
		printf("%d->", p->data);
		p = p->link;
	}
	printf("NULL\n");
}

ListNode* insert_last(ListNode *head, int value)
{

	ListNode *temp = head;
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)
	p->data = value;	
	p->link = NULL;
	// (2)
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0) 
			temp = temp->link;

		temp->link = p;
	}
	return head;	
}

ListNode *extract_even_list(ListNode *list) // 이 함수만 작성해서 이 함수만 제출!
{
	ListNode *newNode;
	ListNode *p = NULL;
	ListNode *q, *r = NULL;
	while (list != NULL) {
		if (list->data % 2 == 0) {
			newNode = (ListNode *)malloc(sizeof(ListNode));
			newNode->data = list->data;
			q = p;
			p = newNode;
			if (q != NULL)
				q->link = p;
			else 
				r = newNode;
			newNode->link = NULL;
		}
		list = list->link;
	}
	return r;
}

int main(void) // 변경하지 말라
{
	ListNode *list = NULL;
	ListNode *evenList = NULL;
	int n;

	scanf("%d", &n);
	while (n != -1) {
        list = insert_last(list, n);
		scanf("%d", &n);
	}

    display(list); 
	evenList = extract_even_list(list);
	display(evenList);
}
