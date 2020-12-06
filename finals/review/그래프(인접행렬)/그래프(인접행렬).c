#include <stdio.h>
#include "queue.h"

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int u, v;
	g->n = 0;
	for (u = 0; u < MAX_VERTICES; u++)
		for (v = 0; v < MAX_VERTICES; v++)
			g->adj_mat[u][v] = 0;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType *g, int v)
{
	int u;
	visited[v] = TRUE;
	printf("%d ", v);
	for (u = 0; u < g->n; u++)
		if (g->adj_mat[v][u] && !visited[u]) 
			dfs_mat(g, u);
}

void bfs_mat(GraphType *g, int v)
{
	int u;
	QueueType q;
	init(&q);
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (u = 0; u < g->n; u++)
			if (g->adj_mat[v][u] && !visited[u]) {
				visited[u] = TRUE;
				printf("%d ", u);
				enqueue(&q, u);
			}
	}
}

void visited_init()
{
	int i;
	for (i = 0; i < MAX_VERTICES; i++)
		visited[i] = 0;
}

int main(void)
{
	GraphType g;
	graph_init(&g);

	insert_vertex(&g, 0);
	insert_vertex(&g, 1);
	insert_vertex(&g, 2);
	insert_vertex(&g, 3);

	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 0);
	insert_edge(&g, 0, 2);

	printf("깊이 우선 탐색\n");
	dfs_mat(&g, 0); printf("\n");

	visited_init();
	dfs_mat(&g, 1); printf("\n");

	visited_init();
	dfs_mat(&g, 2); printf("\n");

	visited_init();
	dfs_mat(&g, 3); printf("\n");

	printf("\n넓이 우선 탐색\n");
	visited_init();
	bfs_mat(&g, 0); printf("\n");

	visited_init();
	bfs_mat(&g, 1); printf("\n");

	visited_init();
	bfs_mat(&g, 2); printf("\n");

	visited_init();
	bfs_mat(&g, 3); printf("\n");
}