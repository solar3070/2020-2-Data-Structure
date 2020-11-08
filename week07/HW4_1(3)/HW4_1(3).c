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

// 비단말 노드 개수
int get_nonleaf_count(TreeNode *t)
{
	if (t == NULL)
		return 0;
	else if (t->left == NULL && t->right == NULL) // 자식 둘 다 널(= 단말 노드)
		return 0;
	else // 자식 둘 중 하나가 널, 자식 둘 다 널 x (아무튼 자식 있는 경우)
		return 1 + get_nonleaf_count(t->left) + get_nonleaf_count(t->right);
}

// 트리의 구조가 같고 대응되는 노드들의 값이 동일하면 1, 아니면 0
int equal(TreeNode *t1, TreeNode *t2) 
{
	if (t1 == NULL && t2 == NULL)
		return TRUE;
	else if (t1 == NULL || t2 == NULL) // 둘 중 하나가 널이면
		return FALSE;
	else if (t1->data != t2->data)
		return FALSE;
	else
		return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

// 자식이 하나인 노드 개수
int get_oneleaf_count(TreeNode *node)
{
	if (node == NULL)
		return 0;
	else if (node->left == NULL && node->right == NULL) 
		return 0;
	else if (node->left == NULL)
		return 1 + get_oneleaf_count(node->right);
	else if (node->right == NULL)
		return 1 + get_oneleaf_count(node->left);
	else
		return get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
}

// 자식이 둘인 노드 개수
int get_twoleaf_count(TreeNode *node)
{
	if (node == NULL)
		return 0;
	else if (node->left == NULL && node->right == NULL) 
		return 0;
	else if (node->left == NULL)
		return get_twoleaf_count(node->right);
	else if (node->right == NULL)
		return get_twoleaf_count(node->left);
	else
		return 1 + get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
}

// 노드 최대값
int get_max(TreeNode *node)
{
	if (node == NULL)
		return INT_MIN;
	else
		return MAX(MAX(node->data, get_max(node->left)), get_max(node->right));
}

// 노드 최소값
int get_min(TreeNode *node) 
{
	if (node == NULL)
		return INT_MAX;
	else
		return MIN(MIN(node->data, get_min(node->left)), get_min(node->right));
}

// 노드 값 1씩 증가
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

// 트리 복제해서 새로운 트리 반환
TreeNode *copy(TreeNode *node)
{
	TreeNode *clone;
	if (node == NULL)	
		return NULL;
	else {
		clone = (TreeNode *)malloc(sizeof(TreeNode));
		if (clone == NULL) {
			fprintf(stderr, "Memory full error\n");
			exit(1);
		}
		clone->left = node->left != NULL ? copy(node->left) : NULL;
		clone->right = node->right != NULL ? copy(node->right) : NULL;
		clone->data = node->data;
		return clone;
	}
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