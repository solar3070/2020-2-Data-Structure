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
TreeNode m7 = {28, NULL, NULL}; // �߰�
TreeNode m4={25, NULL, &m7}; // ����
TreeNode m5={15, &m3, &m4};
TreeNode m6={15, &m2, &m5};
TreeNode *root2= &m6;

// ��ܸ� ��� ����
int get_nonleaf_count(TreeNode *t)
{
	if (t == NULL)
		return 0;
	else if (t->left == NULL && t->right == NULL) // �ڽ� �� �� ��(= �ܸ� ���)
		return 0;
	else // �ڽ� �� �� �ϳ��� ��, �ڽ� �� �� �� x (�ƹ�ư �ڽ� �ִ� ���)
		return 1 + get_nonleaf_count(t->left) + get_nonleaf_count(t->right);
}

// Ʈ���� ������ ���� �����Ǵ� ������ ���� �����ϸ� 1, �ƴϸ� 0
int equal(TreeNode *t1, TreeNode *t2) 
{
	if (t1 == NULL && t2 == NULL)
		return TRUE;
	else if (t1 == NULL || t2 == NULL) // �� �� �ϳ��� ���̸�
		return FALSE;
	else if (t1->data != t2->data)
		return FALSE;
	else
		return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

// �ڽ��� �ϳ��� ��� ����
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

// �ڽ��� ���� ��� ����
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

// ��� �ִ밪
int get_max(TreeNode *node)
{
	if (node == NULL)
		return INT_MIN;
	else
		return MAX(MAX(node->data, get_max(node->left)), get_max(node->right));
}

// ��� �ּҰ�
int get_min(TreeNode *node) 
{
	if (node == NULL)
		return INT_MAX;
	else
		return MIN(MIN(node->data, get_min(node->left)), get_min(node->right));
}

// ��� �� 1�� ����
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

// Ʈ�� �����ؼ� ���ο� Ʈ�� ��ȯ
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

// ���� ��ȸ
void preorder(TreeNode *root) {
	if (root != NULL) {
		printf("[%d] ", root->data);  // ��� �湮
		preorder(root->left);// ���ʼ���Ʈ�� ��ȸ
		preorder(root->right);// �����ʼ���Ʈ�� ��ȸ
	}
}

int main(void)
{
	TreeNode *result[MAX_TREE_SIZE];
	TreeNode *clone;
	int i, num;
	
	printf("��)\n");
	printf("Ʈ�� root �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root)); // 3
	printf("Ʈ�� root2 �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root2)); // 4
	
	printf("Ʈ�� root �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root)); // 1
	printf("Ʈ�� root2 �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root2)); // 2
	
	printf("Ʈ�� root �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root)); // 2
	printf("Ʈ�� root2 �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root2)); // 2
	
	printf("Ʈ�� root ���� ���� ū ���� %d.\n", get_max(root)); // 25
	printf("Ʈ�� root2 ���� ���� ū ���� %d.\n", get_max(root2)); // 28
	
	printf("Ʈ�� root ���� ���� ���� ���� %d.\n", get_min(root)); // 4
	printf("Ʈ�� root2 ���� ���� ���� ���� %d.\n", get_min(root2)); // 4
	
	/* search�Լ� ���� x
	printf("\n ��)\n");
	num = search(root, 15, result);
	for (i = 0; i < num; i++)
		printf("(0x%p, %d), ", result[i], result[i]->data);
	printf("\n"); */
	
	printf("\n��)\n");
	preorder(root);
	printf("\n");
	node_increase(root);
	preorder(root);
	printf("\n"); 
	
	printf("%s\n", equal(root, root) ? "����": "�ٸ���");
	printf("%s\n", equal(root2, root2) ? "����": "�ٸ���");
	printf("%s\n", equal(root, root2) ? "����": "�ٸ���");
	
	printf("\n ��)\n");
	clone = copy(root) ;
	preorder(root) ;
	printf("\n");
	preorder(clone) ;
	printf("\n");
}