#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// �ʱ�ȭ �Լ�
void init(HeapType *h)
{
	h->heap_size = 0;
}

// ���� �Լ�: ���� ����� ������ heap_size �� ���� h �� item �� �����Ѵ�.
void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

// ���� �Լ�
element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		if (temp.key >= h->heap[child].key) 
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
} 

void preorder(HeapType *h, int root) // ����
{
	if (root > h->heap_size)
		return;
	else {
		printf("%d ", h->heap[root]); // h->heap[root].key�� �ƴϾ
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
}

int find(HeapType *h, int root, int key) // ����
{	
	if (root > h->heap_size)
		return 0;
	if (h->heap[root].key == key)
		return root;
	else if (h->heap[root].key < key)
		return 0;
	else 
		return max(find(h, root * 2, key), find(h, root * 2 + 1, key));
}

void print_sorted_value(HeapType heap) // ������ �����ϱ� ���� ���ο� ���� ������� �ʿ�x -> �����Ͱ� �ƴ϶� ������ �޾ұ� ����(����) 
{
	int i;
	
	for (i = heap.heap_size; i > 0; i--) 
		printf("%d ", delete_max_heap(&heap).key);
	printf("\n");
}

void print_heap(HeapType *h)
{
	int i, s;

	for (s = 1; s <= h->heap_size; s *= 2) { // s = 1, 2, 4, 8
		for (i = s; i < s * 2; i++) // if s = 4, i = 4, 5, 6, 7 
			printf("%d ", h->heap[i]);
		printf("\n");
	}
}

void modify_priority(HeapType *h, int oldkey, int newkey)
{
	int i, child;

	if (oldkey == newkey) return;
	i = find(h, 1, oldkey);
	if (i == 0) return;

	if (newkey > oldkey) { // upheap, insert_max_heap�� �ڵ�� ����
		while ((i != 1) && (newkey > h->heap[i / 2].key)) {
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
		h->heap[i].key = newkey;
	}
	else { // downheap, delete_max_heap�� �ڵ�� ����
		child = i * 2;

		while (child <= h->heap_size) {
			if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
					child++;
			if (newkey >= h->heap[child].key) 
				break;
			h->heap[i] = h->heap[child];
			i = child;
			child *= 2;
		}
		h->heap[i].key = newkey;
	}
} 

int main(void)
{
	element e1 = {10}, e2 = {5}, e3 = {30}, eA = {9}, eB = {19}, eC = {39};
	element e4, e5, e6;
	int index;
	int key, oldKey, newKey;
	HeapType heap; // ���� ����

	init(&heap); // �ʱ�ȭ

	printf("Step1: ���Ե� 10, 5, 30 �� �߰������� 9, 19, 39 �� <����> �Ѵ�");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	insert_max_heap(&heap, eA);
	insert_max_heap(&heap, eB);
	insert_max_heap(&heap, eC);

	printf("\nStep2: preorder, print_heap �Լ� �׽�Ʈ\n");
	preorder(&heap, 1);
	printf("\n\n");
	print_heap(&heap);

	e4 = delete_max_heap(&heap);
	printf("\n����: ��Ʈ�� ������\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find �Լ� �׽�Ʈ\n");
	printf("ã�� key �Է�(-1 for exit):");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d �� ����\n", key);
		else
			printf("%d �� [%d]�� ����\n", key, index);
		printf("ã�� key �Է�(-1 for exit):");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value �Լ� �׽�Ʈ\n");
	print_sorted_value(heap);

	printf("\nStep5: modify_priority �Լ� �׽�Ʈ\n");
	printf("�ٲ� key �Է�(-1 for exit):");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("�� key �Է�:");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);
		printf("�ٲ� key �Է�(-1 for exit):");
		scanf("%d", &oldKey);
	}
} 

/* 
is_a_relationship 
����Ʈ�� <- ��������Ʈ�� <- heap
��������Ʈ���� ����Ʈ��
heap�� ��������Ʈ��, ����Ʈ��

����Ʈ���� find�Լ��� heap������ ���ư� 
������ heap�� ������ �̿��ؼ� �������ϴ� �� �� ����

����Ʈ���� get_count
heap�� get_count�� �ǹ̰� ����
�̹� count�� heap_size�� �� ���� (�迭�� �����ϱ� ����)

����Ʈ���� �迭, �����ͷ� ���� ����
heap�� �迭�� ����
*/