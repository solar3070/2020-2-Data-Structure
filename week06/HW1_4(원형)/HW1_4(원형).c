#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode *link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head) // 틀림
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head->link);
	printf("리스트의 끝\n");
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
	return head;	// 변경된 헤드 포인터를 반환한다. 
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
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* delete_first(ListNode* head)
{
     ListNode *temp;
     if (head == NULL) {
          printf("리스트가 비어 삭제를 못함\n");
          return NULL;
     } 

     else if (head == head->link) {  // 즉 하나의 노드가 남았을때 
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

// 리스트의 마지막 노드 삭제 후 헤드노드 반환
ListNode* delete_last(ListNode* head)
{
	ListNode *temp;

	if (head == NULL) {
		printf("리스트가 비어있어 삭제를 못함\n");
		return NULL;
	}
	else if (head == head->link) { // 노드가 하나
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

// 리스트의 길이 반환
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

// data를 가지고 있는 첫 번째 노드를 찾아서 반환
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

// 원형 연결 리스트 테스트 프로그램
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

	printf("리스트의 길이는 %d\n", get_size(head));

	printf("Enter a data: ");
	scanf("%d", &data);
	head = search(head, data);
	print_list(head);

	free(head);
	return 0;
}
