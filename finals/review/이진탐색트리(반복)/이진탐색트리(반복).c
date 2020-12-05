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
	while (node) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

TreeNode *insert_node(TreeNode *root, int key)
{
	TreeNode *t, *p, *n;
	t = root;
	p = NULL;

	while (t != NULL) {
		if (key == t->key) return root;
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}

	n = new_node(key);

	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else
			p->right = n;
	else
		root = n;
	return root;
}

TreeNode *delete_node(TreeNode *root, int key)
{
	TreeNode *t, *p, *child, *succ_p, *succ;
	t = root;
	p = NULL;

	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}

	if (t == NULL) {
		printf("key is not in the tree\n");
		return root;
	}

	if (t->left == NULL && t->right == NULL) 
		if (p != NULL) 
			if (p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		else
			root = NULL;
	else if (t->left != NULL ||t->right != NULL) {
		child = (t->left != NULL) ? t->left : t->right;

		if (p != NULL)
			if (p->left == t)
				p->left = child;
			else
				p->right = child;
		else
			root = child;
	}
	else {
		succ_p = t;
		succ = t->right;

		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;

		t->key = succ->key;
		t = succ;
	}
	free(t);
	return root;
}

int main(void) 
{
	TreeNode *root = NULL;

	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 40);
	root = insert_node(root, 50);
	root = insert_node(root, 60);
	
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