#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *new_node(int item)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

void inorder(TreeNode *root)
{
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}

TreeNode *search(TreeNode *node, int key)
{
	if (node == NULL) return NULL;
	if (node->key == key) return node;
	if (key < node->key) 
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode *insert_node(TreeNode *root, int key)
{
	if (root == NULL) return new_node(key);
	if (key < root->key)
		root->left = insert_node(root->left, key);
	else if (key > root->key)
		root->right = insert_node(root->right, key);
	return root;
}

TreeNode *min_value_node(TreeNode *node)
{
	TreeNode *current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode *delete_node(TreeNode *root, int key)
{
	TreeNode *temp;
	if (root == NULL) return root; 

	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	else 
		if (root->left == NULL) {
			temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			temp = root->left;
			free(root);
			return temp;
		}
		else {
			temp = min_value_node(root->right);
			root->key = temp->key;
			root->right = delete_node(root->right, temp->key);
		}
	return root;
}

int main(void) 
{
	TreeNode *root = NULL;

	root = insert_node(root, 40);
	root = insert_node(root, 20);
	root = insert_node(root, 60);
	root = insert_node(root, 10);
	root = insert_node(root, 30);
	root = insert_node(root, 50);
	root = insert_node(root, 70);
	root = insert_node(root, 5);
	root = insert_node(root, 15);
	root = insert_node(root, 23);
	root = insert_node(root, 55);
	root = insert_node(root, 52);
	
	printf("이진 탐색 트리 중위 순회 결과\n");
	inorder(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함\n");
	else
		printf("이진 탐색 트리에서 30을 발견못함\n");

	root = delete_node(root, 40);
	inorder(root);
	return 0;
}