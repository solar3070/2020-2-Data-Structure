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

// 초기화 함수
void init(HeapType *h)
{
	h->heap_size = 0;
}

// 삽입 함수: 현재 요소의 개수가 heap_size 인 히프 h 에 item 을 삽입한다.
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

// 삭제 함수
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

void preorder(HeapType *h, int root) // 숙제
{
	if (root > h->heap_size)
		return;
	else {
		printf("%d ", h->heap[root]); // h->heap[root].key가 아니어도
		preorder(h, root * 2);
		preorder(h, root * 2 + 1);
	}
}

int find(HeapType *h, int root, int key) // 숙제
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

void print_sorted_value(HeapType heap) // 원본을 유지하기 위해 새로운 힙을 만들어줄 필요x -> 포인터가 아니라 변수로 받았기 때문(복사) 
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

	if (newkey > oldkey) { // upheap, insert_max_heap의 코드와 유사
		while ((i != 1) && (newkey > h->heap[i / 2].key)) {
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
		h->heap[i].key = newkey;
	}
	else { // downheap, delete_max_heap의 코드와 유사
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
	HeapType heap; // 히프 생성

	init(&heap); // 초기화

	printf("Step1: 삽입된 10, 5, 30 에 추가적으로 9, 19, 39 를 <삽입> 한다");
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
	printf("\n삭제: 루트가 삭제됨\n", e4.key);
	print_heap(&heap);

	printf("\nStep3: find 함수 테스트\n");
	printf("찾을 key 입력(-1 for exit):");
	scanf("%d", &key);
	while (key != -1) {
		if ((index = find(&heap, 1, key)) == 0)
			printf("%d 는 없음\n", key);
		else
			printf("%d 은 [%d]에 있음\n", key, index);
		printf("찾을 key 입력(-1 for exit):");
		scanf("%d", &key);
	}

	printf("\nStep4: print_sorted_value 함수 테스트\n");
	print_sorted_value(heap);

	printf("\nStep5: modify_priority 함수 테스트\n");
	printf("바꿀 key 입력(-1 for exit):");
	scanf("%d", &oldKey);
	while (oldKey != -1) {
		printf("새 key 입력:");
		scanf("%d", &newKey);
		modify_priority(&heap, oldKey, newKey);
		print_heap(&heap);
		printf("바꿀 key 입력(-1 for exit):");
		scanf("%d", &oldKey);
	}
} 

/* 
is_a_relationship 
이진트리 <- 완전이진트리 <- heap
완전이진트리는 이진트리
heap는 완전이진트리, 이진트리

이진트리의 find함수는 heap에서도 돌아감 
하지만 heap의 성질을 이용해서 재정의하는 게 더 좋음

이진트리의 get_count
heap의 get_count는 의미가 없음
이미 count가 heap_size에 들어가 있음 (배열로 구현하기 때문)

이진트리는 배열, 포인터로 구현 가능
heap는 배열로 구현
*/