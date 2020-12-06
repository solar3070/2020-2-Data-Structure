#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 100

typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode *new_node(element item) 
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));	
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode *search(TreeNode *node, int id) 
{
	if (node == NULL) return NULL;
	if (id == node->data.id) return node;
	if (id < node->data.id)
		return search(node->left, id);
	else
		return search(node->right, id);
}

TreeNode *insert_node(TreeNode *root, element data)
{
	if (root == NULL) return new_node(data);

	if (data.id < root->data.id)
		root->left = insert_node(root->left, data);
	else if (data.id > root->data.id)
		root->right = insert_node(root->right, data);
	return root;
}

TreeNode *min_value_node(TreeNode *node)
{
	TreeNode *current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode *delete_node(TreeNode *root, int id)
{
	TreeNode *temp;
	if (root == NULL) return NULL;

	if (id < root->data.id)
		root->left = delete_node(root->left, id);
	else if (id < root->data.id)
		root->right = delete_node(root->right, id);
	else {
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
			root->data = temp->data;
			root->right = delete_node(root->right, temp->data.id);
		}
	}
	return root;
}

void print_student(TreeNode *root)
{
	if (root) {
		print_student(root->left);
		printf("-------------------------\n");
		printf("�й�: %d\n", root->data.id);
		printf("�̸�: %s\n", root->data.name);
		printf("��ȭ��ȣ: %s\n", root->data.tel);
		printf("�а�: %s\n", root->data.dept);
		print_student(root->right);
	}
}

int count_student(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + count_student(root->left) + count_student(root->right);
}

int main(void)
{
	TreeNode *root = NULL;
	TreeNode *temp;
	element stu;
	int id;
	char ch;

	printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
	scanf("%c", &ch);

	while (ch != 'q') {
		switch (ch) {
		case 'i':
			printf("�й� �Է�: ");
			scanf("%d", &stu.id);
			printf("�̸� �Է�: ");
			scanf("%s", stu.name);
			printf("��ȭ��ȣ �Է�: ");
			scanf("%s", stu.tel);
			printf("�а� �Է�: ");
			scanf("%s", stu.dept);

			root = insert_node(root, stu);
			break;
		case 'd':
			printf("������ �й� �Է�: ");
			scanf("%d", &id);

			root = delete_node(root, id);
			break;
		case 's':
			printf("Ž���� �й� �Է�: ");
			scanf("%d", &id);

			if (temp = search(root, id)) {
				printf("-------------------------\n");
				printf("�й�: %d\n", temp->data.id);
				printf("�̸�: %s\n", temp->data.name);
				printf("��ȭ��ȣ: %s\n", temp->data.tel);
				printf("�а�: %s\n", temp->data.dept);
			}
			else
				printf("id�� %d�� �л��� �����ϴ�.\n", id);
			break;
		case 'p':
			printf("�л� ���� �й� �� ���\n");
			print_student(root);
			break;
		case 'c':
			printf("���� ����� �л��� �� ���� %d\n", count_student(root));
			break;
		}
		while (getchar() != '\n');
		printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
		scanf("%c", &ch);
	}
}