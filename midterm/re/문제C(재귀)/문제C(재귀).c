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
	if (head == NULL) // ���� ����Ʈ�̸�
		head = p;
	else {
		while (temp->link != 0) 
			temp = temp->link;
		temp->link = p;
	}
	return head;	// ����� ��� ������ ��ȯ
}

void reverse_display(ListNode *head) // �� �Լ��� �ۼ��ؼ� ����
{
	if (head == NULL)
		return;
	else {
		reverse_display(head->link);
		printf("%d->", head->data);
	}
} 

int main(void) // �̰��� �������� ����
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
