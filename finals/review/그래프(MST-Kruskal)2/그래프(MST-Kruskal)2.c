#include <stdio.h>

#define MAX_VERTICES 100

int parent[MAX_VERTICES]; // ������ ���� ������ ��ǥ ������ ����

void set_init(int n) 
{
	int i;
	for (i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int vertex) // ������ �Ű������� ����
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // ��ǥ ������ ã�� ������ �ݺ�, i�� ��ǥ ����
	s = i;
	for (i =  vertex; (p = parent[i]) >= 0; i = p) // ������ ��� ����� ��ǥ ������ s�� ����
		parent[i] = s;
	return s; // ��ǥ ���� ��ȯ
}

void set_union(int s1, int s2)
{
	parent[s2] = s1;
}

#define MAX_ELEMENT 100

typedef struct {
	int key, u, v; // key�� ������ ����ġ
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h) 
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item)
{
	int i = ++(h->heap_size);

	while (i != 1 && item.key < h->heap[i / 2].key) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) 
			child++;
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void insert_heap_edge(HeapType *h, int u, int v, int key)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = key;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h)
{
	insert_heap_edge(h, 0, 1, 10);
	insert_heap_edge(h, 0, 3, 20);
	insert_heap_edge(h, 0, 4, 70);
	insert_heap_edge(h, 1, 2, 50);
	insert_heap_edge(h, 1, 3, 30);
	insert_heap_edge(h, 1, 4, 60);
	insert_heap_edge(h, 2, 4, 40);
	insert_heap_edge(h, 2, 5, 90);
	insert_heap_edge(h, 3, 5, 80);
}

void kruskal(int n) // n�� ���� ����
{
	HeapType h; // �ּ� ����
	element e;
	int edge_accepted = 0; // ���õ� ������ ��
	int uset, vset; // ������ ��ǥ ����

	init(&h); // ���� �ʱ�ȭ
	insert_all_edges(&h);
	set_init(n); // ��ǥ ���� �迭 �ʱ�ȭ

	while (edge_accepted < n - 1) { // 0 1 2 3 4: 5�� �ݺ� (������ �� = n - 1)
		e = delete_min_heap(&h); // ����ġ�� �ּ��� element ����
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) { // ��ǥ ������ �ٸ��ٴ� ���� ���� ���� ������ �ٸ��ٴ� �� = ����Ŭ�� ������ ����
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); // ���� ��ħ
		}
	}
}

int main(void)
{
	kruskal(6); // �μ��� ������ ����
}