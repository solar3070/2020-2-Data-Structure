#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_ELEMENT 200

typedef struct {
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h) 
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item)
{
	int i = ++(h->heap_size);

	while (i != 1 && item.key > h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];

	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void preorder(HeapType *h, int root)
{
	if (root <= h->heap_size) {
		printf("%d ", h->heap[root].key);
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
}

void print_heap(HeapType *h) // 교수님 코드도 참고 (맨 밑 주석)
{
	int i, lf = 2;
	for (i = 1; i <= h->heap_size; i++) {
		if (lf == i) {
			printf("\n");
			lf *= 2;
		}
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

int find(HeapType *h, int root, int key)
{
	if (root > h->heap_size)
		return 0;
	if (h->heap[root].key == key)
		return root;
	if (h->heap[root].key < key)
		return 0;
	else
		return MAX(find(h, root * 2, key), find(h, root * 2 + 1, key));
}

void print_sorted_value(HeapType heap)
{
	int i;
	for (i = heap.heap_size; i >= 1; i--)
		printf("%d ", delete_max_heap(&heap).key);
	printf("\n");
}

void modify_priority(HeapType *h, int oldkey, int newkey)
{
	int i, child;
	if (oldkey == newkey) return;
	i = find(h, 1, oldkey);
	if (i == 0) return;

	if (newkey > oldkey) 
		while (i != 1 && newkey > h->heap[i / 2].key) {
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
	else {
		child = i * 2;
		while (child <= h->heap_size) {
			if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key)
				child++;
			if (newkey >= h->heap[child].key) break;
			h->heap[i] = h->heap[child];
			i = child;
			child *= 2;
		}
	}
	h->heap[i].key = newkey;

}

int main(void)
{
	element e1 = {10}, e2 = {5}, e3 = {30}, eA = {9}, eB = {19}, eC = {39};
	element e4, e5, e6;
	int index;
	int key, oldKey, newKey;
	HeapType heap;

	init(&heap);

	printf("Step1: 삽입된 10, 5, 30에 추가적으로 9, 19, 39를 <삽입>한다\n");
	insert_max_heap(&heap, e1);
	insert_max_heap(&heap, e2);
	insert_max_heap(&heap, e3);
	insert_max_heap(&heap, eA);
	insert_max_heap(&heap, eB);
	insert_max_heap(&heap, eC);

	printf("\nStep2: preorder, print_heap 함수 테스트\n");
	preorder(&heap, 1);
	printf("\n\n");
	print_heap(&heap);

	e4 = delete_max_heap(&heap);
	printf("\n삭제: %d 루트가 삭제됨\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find 함수 테스트\n");
	printf("찾을 key 입력(-1 for exit): ");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d는 없음\n", key);
		else
			printf("%d은 [%d]에 있음\n", key, index);

		printf("찾을 key 입력(-1 for exit): ");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value 함수 테스트\n");
	print_sorted_value(heap);

	printf("\nStep5: modify_priority 함수 테스트\n");
	printf("바꿀 key 입력(-1 for exit): ");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("새 key 입력: ");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);

		printf("바꿀 key 입력(-1 for exit): ");
		scanf("%d", &oldKey);
	}
}

/*
void print_heap(HeapType *h)
{
	int i, s;

	for (s = 1; s <= h->heap_size; s *= 2) { // s = 1, 2, 4, 8
		for (i = s; i < s * 2; i++) // if s = 4, i = 4, 5, 6, 7 
			printf("%d ", h->heap[i]);
		printf("\n");
	}
}
*/