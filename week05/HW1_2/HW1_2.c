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
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 동적 메모리 할당을 통해 새로운 노드 p 생성
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
	if (head == NULL) error("삭제할 항목이 없음");
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode *head) 
{
	ListNode *temp = head;
	ListNode *prevTemp; // 삭제 노드 전 노드의 link를 NULL로 바꾸기 위해 필요
	if (head == NULL) error("삭제할 항목이 없음");
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

// item 이 리스트에 있으면 1 을 아니면 0 을 반환 
int is_in_list(ListNode *head, element item) 
{
	ListNode *p = head;
	while (p != NULL) {
		if (p->data == item) return 1;
		p = p->link;
	}
	return 0;
}

// 단순 연결 리스트에 존재하는 노드의 수를 반환 
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

// 단순연결리스트의 모든 데이터 값을 더한 합을 반환 
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

// pos 위치(0이 첫 번째 노드)에 있는 노드의 data를 반환
element get_entry(ListNode *head, int pos) 
{
	ListNode *p;
	int i = 0;
	if (pos < 0 || pos >= get_length(head))
		error("위치 오류");
	p = head;
	while (i++ < pos)
		p = p->link;
	return p->data;
}

// key값의 노드 삭제
ListNode * delete_by_key(ListNode *head, int key) 
{
	ListNode *temp = head;
	ListNode *prevTemp = NULL;
	int pos = 0;

	if (!is_in_list(head, key)) 
		error("존재하지 않는 값");

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

// pos 위치에 value를 갖는 노드를 추가 
ListNode* insert_pos(ListNode *head, int pos, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("위치 오류");

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

// pos 위치의 노드를 삭제 
ListNode * delete_pos(ListNode *head, int pos)
{
	ListNode *prevTemp = NULL;
	ListNode *temp;
	int i = 0;

	if (pos < 0 || pos > get_length(head))
		error("위치 오류");

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

	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30); 
	// list1을 출력
	printf("list1 = ");
	print_list(list1); 

	//list1의 맨 앞 노드를 삭제한다 즉, list1 = 20->30-> 
	list1 = delete_first(list1);
	// list1을 출력
	printf("list1 = ");
	print_list(list1); 

	//list2 = 11->22->33->44->를 만든다. 이때 11, 22, 33, 44의 순으로 노드를 삽입한다.
	list2 = insert_last(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	// list2를 출력
	printf("list2 = ");
	print_list(list2);

	// list2의 맨 뒤 노드를 삭제한다. 즉, list2 = 11->22->33->
	list2 = delete_last(list2);
	// list2를 출력 
	printf("list2 = ");
	print_list(list2); 

	//list2를 역순으로 바꾼 리스트를 list3가 가리키게 한다. list3 = 33->22->11->를 만든다.
	list3 = reverse(list2);
	//list3를 출력
	printf("list3 = ");
	print_list(list3); 

	// list1 = 20->30->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다.
	list1 = concat(list1, list3);
	//list1을 출력한다. 
	printf("list1 = ");
	print_list(list1); 

	printf("찾을 아이템을 입력하시오: ");
	scanf("%d", &item);
	if (is_in_list(list1, item))
		printf("아이템이 리스트에 있습니다.\n");
	else
		printf("아이템이 리스트에 없습니다.\n");

	printf("리스트의 노드의 수: %d\n", get_length(list1));
	printf("리스트의 모든 값을 더한 값: %d\n", get_total(list1));

	printf("찾을 노드의 위치를 입력하시오(0부터 시작): ");
	scanf("%d", &pos);
	printf("%d번째 노드의 값: %d\n", pos + 1, get_entry(list1, pos));

	printf("삭제할 값을 입력하시오: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1); 

	printf("삽입할 위치와 값을 입력하시오: ");
	scanf("%d %d", &pos, &value);
	list1 = insert_pos(list1, pos, value);
	printf("list1 = ");
	print_list(list1); 

	printf("삭제할 위치를 입력하시오: ");
	scanf("%d", &pos);
	list1 = delete_pos(list1, pos);
	printf("list1 = ");
	print_list(list1); 
}
