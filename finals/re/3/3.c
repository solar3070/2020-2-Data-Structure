#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

int is_empty(HeapType *h)
{
	return h->heap_size == 0;
}

void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}

element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int delete_sumUp(HeapType *h) // �� �Լ��� �����ؼ� *����*
{
	element item;
	int sum;
	item = delete_max_heap(h);
	sum = item.key;
	while (!is_empty(h) && item.key == h->heap[1].key) {
		item = delete_max_heap(h);
		sum += item.key;
	}
	return sum;	
}

void preorder(HeapType *h, int root) 
{
     if (h->heap_size < root)
          return;
     else {
          printf("%d ", h->heap[root].key);
          preorder(h, root*2);
          preorder(h, root*2+1);
     }
}

void inorder(HeapType *h, int root) 
{
     if (h->heap_size < root)
          return;
     else {
          inorder(h, root*2);
          printf("%d ", h->heap[root].key);
          inorder(h, root*2+1);
     }
}

void printCheck(HeapType *h) // üũ�� ���� ����Ʈ
{
	preorder(h, 1); printf("üũ1\n");
	inorder(h, 1); printf("üũ2\n");
}

int main(void) //�������� ����
{
	HeapType *h = create();
	element ele;

	init(h);
	scanf("%d", &ele.key);
	while (ele.key != -1) {	
		insert_max_heap(h, ele);
		scanf("%d", &ele.key);
	}
	printf("%d\n", delete_sumUp(h));
	printCheck(h); // ������ �� üũ
}