#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_PER_LINE 100

typedef struct {
	char line[MAX_CHAR_PER_LINE];
} element;
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
// 리스트 처음에 노드 삽입
ListNode* insert_first(ListNode *head, element value)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	newNode->data = value;
	newNode->link = head;
	head = newNode;
	return head;
}
// 리스트 마지막에 노드 삽입
ListNode* insert_last(ListNode *head, element value)
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
// 리스트 처음 노드 삭제
ListNode* delete_first(ListNode *head)
{
	ListNode *p = head;
	if (head == NULL) error("삭제할 항목이 없음");
	head = p->link;
	free(p);
	return head;
}
// 리스트 마지막 노드 삭제
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
// 리스트 출력
void display_te(ListNode *head)
{
	ListNode *p;
	int i = 1;
	printf("----------text edited---------\n");
	for (p = head; p != NULL; p = p->link)
		printf("(%d) %s", i++, p->data.line);
} 
// 값 검색 후 해당 노드 반환
ListNode *search(ListNode *head, element x)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data.line == x.line)
			return p;
	return NULL;
}
// 리스트 2개 연결
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
// 리스트 반대로 
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
// 아이템이 리스트에 있으면 1, 없으면 0 반환
int is_in_list(ListNode *head, element item)
{
	ListNode *p;
	for (p = head; p != NULL; p = p->link)
		if (p->data.line == item.line) return 1;
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
/*// 리스트의 모든 값을 더한 합 반환
int get_total(ListNode *head)
{
	ListNode *p;
	int sum = 0;
	for (p = head; p != NULL; p = p->link)
		sum += p->data;
	return sum;
}*/
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
// delete_pos 이용하여 key값을 찾고 해당 값을 가진 노드 삭제
ListNode *delete_by_key(ListNode *head, element key)
{
	ListNode *p = head;
	int pos = 0;

	while (p != NULL) {
		if (p->data.line == key.line) 
				 return delete_pos(head, pos);
		p = p->link;
		pos++;
	}
	printf("%d값을 지닌 노드는 존재하지 않는다\n", key);
	return head;
}

char askChoice(void) {
	char choice;
	printf("------------------------------\n"); 
	printf("a: 텍스트 끝에 라인 추가\n"); 
	printf("i: 라인 번호로 라인 추가\n"); 
	printf("d: 라인 번호로 라인 삭제\n"); 
	printf("v: 라인 번호로 해당 라인 출력\n"); 
	printf("p: 전체 텍스트 출력\n"); 
	printf("q: 끝\n");

	printf("메뉴 선택: "); 
	scanf("%c", &choice);
	return choice;
}

int main(void) 
{
	ListNode *list = NULL;
	char choice;
	int lineNb;
	element newElement;

	while ((choice = askChoice()) != 'q') {
		switch (choice) {
		case 'a':
			printf("텍스트 끝에 삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_last(list, newElement);
			display_te(list);
			break;
		case 'i':
			printf("삽입할 라인 번호: ");
			scanf("%d", &lineNb);

			printf("삽입할 라인: ");
			fflush(stdin);
			fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

			list = insert_pos(list, lineNb - 1, newElement);
			display_te(list);
			break;
		case 'd':
			printf("삭제할 라인 번호: ");
			scanf("%d", &lineNb);

			list = delete_pos(list, lineNb - 1);
			display_te(list);
			break;
		case 'v':
			printf("출력할 라인 번호: ");
			scanf("%d", &lineNb);

			printf("(%d) %s", lineNb, get_entry(list, lineNb - 1).line);
			break;
		case 'p':
			display_te(list);
		}
		fflush(stdin);
	}
}