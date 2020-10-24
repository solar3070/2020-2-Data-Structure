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
// ��� new_node�� ��� before�� �����ʿ� �����Ѵ�.
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

void remove_odd(DlistNode *phead_node) // �� �Լ��� �ۼ��Ͽ� ����
{
	DlistNode *p, *temp;
	int odd = 1;

	for (p = phead_node->rlink; p != phead_node;) {
		if (odd % 2 == 1) {
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			temp = p;
			p = p->rlink;
			free(temp);
		}
		else {
			p = p->rlink;
		}
		odd++;
	}
}

int main(void) // �������� ����
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
