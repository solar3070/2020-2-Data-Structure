#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000L

typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r<MAX_VERTICES; r++)
		for (c = 0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c] = INF;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int adj_mat)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = adj_mat;
	g->adj_mat[end][start] = adj_mat;
}

// selected���� ���� ���� �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n) // �״�� ����Ѵ�
{
	int v, i;
	for (i = 0; i <n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;
	return (v);
}
//
int prim(GraphType* g, int s, GraphType *t) //������ prim�Լ��� �����Ѵ�. 
{
	int connectedVertex[MAX_VERTICES]; // �ʿ��ϸ� ����Ѵ�.
	int i, u, v;
	int sum = 0;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		connectedVertex[u] = s;
	}
	distance[s] = 0;
	
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;

		for (v = 0; v <g->n; v++)
			if (g->adj_mat[u][v] != INF)
				if (!selected[v] && g->adj_mat[u][v] < distance[v]) {
					distance[v] = g->adj_mat[u][v];
					connectedVertex[v] = u;
				}
	}

	for (v = 0; v <g->n; v++) 
		if (v != s) {
			sum += distance[v];
			insert_edge(t, v, connectedVertex[v], distance[v]);
		}

	return sum;
}

void print_graph(GraphType *t) //�������� ����
{
	int i, j;
	printf("%d\n", t->n);
	for (i = 0; i < t->n; i++)
		for (j = i; j < t->n; j++) 
			if (t->adj_mat[i][j] != INF)
				printf("%d %d %d\n", i, j, t->adj_mat[i][j]);
}
int main(void) //�������� ����
{
	GraphType g, t;
	int u, v, w;
	int start;

	graph_init(&g);
	graph_init(&t);
	
	scanf("%d", &g.n);
	t.n = g.n;
	scanf("%d %d %d", &u, &v, &w);
	while (u != -1) {
		insert_edge(&g, u, v, w);
		scanf("%d %d %d", &u, &v, &w);
	}

	scanf("%d", &start);
	printf("%d\n", prim(&g, start, &t)); // g�� �־��� �׷���, t�� �ּҺ�����Ʈ��
	print_graph(&t);
	return 0;
}
