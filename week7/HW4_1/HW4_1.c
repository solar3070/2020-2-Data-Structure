#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20

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

// 비단말 노드 개수
int get_nonleaf_count(TreeNode *t)
{
	int count = 0;
	if (t != NULL) {
		if (t->left != NULL || t->right != NULL)
			count++;
		if (t->left != NULL) 
			count += get_nonleaf_count(t->left);
		if (t->right != NULL) 
			count += get_nonleaf_count(t->right);
	}
	return count;
}

// 트리의 구조가 같고 대응되는 노드들의 값이 동일하면 1, 아니면 0
int equal(TreeNode *t1, TreeNode *t2) 
{
	if (t1 == NULL && t2 == NULL)
		return 1;
	else if (t1 == NULL || t2 == NULL) // 둘 중 하나가 널이면
		return 0;
	else if (t1->data != t2->data)
		return 0;
	else
		return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

// 자식이 하나인 노드 개수
int get_oneleaf_count(TreeNode *node)
{
	int count = 0;
	if (node != NULL) {
		if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) // 자식 둘 중 하나가 널이면
			count++;
		if (node->left != NULL)
			count += get_oneleaf_count(node->left);
		if (node->right != NULL)
			count += get_oneleaf_count(node->right);
	}
	return count;
}

// 자식이 둘인 노드 개수
int get_twoleaf_count(TreeNode *node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL) // 자식 둘 다 널이 아니면
			count++;
		if (node->left != NULL)
			count += get_twoleaf_count(node->left);
		if (node->right != NULL)
			count += get_twoleaf_count(node->right);
	}
	return count;
}

// 노드 최대값
int get_max(TreeNode *node)
{
	int leftMax = INT_MIN, rightMax = INT_MIN, max;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return node->data;
		if (node->left != NULL)
			leftMax = get_max(node->left);
		if (node->right != NULL)
			rightMax = get_max(node->right);

		max = leftMax > rightMax ? leftMax : rightMax;
		return max > node->data ? max : node->data;
	}
}

// 노드 최소값
int get_min(TreeNode *node) 
{
	int leftMin = INT_MAX, rightMin = INT_MAX, min;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return node->data;
		if (node->left != NULL)
			leftMin = get_min(node->left);
		if (node->right != NULL)
			rightMin = get_min(node->right);

		min = leftMin < rightMin ? leftMin : rightMin;
		return min < node->data ? min : node->data;
	}
}

// 노드 값 1씩 증가
void node_increase(TreeNode *node) 
{
	if (node != NULL) {
		if (node->left != NULL)
			node_increase(node->left);
		if (node->right != NULL)
			node_increase(node->right);
		node->data++;
	}
}

// 트리 복제해서 새로운 트리 반환
TreeNode *copy(TreeNode *node)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	if (node != NULL)	{
		temp->data = node->data;
		temp->left = node->left != NULL ? copy(node->left) : NULL;
		temp->right = node->right != NULL ? copy(node->right) : NULL;

		return temp;
	}
	return NULL;
}

// 전위 순회
void preorder(TreeNode *root) {
	if (root != NULL) {
		printf("[%d] ", root->data);  // 노드 방문
		preorder(root->left);// 왼쪽서브트리 순회
		preorder(root->right);// 오른쪽서브트리 순회
	}
}

int main(void)
{
	TreeNode *result[MAX_TREE_SIZE];
	TreeNode *clone;
	int i, num;

	printf("가)\n");
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
	
	/* search함수 구현 x
	printf("\n 나)\n");
	num = search(root, 15, result);
	for (i = 0; i < num; i++)
		printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n"); */
	
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