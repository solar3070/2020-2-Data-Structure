#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *insert_node(TreeNode *root, int key)  // 변경하지 말라. 아직 배우지 않았으나 어떤 규칙으로 트리에 노드를 삽입한다.
{
    TreeNode *p, *t; // p는 부모노드, t는 현재노드 
	TreeNode *n;	    // n은 새로운 노드

	t = root;
	p = NULL;

	// 탐색을 먼저 수행, 반복을 이용해서 search(위의 search함수 참조)
	while (t != NULL){ // 현재노드가 NULL이 될때까지
	     //if( key == t->key ) return;
	     p = t; // 현재노드를 부모노드로 하고
             // 현재노드를 전진
             if( key < t->key ) 
               t = t->left; 
	     else 
               t = t->right;
        }
	// key가 트리 안에 없으므로 삽입 가능
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

int count_key(TreeNode *node, int key) // 이 함수를 작성해서 제출
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

int main(void) // main은 변경하지 말라. 
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
