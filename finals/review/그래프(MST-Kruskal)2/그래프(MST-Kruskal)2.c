#include <stdio.h>

#define MAX_VERTICES 100

int parent[MAX_VERTICES]; // 본인이 속한 집합의 대표 정점을 가짐

void set_init(int n) 
{
	int i;
	for (i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int vertex) // 정점을 매개변수로 받음
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); // 대표 정점을 찾을 때까지 반복, i가 대표 정점
	s = i;
	for (i =  vertex; (p = parent[i]) >= 0; i = p) // 집합의 모든 요소의 대표 정점을 s로 설정
		parent[i] = s;
	return s; // 대표 정점 반환
}

void set_union(int s1, int s2)
{
	parent[s2] = s1;
}

#define MAX_ELEMENT 100

typedef struct {
	int key, u, v; // key는 간선의 가중치
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

void kruskal(int n) // n은 정점 개수
{
	HeapType h; // 최소 히프
	element e;
	int edge_accepted = 0; // 선택된 간선의 수
	int uset, vset; // 집합의 대표 정점

	init(&h); // 히프 초기화
	insert_all_edges(&h);
	set_init(n); // 대표 정점 배열 초기화

	while (edge_accepted < n - 1) { // 0 1 2 3 4: 5번 반복 (간선의 수 = n - 1)
		e = delete_min_heap(&h); // 가중치가 최소인 element 받음
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) { // 대표 정점이 다르다는 것은 서로 속한 집합이 다르다는 것 = 사이클이 생기지 않음
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); // 집합 합침
		}
	}
}

int main(void)
{
	kruskal(6); // 인수는 정점의 개수
}