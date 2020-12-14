#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *insert_node(TreeNode *root, int key)
{
    TreeNode *p, *t; // p�� �θ���, t�� ������ 
	TreeNode *n;	    // n�� ���ο� ���

	t = root;
	p = NULL;

	while (t != NULL){ // �����尡 NULL�� �ɶ�����
	     //if( key == t->key ) return;
	     p = t; // �����带 �θ���� �ϰ�
             // �����带 ����
             if( key < t->key ) 
               t = t->left; 
	     else 
               t = t->right;
        }

	n = (TreeNode *) malloc(sizeof(TreeNode));
	if( n == NULL ) return;
	// ������ ����
	n->key = key;
	n->left = n->right = NULL;

	// �θ� ���� ��ũ ����
	if( p != NULL ) 
	    if( key < p->key ) 
            p->left = n;
	    else 
            p->right = n;
	else // ���ʿ� Ʈ���� ����־�����
			root = n;
	return root;
}

int get_height(TreeNode *root)
{
	int lH, rH;
	if (root == NULL) 
		return 0;
	else {
		lH = get_height(root->left);
		rH = get_height(root->right);

		if (lH > rH)
			return 1 + lH;
		else
			return 1 + rH;
	}
}

int isBalanced(TreeNode *node) // �� �Լ��� ����
{
	int lH = 0, rH = 0;
	int n;

	lH = get_height(node->left);
	rH = get_height(node->right);
	
	if (lH > rH)
		n = lH - rH;
	else 
		n = rH - lH;

	if (n <= 1)
		return 1;
	else 
		return 0;
}

int main(void) // main�� �������� ����. 
{
	int n, key;
	TreeNode *root = NULL;
	int i;

	for (i = 0; i < 3; i++) { // ������ �ݺ��ؼ� �˻�
		root = NULL;

		// Ʈ���� �����
		scanf("%d", &n);
		while (n != -1) {
			root = insert_node(root, n);
			scanf("%d", &n);
		}
		printf("%d\n", isBalanced(root));
	}
}
