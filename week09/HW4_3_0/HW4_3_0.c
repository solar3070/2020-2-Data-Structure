#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 100
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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


TreeNode * search(TreeNode * node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->data.id) return node;
	else if (key < node->data.id)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode * new_node(element item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode * insert_node(TreeNode * node, element key)
{
	if (node == NULL) return new_node(key);
	if (key.id < node->data.id)
		node->left = insert_node(node->left, key);
	else if (key.id > node->data.id)
		node->right = insert_node(node->right, key);
	return node;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;
	while (current->left != NULL) // 맨 왼쪽 단말 노드를 찾으러 내려감
		current = current->left;
	return current;
}

TreeNode * delete_node(TreeNode * root, int key)
{
	TreeNode * temp;
	if (root == NULL) return root;
	if (key < root->data.id)
		root->left = delete_node(root->left, key);
	else if (key > root->data.id)
		root->right = delete_node(root->right, key);
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
		temp = min_value_node(root->right);
		root->data = temp->data; 
		root->right = delete_node(root->right, temp->data.id);
	}
	return root;
}

void inorder(TreeNode * root) {
	if (root) {
		inorder(root->left);
		printf("------------------------------\n");
		printf("학번: %d\n", root->data.id);  
		printf("이름: %s\n", root->data.name);  
		printf("전화번호: %s\n", root->data.tel);  
		printf("학과: %d\n", root->data.dept);  
		inorder(root->right);
	}
}

int get_node_count(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + get_node_count(root->left) + get_node_count(root->right);
}

int main(void)
{
	TreeNode *root = NULL;
	TreeNode *temp;
	element stu;
	char ch;
	int id;

	printf("enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
	scanf("%c", &ch);

	while (ch != 'q') {
		switch(ch) {
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
			printf("삭제할 학번 입력: ");
			scanf("%d", &id);
			root = delete_node(root, id);
			break;
		case 's':
			printf("탐색할 학번 입력: ");
			scanf("%d", &id);
			temp = search(root, id);
			if (temp != NULL) {
				printf("------------------------------\n");
				printf("학번: %d\n", temp->data.id);  
				printf("이름: %s\n", temp->data.name);  
				printf("전화번호: %s\n", temp->data.tel);  
				printf("학과: %s\n", temp->data.dept);  
			}
			else
				printf("id가 %d인 학생은 없습니다.\n", id);
			break;
		case 'p':
			printf("학생 정보 학번 순 출력\n");
			inorder(root);
			printf("\n");
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", get_node_count(root));
			break;
		}
		while (getchar() != '\n');
		printf("enter i(nsert), d(elete), s(earch), p(rint), c(ount), q(uit): ");
		scanf("%c", &ch);
	}
}