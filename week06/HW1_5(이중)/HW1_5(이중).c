#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	// 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode *before, element data)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	newnode->data = data;

	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 역순으로 순회하면서 저장된 데이터 값 출력
void print_reverse_dlist(DListNode *head)
{
	DListNode *p = head->llink;

	while (p != head) {
		printf("%d ", p->data);
		p = p->llink;
	}
	printf("\n");
}

// data를 갖는 노드 반환
DListNode* search(DListNode *head, element data)
{
	DListNode *p = head->rlink;

	while (p != head) {
		if (p->data == data) {
			p->llink = head;
			p->rlink = head;
			head->llink = p;
			head->rlink = p;
			return head;
		}
		p = p->rlink;
	}
	return NULL;
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	element data;
	init(head);
	printf("추가 단계\n");
	
	// 처음에 삽입
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);
	
	// 뒤에 삽입하려면?
	dinsert(head->llink, 99);
	print_dlist(head);
	
	printf("\n삭제 단계\n");
	// 앞에것을 삭제 
	ddelete(head, head->rlink);
	print_dlist(head);
	
	// 뒤에것을 삭제 
	ddelete(head, head->llink);
	print_dlist(head);
	
	print_reverse_dlist(head);

	printf("Enter a data: ");
	scanf("%d", &data);
	head = search(head, data);
	print_dlist(head);

	free(head);
	return 0;
}