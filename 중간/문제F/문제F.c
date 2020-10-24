#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *insert_node(TreeNode *root, int key) // �������� ����. ���� ����� �ʾ����� � ��Ģ���� Ʈ���� ��带 �����Ѵ�.
{
    TreeNode *p, *t; // p�� �θ���, t�� ������ 
	TreeNode *n;	    // n�� ���ο� ���

	t = root; p = NULL;
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
	n->key = key;
	n->left = n->right = NULL;
	if( p != NULL ) 
	    if( key < p->key )  p->left = n;
	    else   p->right = n;
	else // ���ʿ� Ʈ���� ����־�����
	root = n;
	return root;
}

void inorder( TreeNode *root ){
	if ( root ){
		 inorder( root->left );	// ���ʼ���Ʈ�� ��ȸ
		 printf("%d ", root->key ); 	// ��� �湮
		 inorder( root->right );	// �����ʼ���Ʈ�� ��ȸ
	}
}

void preorder( TreeNode *root ){
	if ( root ){
		 printf("%d ", root->key ); 	// ��� �湮
		 preorder( root->left );	// ���ʼ���Ʈ�� ��ȸ
		 preorder( root->right );	// �����ʼ���Ʈ�� ��ȸ
	}
}

void printCheck(TreeNode *node)
{	
	preorder(node); printf("\n");
	inorder(node); printf("\n");
}

TreeNode *copy_child_change(TreeNode *root) // �� �Լ��� �ۼ��ؼ� ����
{
	TreeNode *clone = (TreeNode *)malloc(sizeof(TreeNode));
	if (root == NULL)
		return NULL;
	else {
		clone->key = root->key;
		clone->left = root->right != NULL ? copy_child_change(root->right) : NULL;
		clone->right = root->left != NULL ? copy_child_change(root->left) : NULL;
		return clone;
	}
}

int main(void) // main�� �������� ����. 
{
	int n;
	TreeNode *root = NULL, *root2;

	scanf("%d", &n);
	while (n != -1) {
		root = insert_node(root, n);
		scanf("%d", &n);
	}
	root2 = copy_child_change(root);
	printCheck(root); 
	printCheck(root2); 
	printf("end\n");
}
