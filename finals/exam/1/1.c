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

int calculate_bigger_value(TreeNode *node, int key) // �� �Լ��� ����
{
	if (node == NULL)
		return 0;
	
	if (node->key >= key)
		return node->key + calculate_bigger_value(node->left, key) + calculate_bigger_value(node->right, key);
	else 
		return calculate_bigger_value(node->left, key) + calculate_bigger_value(node->right, key);
}

int main(void) // main�� �������� ����. 
{
	int n, key;

	TreeNode *root = NULL;

	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	}

	scanf("%d", &key);
	printf("%d\n", calculate_bigger_value(root, key));
}
