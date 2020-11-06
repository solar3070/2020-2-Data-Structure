#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *insert_node(TreeNode *root, int key)  // �������� ����. ���� ����� �ʾ����� � ��Ģ���� Ʈ���� ��带 �����Ѵ�.
{
    TreeNode *p, *t; // p�� �θ���, t�� ������ 
	TreeNode *n;	    // n�� ���ο� ���

	t = root;
	p = NULL;

	// Ž���� ���� ����, �ݺ��� �̿��ؼ� search(���� search�Լ� ����)
	while (t != NULL){ // �����尡 NULL�� �ɶ�����
	     //if( key == t->key ) return;
	     p = t; // �����带 �θ���� �ϰ�
             // �����带 ����
             if( key < t->key ) 
               t = t->left; 
	     else 
               t = t->right;
        }
	// key�� Ʈ�� �ȿ� �����Ƿ� ���� ����
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

int count_key(TreeNode *node, int key) // �� �Լ��� �ۼ��ؼ� ����
{
	if (node == NULL)
		return 0;
	else {
		if (node->key == key)
			return 1 + count_key(node->left, key) + count_key(node->right, key);
		else
			return count_key(node->left, key) + count_key(node->right, key);
	}
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
	printf("%d\n", count_key(root, key));
}
