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
    TreeNode *p, *t; // p는 부모노드, t는 현재노드 
	TreeNode *n;	    // n은 새로운 노드

	t = root;
	p = NULL;

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
	// 데이터 복사
	n->key = key;
	n->left = n->right = NULL;

	// 부모 노드와 링크 연결
	if( p != NULL ) 
	    if( key < p->key ) 
            p->left = n;
	    else 
            p->right = n;
	else // 애초에 트리가 비어있었으면
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

int isBalanced(TreeNode *node) // 이 함수를 제출
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

int main(void) // main은 변경하지 말라. 
{
	int n, key;
	TreeNode *root = NULL;
	int i;

	for (i = 0; i < 3; i++) { // 세번을 반복해서 검사
		root = NULL;

		// 트리를 만든다
		scanf("%d", &n);
		while (n != -1) {
			root = insert_node(root, n);
			scanf("%d", &n);
		}
		printf("%d\n", isBalanced(root));
	}
}
