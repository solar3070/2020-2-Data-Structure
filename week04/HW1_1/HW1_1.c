#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 5 // ����Ʈ�� �ִ�ũ��

typedef int element; // �׸��� ����
typedef struct {
	element array[MAX_LIST_SIZE]; // �迭 ����
	int size; // ���� ����Ʈ�� ����� �׸���� ����
} ArrayListType;

// ���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ����Ʈ �ʱ�ȭ �Լ�
void init(ArrayListType *L)
{
	L->size = 0;
}

// ����Ʈ�� ��� ������ 1�� ��ȯ, �׷��� ������ 0�� ��ȯ
int is_empty(ArrayListType *L)
{
	return L->size == 0;
}

// ����Ʈ�� ���� �� ������ 1�� ��ȯ, �׷��� ������ 1�� ��ȯ
int is_full(ArrayListType *L)
{
	return L->size == MAX_LIST_SIZE;
}

// pos��° �׸� ��ȯ
element get_entry(ArrayListType *L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

// ����Ʈ�� �׸� �� ��ȯ
int get_length(ArrayListType *L) 
{
	return L->size;
}

// ����Ʈ ���
void print_list(ArrayListType *L)
{
	int i;
	for (i = 0; i<L->size; i++)
		printf("%d->", L->array[i]);
	printf("����Ʈ ��\n");
}

// item �� ����Ʈ�� ù��° �׸� �߰�
void insert_first(ArrayListType *L, element item)
{
	int i;

	if(L->size >= MAX_LIST_SIZE ) {
		printf("����Ʈ �����÷ο�\n");
		return;
	}
	
	for (i = L->size - 1; i >= 0; i--)
		L->array[i + 1] = L->array[i];
	L->array[0] = item;
	L->size++;
}

// item �� ����Ʈ�� ������ �׸� �߰�
void insert_last(ArrayListType *L, element item)
{
	if(L->size >= MAX_LIST_SIZE ) {
		printf("����Ʈ �����÷ο�\n");
		return;
	}
	L->array[L->size++] = item;
}

// item �� ����Ʈ�� pos ��° �׸� �߰�
void insert(ArrayListType *L, int pos, element item)
{
	int i;
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}

// pos ��° �׸� ����
element delete_pos(ArrayListType *L, int pos)
{
	element item;
	int i;

	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	item = L->array[pos];
	for (i = pos; i<(L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

// ����Ʈ ���
void clear(ArrayListType *L) 
{
	int i;

	for (i = 0; i < L->size; i++)
		L->array[i] = NULL;
	init(L);
}

// pos ��° �׸��� item���� �ٲ� 
void replace(ArrayListType *L, int pos, element item) 
{
	if (pos >= 0 || pos < L->size)
		L->array[pos] = item;
}

// item�� ����Ʈ�� ������ 1�� �ƴϸ� 0 �� ��ȯ 
int is_in_list(ArrayListType *L, element item)
{
	int i;

	for (i = 0; i < L->size; i++)
		if (L->array[i] == item)
			return 1;
	return 0;
}

//����Ʈ���� key �� �˻� �� ����(���� ���� key ���� �������� ù��° key �� ����), key ���� ���� ��� "����" ���
void delete_by_key(ArrayListType *L, element key) 
{
	int i;

	for (i = 0; i < L->size; i++)
		if (L->array[i] == key) {
			delete_pos(L, i);
			return;
		}
	printf("�����Ϸ��� key�� %d�� ����Ʈ�� �����ϴ�\n", key);
}

int main(void)
{
	// ArrayListType�� �������� �����ϰ� ArrayListType�� ����Ű�� �����͸� �Լ��� �Ű������� ����
	ArrayListType list1;

	init(&list1);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	clear(&list1); print_list(&list1);

	insert_last(&list1, 90); print_list(&list1);

	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);

	delete_pos(&list1, 2); print_list(&list1);

	 printf("\n-�� ���Ĵ� HW1_1���� �߰��� �Լ��� �׽�Ʈ-\n");
	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1); 

	// ���� ����Ʈ�� �� ��(ũ�� 5��) �����̹Ƿ� �� �׸��� �� �߰��ϸ� "����Ʈ �����÷ο�" ���
	insert_first(&list1, 1); print_list(&list1); 

	printf("���̴� %d\n", get_length(&list1));
	printf("3��° ����Ÿ�� %d\n", get_entry(&list1, 2)); 
	replace(&list1, 3, 40); print_list(&list1);
	printf("20�� ����Ʈ�� %s\n", is_in_list(&list1, 20) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("22�� ����Ʈ�� %s\n", is_in_list(&list1, 22) ? "�ֽ��ϴ�" : "�����ϴ�"); 

	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1); 

	return 0;
}