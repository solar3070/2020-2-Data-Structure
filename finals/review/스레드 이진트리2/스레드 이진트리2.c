#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int data;
	TreeNode *left, *right;
	int is_thread;
} TreeNode;

//				7
//		3				6
//	1				4		8
//				5
TreeNode n1 = {1, NULL, NULL, 1};
TreeNode n3 = {3, &n1, NULL, 1};
TreeNode n5 = {5, NULL, NULL, 1};
TreeNode n4 = {4, &n5, NULL, 1};
TreeNode n8 = {8, NULL, NULL, 0};
TreeNode n6 = {6, &n4, &n8, 0};
TreeNode n7 = {7, &n3, &n6, 0};
TreeNode *exp = &n7;

TreeNode *find_thread_successor(TreeNode *p)
{
	TreeNode *q = p->right;
	if (q == NULL) return NULL;
	if (p->is_thread == TRUE) return q;
	while (q->left != NULL) q = q->left;
	return q;
}

void thread_inorder(TreeNode *t)
{
	TreeNode *q = t;
	while (q->left != NULL) 
		q = q->left;
	do {
		printf("%d ", q->data);
		q = find_thread_successor(q);
	} while (q);
}

int main(void) 
{
	n1.right = &n3;
	n3.right = &n7;
	n5.right = &n4;
	n4.right = &n6;

	thread_inorder(exp);
}