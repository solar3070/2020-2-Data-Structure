#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

// ������ ���� Ÿ�� ����
typedef TreeNode *element;
typedef struct StackNode {
	element item;
	struct StackNode *link;
} StackNode;
typedef struct {
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType *s)
{
	return s->top == NULL;
}

int is_full(LinkedStackType *s)
{
	return 0;
}

void push(LinkedStackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		return;
	}
	temp->item = item;
	temp->link = s->top;
	s->top = temp;
}

TreeNode *pop(LinkedStackType *s) // ��ȯ�� ����
{
	StackNode *temp;
	TreeNode *p;
	element item;
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	temp = s->top;
	p = temp->item; // temp->item�� TreeNode��
	s->top = temp->link;
	free(temp);
	return p;
}

element peek(LinkedStackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	return s->top->item;
}

void inorder_iter(TreeNode *root)
{
	LinkedStackType s;
	init(&s);

	while (1) {
		for (; root; root = root->left)
			push(&s, root);
		if (is_empty(&s))
			break;
		else
			root = pop(&s);
		printf("[%d] ", root->data);
		root = root->right;
	}
}

//		  15
//	  4		  20
//  1	    16  25
TreeNode n1 = { 1,  NULL, NULL };
TreeNode n2 = { 4,  &n1,  NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3,  &n4 };
TreeNode n6 = { 15, &n2,  &n5 };
TreeNode *root = &n6;

int main(void)
{
	printf("���� ��ȸ=");
	inorder_iter(root);
	printf("\n");
	return 0;
}

/* �ݺ� ������ȸ
void preorder_iter(TreeNode *root)
{
	LinkedStackType s;
	init(&s);

	while (1) {
		for (; root; root = root->left) {
			printf("[%d] ", root->data);
			push(&s, root);
		}
		if (is_empty(&s))
			break;
		else
			root = pop(&s);	
		root = root->right;
	}
}
*/
/* �ݺ� ������ȸ
void postorder_iter(TreeNode *root)
{
	LinkedStackType s;
	init(&s);

	while (1) {
		do {
			if (root->data != NULL && root != NULL) {
				push(&s, root);
				root = root->left;
			}
			else
				break;
		} while (root != NULL);

		if (is_empty(&s))
			break;
		else
			root = pop(&s);

		if (root->right != NULL)
			if (root->right->data == NULL) {
				printf("[%d] ", root->data);
				root->data = NULL;
			}
			else {
				push(&s, root);
				root = root->right;
			}
		else {
			printf("[%d] ", root->data);
			root->data = NULL;
		}
	}
}
*/