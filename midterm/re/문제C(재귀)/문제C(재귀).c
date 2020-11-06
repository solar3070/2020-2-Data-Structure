#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode { 
	element data;
	struct ListNode *link;   
} ListNode;

ListNode* insert_last(ListNode *head, int value)
{
	ListNode *temp = head;
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	
	p->data = value;	
	p->link = NULL;
	if (head == NULL) // 공백 리스트이면
		head = p;
	else {
		while (temp->link != 0) 
			temp = temp->link;
		temp->link = p;
	}
	return head;	// 변경된 헤드 포인터 반환
}

void reverse_display(ListNode *head) // 이 함수만 작성해서 제출
{
	if (head == NULL)
		return;
	else {
		reverse_display(head->link);
		printf("%d->", head->data);
	}
} 

int main(void) // 이것은 변경하지 말라
{	
	ListNode *list = NULL;
	int n;

	scanf("%d", &n);
	while (n != -1) {
		list = insert_last(list, n);
		scanf("%d", &n);
	}
   reverse_display(list);
   printf("end\n"); 
}
