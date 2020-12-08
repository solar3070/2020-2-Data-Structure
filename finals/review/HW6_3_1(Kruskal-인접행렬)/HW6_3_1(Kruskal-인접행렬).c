#include <stdio.h>

#define MAX_VERTICES 100

int parent[MAX_VERTICES];

void set_init(int n) 
{
	int i;
	for (i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p);
	s = i;
	for (i =  vertex; (p = parent[i]) >= 0; i = p) 
		parent[i] = s;
	return s; 
}

void set_union(int s1, int s2)
{
	parent[s2] = s1;
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
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

#define INF 1000L

typedef struct { // 그래프를 인접행렬로 표현
	int n; // 정점 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 간선의 가중치 저장
} GraphType;


void graph_init(GraphType *g)
{
	int u, v;
	g->n = 0;
	for (u = 0; u < MAX_VERTICES; u++)
		for (v = 0; v < MAX_VERTICES; v++)
			g->adj_mat[u][v] = INF;
}

void read_graph(GraphType *g, char *filename)
{
	int u, v, key;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "파일 오픈 에러");
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d %d", &u, &v, &key) != EOF) {
		g->adj_mat[u][v] = key;
		g->adj_mat[v][u] = key;
	}

	fclose(fp);
}

void write_graph(GraphType *g, char *filename)
{
	int u, v;
	FILE *fp;
	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "w");
		if (fp == NULL) {
			fprintf(stderr, "파일 오픈 에러");
			return;
		}
	}
	fprintf(fp, "%d\n", g->n);
	for (u = 0; u < g->n; u++)
		for (v = u; v < g->n; v++)
			if (g->adj_mat[u][v] != INF)
				fprintf(fp, "%d %d %d\n", u, v, g->adj_mat[u][v]);

	fclose(fp);
}

void insert_heap_edge(HeapType *h, int u, int v, int key)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = key;
	insert_min_heap(h, e);
}

void insert_all_edges(HeapType *h, GraphType *g)
{
	int u, v;
	for (u = 0; u < MAX_VERTICES; u++)
		for (v = 0; v < MAX_VERTICES; v++)
			if (g->adj_mat[u][v] != INF) // 간선이 있으면
				insert_heap_edge(h, u, v, g->adj_mat[u][v]);
}

void kruskal(GraphType *g, GraphType *t) 
{
	int edge_accepted = 0; 
	int uset, vset; 
	HeapType h; 
	element e;

	init(&h);
	insert_all_edges(&h, g); // 그래프를 인접행렬로 표현하면서 바뀐 점
	set_init(g->n); 

	printf("선택된 간선(순서대로):\n");
	while (edge_accepted < g->n - 1) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) { 
			printf("(%d, %d) %d\n", e.u, e.v, e.key);

			t->adj_mat[e.u][e.v] = e.key; // g로부터 최소 비용 신장 트리 t만들기
			t->adj_mat[e.v][e.u] = e.key; // g로부터 최소 비용 신장 트리 t만들기

			edge_accepted++;
			set_union(uset, vset); 
		}
	}
}

int main(void)
{
	GraphType g, t;

	graph_init(&g);
	read_graph(&g, "input.txt");

	graph_init(&t);
	t.n = g.n;

	kruskal(&g, &t);
	printf("\n파일로 출력: \n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL); // to stdout
}