#include <stdio.h>
#define MAX_VERTICES 100

int parent[MAX_VERTICES]; // 본인이 속한 집합의 대표 정점을 가지는 배열
// int num[MAX_VERTICES];

void set_init(int n)
{
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;
//		num[i] = 1;
	}
}

int set_find(int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);
	s = i;
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;
	return s;
}

void set_union(int s1, int s2) 
{
//	if (num[s1] < num[s2]) {
//		parent[s1] = s2;
//		num[s2] += num[s1];
//	}
//	else {
		parent[s2] = s1;
//		num[s1] += num[s2];
//	}
}

#define MAX_ELEMENT 100

typedef struct {
	int key, u, v;
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
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
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

void kruskal(int n)
{
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;

	init(&h);
	insert_all_edges(&h);
	set_init(n);

	while (edge_accepted < n - 1) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);
		if (uset != vset) {
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
}

int main(void)
{
	kruskal(6);
}