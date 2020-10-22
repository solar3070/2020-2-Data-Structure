#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

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
}
// pos ��ġ �� ����, ��ȯ
element delete_pos(ArrayListType *L, int pos)
{
    element i, item;
    if (pos < 0 || pos >= L->size)
        error("��ġ ����");
    item = L->array[pos];
    for (i = pos; i < L->size - 1; i++)
        L->array[i] = L->array[i + 1];
    L->size--;
    return item;
}

int main(void)
{
	// ArrayListType�� �������� �����ϰ� ArrayListType�� ����Ű�� �����͸� �Լ��� �Ű������� ����
	ArrayListType list;

	init(&list);
	insert_pos(&list, 0, 10); print_list(&list); // 0��° ��ġ�� 10 �߰�
	insert_pos(&list, 0, 20); print_list(&list); // 0��° ��ġ�� 20 �߰�
	insert_pos(&list, 0, 30); print_list(&list); // 0��° ��ġ�� 30 �߰�
	insert_last(&list, 40); print_list(&list); // �� ���� 40 �߰�
	delete_pos(&list, 0); print_list(&list); // 0��° �׸� ����
	
	return 0;
} 

/*
���� ���
ArrayListType *list = (ArrayListType *)malloc(sizeof(ArrayListType));

	init(list);
	insert_pos(list, 0, 10); print_list(list); // 0��° ��ġ�� 10 �߰�
	insert_pos(list, 0, 20); print_list(list); // 0��° ��ġ�� 20 �߰�
	insert_pos(list, 0, 30); print_list(list); // 0��° ��ġ�� 30 �߰�
	insert_last(list, 40); print_list(list); // �� ���� 40 �߰�
	delete_pos(list, 0); print_list(list); // 0��° �׸� ����
*/