#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode *link;
} ListNode;

// 오류 처리 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert_next(ListNode *head, ListNode *pre, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = pre->link;
	pre->link = newNode;
	return head;
}

ListNode* insert_first(ListNode *head, int value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}

ListNode* insert_last(ListNode *head, int value)
{
	ListNode *p;
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = NULL;

	if (head == NULL)
		head = newNode;
	else {
		for (p = head; p->link != NULL; p = p->link);
		p->link = newNode;
	}
	return head;
}
// pre가 가리키는 노드의 다음 노드를 삭제 
ListNode* delete_next(ListNode *head, ListNode *pre)
{
	ListNode *p = pre->link;
	pre->link = p->link;
	free(p);
	return head;
}

ListNode* delete_first(ListNode *head)
{
	ListNode *p = head;
	if (head == NULL) error("삭제할 항목이 없음");
	head = p->link;
	free(p);
	return head;
}

ListNode* delete_last(ListNode *head)
{
	ListNode *p;
	ListNode *prev;
	if (head == NULL) error("삭제할 항목이 없음");
	if (head->link == NULL) {
		free(head);
		head = NULL;
	}
	else {
		for (p = head; p->link != NULL; p = p->link)
			prev = p;
		free(p);
		prev->link = NULL;
	}
	return head;
}

void print_list(ListNode *head)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("리스트끝\n");
} 

ListNode *search(ListNode *head, int x)
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
	}
	return head1;
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

// 여기서부터 새로 추가한 함수
// 아이템이 리스트에 있으면 1, 없으면 0 반환
int is_in_list(ListNode *head, element item)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data == item) return 1;
	return 0;
}
// 리스트에 존재하는 노드 수 반환
int get_length(ListNode *head)
{
	ListNode *p;
	int len = 0;
	for (p = head; p != NULL; p = p->link)
		len++;
	return len;
}
// 리스트의 모든 값을 더한 합 반환
int get_total(ListNode *head)
{
	ListNode *p;
	int sum = 0;
	for (p = head; p != NULL; p = p->link)
		sum += p->data;
	return sum;
}
// pos 위치에 있는 노드의 값 반환
element get_entry(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("위치 오류"); // head가 NULL이면 여기서 걸러짐

	for (i = 0; i < pos; i++)
		p = p->link;
	return p->data;
}
/*// pos 위치에 value를 갖는 노드 추가
ListNode *insert_pos(ListNode *head, int pos, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *prev = head;
	int i;

	if (pos < 0 || pos > get_length(head)) error("위치 오류"); // pos = get_length(head)일 때 삽입 가능

	if (pos == 0) 
		head = insert_first(head, value);
	else {
		newNode->data = value;
		for (i = 0; i < pos - 1; i++) // prev가 pos 직전을 가리킴
			prev = prev->link;
		newNode->link = prev->link;
		prev->link = newNode;
	}
	return head;
}*/
// insert_next 이용하여 pos 위치에 value를 갖는 노드 추가
ListNode *insert_pos(ListNode *head, int pos, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	ListNode *p = head;
	int i;

	if (pos < 0 || pos > get_length(head)) error("위치 오류"); // pos = get_length(head) 일 때 삽입 가능

	if (pos == 0) 
		return insert_first(head, value);
	else {
		for (i = 0; i < pos - 1; i++) // p가 pos 직전을 가리킴
			p = p->link;
		return insert_next(head, p, value);
	}
}
/*// pos 위치 노드 삭제
ListNode *delete_pos(ListNode *head, int pos)
{
	ListNode *p = head;
	ListNode *prev;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("위치 오류"); // head가 NULL이면 여기서 걸러짐

	if (pos == 0)
		return delete_first(head); // pos가 정상적으로 입력된다고 가정, 위의 오류문을 지웠을 때 head가 NULL이면 delete_first함수에서 걸러짐
	else {
		for (i = 0; i < pos; i++) {
			prev = p;
			p = p->link;
		}
		prev->link = p->link;
		free(p);
	}
	return head;
}*/
// delete_next 이용하여 pos 위치 노드 삭제
ListNode *delete_pos(ListNode *head, int pos)
{
	ListNode *p = head;
	int i;

	if (pos < 0 || pos >= get_length(head)) error("위치 오류"); // head가 NULL이면 여기서 걸러짐

	if (pos == 0)
		return delete_first(head); // pos가 정상적으로 입력된다고 가정, 위의 오류문을 지웠을 때 head가 NULL이면 delete_first함수에서 걸러짐
	else {
		for (i = 0; i < pos - 1; i++) 
			p = p->link;
		return delete_next(head, p);
	}
}
/*// key값을 찾고 해당 값을 가진 노드 삭제
ListNode *delete_by_key(ListNode *head, int key)
{
	ListNode *p = head;
	ListNode *prev;

	while (p != NULL) {
		if (p->data == key) 
			if (p == head) // key가 첫 번째 노드에 있는 경우
				 return delete_first(head);
			else {
				prev->link = p->link;
				free(p);
				return head;
			}
		prev = p;
		p = p->link;
	}
	printf("%d값을 지닌 노드는 존재하지 않는다\n", key);
	return head;
}*/
// delete_pos 이용하여 key값을 찾고 해당 값을 가진 노드 삭제
ListNode *delete_by_key(ListNode *head, int key)
{
	ListNode *p = head;
	int pos = 0;

	while (p != NULL) {
		if (p->data == key) 
				 return delete_pos(head, pos);
		p = p->link;
		pos++;
	}
	printf("%d값을 지닌 노드는 존재하지 않는다\n", key);
	return head;
}

int main(void)
{
	ListNode *list1 = NULL, *list2 = NULL, *list3;
	element is_in, key, value;
	int pos;
	
	//list1 = 30->20->10->를 만든다. 이때 10, 20, 30의 순으로 노드를 삽입한다.
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	// list1을 출력
	printf("list1 = ");
	print_list(list1);
	
	//list1의 맨 앞 노드를 삭제한다. 즉, list1 = 20->10->
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
	//list3를 출력한다.
	printf("list3 = ");
	print_list(list3);

	// list1 = 20->10->33->22->11->를 만든다. 즉, list1과 list3를 합쳐서 list1이 가리키게 한다.
	list1 = concat(list1, list3);
	//list1을 출력한다. 
	printf("list1 = ");
	print_list(list1);
 
	printf("\n[새로 추가한 함수 테스트(list1 이용)]\n");

	printf("존재 유무 확인할 값: ");
	scanf("%d", &is_in);
	if (is_in_list(list1, is_in))
		printf("%d은 리스트에 있다\n", is_in);
	else
		printf("%d은 리스트에 없다\n", is_in);

	printf("리스트의 노드의 수는 %d\n", get_length(list1));

	printf("리스트의 모든 노드의 합은 %d\n", get_total(list1));

	printf("값을 알고 싶은 노드의 인덱스: ");
	scanf("%d", &pos);
	printf("인덱스가 %d인 노드의 값은 %d\n", pos, get_entry(list1, pos));
	
	printf("삭제하고 싶은 값: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1);
	
	printf("값을 넣고 싶은 노드의 인덱스: ");
	scanf("%d", &pos);
	printf("넣을 값: ");
	scanf("%d", &value);
	list1 = insert_pos(list1, pos, value);
	printf("list1 = ");
	print_list(list1);
	
	printf("값을 삭제하고 싶은 노드의 인덱스: ");
	scanf("%d", &pos);
	list1 = delete_pos(list1, pos);
	printf("list1 = ");
	print_list(list1);
	
	printf("삭제하고 싶은 값: ");
	scanf("%d", &key);
	list1 = delete_by_key(list1, key);
	printf("list1 = ");
	print_list(list1);
} 