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
TreeNode m7 = {28, NULL, NULL}; // �߰�
TreeNode m4={25, NULL, &m7}; // ����
TreeNode m5={15, &m3, &m4};
TreeNode m6={15, &m2, &m5};
TreeNode *root2= &m6;

// ��ܸ� ��� ����
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

// Ʈ���� ������ ���� �����Ǵ� ������ ���� �����ϸ� 1, �ƴϸ� 0
int equal(TreeNode *t1, TreeNode *t2) 
{
	if (t1 == NULL && t2 == NULL)
		return 1;
	else if (t1 == NULL || t2 == NULL) // �� �� �ϳ��� ���̸�
		return 0;
	else if (t1->data != t2->data)
		return 0;
	else
		return equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

// �ڽ��� �ϳ��� ��� ����
int get_oneleaf_count(TreeNode *node)
{
	int count = 0;
	if (node != NULL) {
		if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) // �ڽ� �� �� �ϳ��� ���̸�
			count++;
		if (node->left != NULL)
			count += get_oneleaf_count(node->left);
		if (node->right != NULL)
			count += get_oneleaf_count(node->right);
	}
	return count;
}

// �ڽ��� ���� ��� ����
int get_twoleaf_count(TreeNode *node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL) // �ڽ� �� �� ���� �ƴϸ�
			count++;
		if (node->left != NULL)
			count += get_twoleaf_count(node->left);
		if (node->right != NULL)
			count += get_twoleaf_count(node->right);
	}
	return count;
}

// ��� �ִ밪
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

// ��� �ּҰ�
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

// ��� �� 1�� ����
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

// Ʈ�� �����ؼ� ���ο� Ʈ�� ��ȯ
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