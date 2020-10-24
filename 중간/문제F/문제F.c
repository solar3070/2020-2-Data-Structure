#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *insert_node(TreeNode *root, int key) // 변경하지 말라. 아직 배우지 않았으나 어떤 규칙으로 트리에 노드를 삽입한다.
{
    TreeNode *p, *t; // p는 부모노드, t는 현재노드 
	TreeNode *n;	    // n은 새로운 노드

	t = root; p = NULL;
	while (t != NULL){ // 현재노드가 NULL이 될때까지
	     //if( key == t->key ) return;
	     p = t; // 현재노드를 부모노드로 하고
		              // 현재노드를 전진
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
	else // 애초에 트리가 비어있었으면
	root = n;
	return root;
}

void inorder( TreeNode *root ){
	if ( root ){
		 inorder( root->left );	// 왼쪽서브트리 순회
		 printf("%d ", root->key ); 	// 노드 방문
		 inorder( root->right );	// 오른쪽서브트리 순회
	}
}

void preorder( TreeNode *root ){
	if ( root ){
		 printf("%d ", root->key ); 	// 노드 방문
		 preorder( root->left );	// 왼쪽서브트리 순회
		 preorder( root->right );	// 오른쪽서브트리 순회
	}
}

void printCheck(TreeNode *node)
{	
	preorder(node); printf("\n");
	inorder(node); printf("\n");
}

TreeNode *copy_child_change(TreeNode *root) // 이 함수를 작성해서 제출
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

int main(void) // main은 변경하지 말라. 
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
