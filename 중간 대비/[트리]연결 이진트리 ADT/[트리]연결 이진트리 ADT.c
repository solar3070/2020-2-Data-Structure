#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct TreeNode {
 int data;
 struct TreeNode *left, *right;
} TreeNode;

//        root                         root2
//         15                           15
//     4        15                  4        15  
// 15        16    25           15        16    25
//                                                28

TreeNode n1={15, NULL, NULL};
TreeNode n2={4, &n1, NULL};
TreeNode n3={16, NULL, NULL};
TreeNode n4={25, NULL, NULL};
TreeNode n5={15, &n3, &n4};
TreeNode n6={15, &n2, &n5};
TreeNode *root= &n6;

TreeNode m1={15, NULL, NULL};
TreeNode m2={4, &n1, NULL};
TreeNode m3={16, NULL, NULL};
TreeNode m7 = {28, NULL, NULL}; // 추가
TreeNode m4={25, NULL, &m7}; // 변경
TreeNode m5={15, &m3, &m4};
TreeNode m6={15, &m2, &m5};
TreeNode *root2= &m6;

int get_leaf_count(TreeNode *t) 
{
	if (t == NULL)
		return 0;
	else if (t->left == NULL && t->right == NULL)
		return 1;
	else
		return get_leaf_count(t->left) + get_leaf_count(t->right);

}
int get_nonleaf_count(TreeNode *t) 
{
	if (t == NULL)
		return 0;
	else if (t->left == NULL && t->right == NULL)
		return 0;
	else
		return 1 + get_nonleaf_count(t->left) + get_nonleaf_count(t->right);
}

int equal(TreeNode *t1, TreeNode *t2) 
{
	if (t1 == NULL && t2 == NULL)
		return 1;
	else if (t1 == NULL || t2 == NULL)
		return 0;
	else if (t1->data != t2->data)
		return 0;
	else
		return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

int get_oneleaf_count(TreeNode *node) 
{
	if (node == NULL)
		return 0;
	else if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL))
		return 1 + get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
	else
		return get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
}

int get_twoleaf_count(TreeNode *node) 
{
	if (node == NULL)
		return 0;
	else if (node->left != NULL && node->right != NULL)
		return 1 + get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
	else
		return get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
}

int get_max(TreeNode *node) 
{
	if (node == NULL)
		return INT_MIN;
	else
		return MAX(MAX(get_max(node->left), get_max(node->right)), node->data);
}

int get_min(TreeNode *node) 
{
	if (node == NULL)
		return INT_MAX;
	else
		return MIN(MIN(get_min(node->left), get_min(node->right)), node->data);
}

int get_height(TreeNode *node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + MAX(get_height(node->left), get_height(node->right));
}

int get_node_count(TreeNode *node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + get_node_count(node->left) +get_node_count(node->right);
}

void node_increase(TreeNode *node) 
{
	if (node == NULL)
		return;
	else {
		node->data++;
		node_increase(node->left);
		node_increase(node->right);
	}
}

TreeNode *copy(TreeNode *node)
{
	TreeNode *clone = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL)
		return NULL;
	else {
		clone->data = node->data;
		clone->left = node->left != NULL ? copy(node->left) : NULL;
		clone->right = node->right != NULL ? copy(node->right) : NULL;
		return clone;
	}
}

// 전위 순회
void preorder(TreeNode *root) {
	if (root != NULL) {
		printf("[%d] ", root->data);  
		preorder(root->left);
		preorder(root->right);
	}
}

int main(void)
{
	TreeNode *result[MAX_TREE_SIZE];
	TreeNode *clone;
	int i, num;
	
	printf("가)\n");

	printf("트리 root 중 단말노드의 개수는 %d.\n", get_leaf_count(root)); // 3
	printf("트리 root2 중 단말노드의 개수는 %d.\n", get_leaf_count(root2)); // 3

	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root)); // 3
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2)); // 4
	
	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root)); // 1
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2)); // 2
	
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root)); // 2
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2)); // 2
	
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root)); // 25
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2)); // 28
	
	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root)); // 4
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2)); // 4
	
	printf("트리 root의 높이는 %d.\n", get_height(root)); // 3
	printf("트리 root2의 높이는 %d.\n", get_height(root2)); // 4

	printf("트리 root의 노드 개수는 %d.\n", get_node_count(root)); // 6
	printf("트리 root2의 노드 개수는 %d.\n", get_node_count(root2)); // 7

	printf("\n다)\n");
	preorder(root);
	printf("\n");
	node_increase(root);
	preorder(root);
	printf("\n"); 
	
	printf("%s\n", equal(root, root) ? "같다": "다르다");
	printf("%s\n", equal(root2, root2) ? "같다": "다르다");
	printf("%s\n", equal(root, root2) ? "같다": "다르다");
	
	printf("\n 라)\n");
	clone = copy(root) ;
	preorder(root) ;
	printf("\n");
	preorder(clone) ;
	printf("\n");
}