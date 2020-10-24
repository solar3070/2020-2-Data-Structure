#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 5

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size; // ���� ����Ʈ�� ����� �׸��� ����
} ArrayListType;

//���� ó�� �Լ�
void error(char *message)
{ 
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// ����Ʈ �ʱ�ȭ
void init(ArrayListType *L)
{
    L->size = 0;
}
// ����Ʈ�� ��������� 1 ��ȯ, �׷��� ������ 0 ��ȯ
int is_empty(ArrayListType *L)
{
    return L->size == 0;
}
// ����Ʈ�� ���� �� ������ 1 ��ȯ, �׷��� ������ 0 ��ȯ
int is_full(ArrayListType *L)
{
    return L->size == MAX_LIST_SIZE;
}
// �ε����� pos�� �� ��ȯ
element get_entry(ArrayListType *L, int pos)
{
    if (pos < 0 || pos >= L->size)
        error("��ġ ����");
    return L->array[pos];
}
// ����Ʈ ���
void print_list(ArrayListType *L)
{
    int i;
    for (i = 0; i < L->size; i++)
        printf("%d->", L->array[i]);
    printf("����Ʈ��\n");
}
// ���� ����
void insert_last(ArrayListType *L, element item)
{
    if (is_full(L)) // L->size >= MAX_LIST_SIZE
        error("����Ʈ �����÷ο�");
    L->array[L->size++] = item;
}
// pos ��ġ�� ����
void insert_pos(ArrayListType *L, int pos, element item)
{
    int i;
    if (!is_full(L) && (pos >= 0 && pos <= L->size)) {
        for (i = L->size - 1; i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->size++;
    }
	else
		printf("����Ʈ �����÷ο�");
}
// pos ��ġ �� ����, ��ȯ
element delete_pos(ArrayListType *L, int pos)
{
    int i;
	element item;
    if (pos < 0 || pos >= L->size)
        error("��ġ ����");
    item = L->array[pos];
    for (i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    return item;
}

// ���⼭���� ���� �ۼ��� �Լ���

// ����Ʈ ����
void clear(ArrayListType *L) 
{
	L->size = 0;
}
// item�� ����Ʈ�� ù ��° �׸� �߰�
void insert_first(ArrayListType *L, element item)
{
	int i;
	if (is_full(L)) 
		printf("����Ʈ �����÷ο�\n");
	else {
		for (i = L->size - 1; i >= 0; i--)
			L->array[i + 1] = L->array[i];
		L->array[0] = item;
		L->size++;
	}
}
// ����Ʈ�� �׸� �� ��ȯ
int get_length(ArrayListType *L)
{
	return L->size;
}
// pos��° �׸��� item���� �ٲ۴�
void replace(ArrayListType *L, int pos, element item)
{
	if (pos < 0 || pos >= L->size) 
		printf("��ġ ����\n");
	else
		L->array[pos] = item;
}
// item�� ����Ʈ�� ������ 1�� �ƴϸ� 0�� ��ȯ
int is_in_list(ArrayListType *L, element item)
{
	int i;
	for (i = 0; i < L->size; i++)
		if (L->array[i] == item)
			return 1;
	return 0;
}
// ����Ʈ���� key�� �˻� �� ����
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
	ArrayListType list;

	init(&list);
	insert_pos(&list, 0, 20);
	insert_pos(&list, 0, 10); print_list(&list); 
	clear(&list); print_list(&list);

	insert_last(&list, 90); print_list(&list); 

	insert_pos(&list, 0, 30);
	insert_pos(&list, 0, 20);
	insert_pos(&list, 0, 10);

	delete_pos(&list, 2); print_list(&list); 
	
	printf("\n�߰� �Լ� �׽�Ʈ\n"); 
	insert_first(&list, 9); print_list(&list); 
	insert_last(&list, 99); print_list(&list);

	insert_first(&list, 1); print_list(&list); // ����Ʈ �� �� ����

	printf("���̴� %d\n", get_length(&list));
	printf("3��° �����ʹ� %d\n", get_entry(&list, 2));

	replace(&list, 3, 40); print_list(&list); 
	printf("20�� ����Ʈ�� %s\n", is_in_list(&list, 20) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("22�� ����Ʈ�� %s\n", is_in_list(&list, 22) ? "�ֽ��ϴ�" : "�����ϴ�");

	delete_by_key(&list, 20); print_list(&list);
	delete_by_key(&list, 22); print_list(&list);
} 