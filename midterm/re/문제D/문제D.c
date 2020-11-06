#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

void init(DlistNode *phead) 
{
	phead->llink = phead;
	phead->rlink = phead;
}

void display(DlistNode *phead) 
{
	DlistNode *p;
	for(p=phead->rlink; p != phead; p = p->rlink){
		printf("%d->", p->data);
	}
	printf("NULL\n");
}
// 노드 new_node를 노드 before의 오른쪽에 삽입한다.
void dinsert_node(DlistNode *before, element data) 
{ 
	DlistNode *new_node;
	new_node = (DlistNode *)malloc(sizeof(DlistNode));
	new_node->data = data;

	new_node->llink = before; 
	new_node->rlink = before->rlink; 
	before->rlink->llink = new_node; 
	before->rlink = new_node; 
} 

void remove_odd(DlistNode *phead_node) // 이 함수를 작성하여 제출
{
	DlistNode *p = phead_node;
	DlistNode *temp;

	if (phead_node == phead_node->rlink) return;

	do {
		temp = p->rlink;
		p->rlink = temp->rlink; //p->rlink->rlink
		p->rlink->llink = p;
		p = p->rlink;
		free(temp);
	} while (p != phead_node && p->rlink != phead_node);
}

int main(void) // 변경하지 말라
{
	DlistNode head_node;
	int n;
	init(&head_node);
	scanf("%d", &n);
	while (n != -1) {
		dinsert_node(head_node.llink, n);
		scanf("%d", &n);
	}

	display(&head_node);
	remove_odd(&head_node);
	display(&head_node); 
}