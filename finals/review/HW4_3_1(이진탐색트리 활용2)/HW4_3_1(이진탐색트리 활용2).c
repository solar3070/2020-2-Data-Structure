#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TreeNode *search(TreeNode *node, char name[]) 
{
	if (node == NULL) return NULL;
	if (!strcmp(name, node->data.name)) return node;
	if (strcmp(name,  node->data.name) == -1)
		return search(node->left, name);
	else
		return search(node->right, name);
}

TreeNode *insert_node(TreeNode *root, element data)
{
	if (root == NULL) return new_node(data);

	if (strcmp(data.name, root->data.name) == -1)
		root->left = insert_node(root->left, data);
	else if (strcmp(data.name, root->data.name) == 1)
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

TreeNode *delete_node(TreeNode *root, char name[])
{
	TreeNode *temp;
	if (root == NULL) return NULL;

	if (strcmp(name, root->data.name) == -1)
		root->left = delete_node(root->left, name);
	else if (strcmp(name, root->data.name) == 1)
		root->right = delete_node(root->right, name);
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
			root->right = delete_node(root->right, temp->data.name);
		}
	}
	return root;
}

void print_student(TreeNode *root)
{
	if (root) {
		print_student(root->left);
		printf("-------------------------\n");
		printf("학번: %d\n", root->data.id);
		printf("이름: %s\n", root->data.name);
		printf("전화번호: %s\n", root->data.tel);
		printf("학과: %s\n", root->data.dept);
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
	char name[MAX_STRING];
	char ch;

	printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
	scanf("%c", &ch);

	while (ch != 'q') {
		switch (ch) {
		case 'i':
			printf("학번 입력: ");
			scanf("%d", &stu.id);
			printf("이름 입력: ");
			scanf("%s", stu.name);
			printf("전화번호 입력: ");
			scanf("%s", stu.tel);
			printf("학과 입력: ");
			scanf("%s", stu.dept);

			root = insert_node(root, stu);
			break;
		case 'd':
			printf("삭제할 이름 입력: ");
			scanf("%s", name);

			root = delete_node(root, name);
			break;
		case 's':
			printf("탐색할 이름 입력: ");
			scanf("%s", name);

			if (temp = search(root, name)) {
				printf("-------------------------\n");
				printf("학번: %d\n", temp->data.id);
				printf("이름: %s\n", temp->data.name);
				printf("전화번호: %s\n", temp->data.tel);
				printf("학과: %s\n", temp->data.dept);
			}
			else
				printf("이름이 %s인 학생은 없습니다.\n", name);
			break;
		case 'p':
			printf("학생 정보 이름 순 출력\n");
			print_student(root);
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", count_student(root));
			break;
		}
		while (getchar() != '\n');
		printf("Enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
		scanf("%c", &ch);
	}
}