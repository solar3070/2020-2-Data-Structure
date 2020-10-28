#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ��ȯ���� Ž�� �Լ�
TreeNode * search(TreeNode * node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode * new_node(int item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode * insert_node(TreeNode * node, int key)
{
	if (node == NULL) return new_node(key);
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	return node;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;
	while (current->left != NULL) // �� ���� �ܸ� ��带 ã���� ������
		current = current->left;
	return current;
}

TreeNode * delete_node(TreeNode * root, int key)
{
	TreeNode * temp;
	if (root == NULL) return root;
	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode * temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode * temp = root->left;
			free(root);
			return temp;
		}
		temp = min_value_node(root->right);
		root->key = temp->key; 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void preorder(TreeNode * root) {
	if (root) {
		printf("%d ", root->key);  
		preorder(root->left);
		preorder(root->right);
	}
}

int get_height(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + MAX(get_height(root->left), get_height(root->right));
}

int get_node_count(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + get_node_count(root->left) + get_node_count(root->right);
}

int get_maximum(TreeNode *root) 
{
	if (root == NULL)
		return 0;
	while (root->right != NULL)
		root = root->right;
	return root->key;
}

int get_minimum(TreeNode *root) 
{
	if (root == NULL)
		return 0;
	while (root->left != NULL)
		root = root->left;
	return root->key;
}

int main(void)
{
	TreeNode *root = NULL;
	char ch;
	int key;

	printf("enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit): ");
	scanf("%c", &ch);

	while (ch != 'q') {
		switch(ch) {
		case 'i':
			printf("������ key�� �Է�: ");
			scanf("%d", &key);
			root = insert_node(root, key);
			break;
		case 'd':
			printf("������ key�� �Է�: ");
			scanf("%d", &key);
			root = delete_node(root, key);
			break;
		case 's':
			printf("Ž���� key�� �Է�: ");
			scanf("%d", &key);
			if (search(root, key) != NULL)
				printf("����\n");
			else
				printf("����\n");
			break;
		case 'p':
			preorder(root);
			printf("\n");
			break;
		case 'h':
			printf("Ʈ���� ���̴� %d\n", get_height(root));
			break;
		case 'c':
			printf("����� ������ %d\n", get_node_count(root));
			break;
		case 'm':
			printf("���� ū ���� %d\n", get_maximum(root));
			break;
		case 'n':
			printf("���� ���� ���� %d\n", get_minimum(root));
			break;
		}
		while (getchar() != '\n');
		printf("enter i(nsert), d(elete), s(earch), p(rint), h(eight), c(ount), m(ax), n(min), q(uit): ");
		scanf("%c", &ch);
	}
}