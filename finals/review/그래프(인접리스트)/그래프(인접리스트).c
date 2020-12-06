#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int v, int u)
{
	GraphNode *node;
	if (v >= g->n || u >= g->n) {
		fprintf(stderr, "그래프 정점 번호 오류");
		return;
	}

	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = u;
	node->link = g->adj_list[v];
	g->adj_list[v] = node;

	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void dfs_list(GraphType *g, int v)
{
	GraphNode *u;
	visited[v] = TRUE;
	printf("%d ", v);
	for (u = g->adj_list[v]; u; u = u->link)
		if (!visited[u->vertex])
			dfs_list(g, u->vertex);
}

void bfs_list(GraphType *g, int v)
{
	GraphNode *u;
	QueueType q;
	init(&q);
	visited[v] = TRUE;
	printf("%d ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (u = g->adj_list[v]; u; u = u->link) 
			if (!visited[u->vertex]) {
				visited[u->vertex] = TRUE;
				printf("%d ", u->vertex);
				enqueue(&q, u->vertex);
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
	dfs_list(&g, 0); printf("\n");

	visited_init();
	dfs_list(&g, 1); printf("\n");

	visited_init();
	dfs_list(&g, 2); printf("\n");

	visited_init();
	dfs_list(&g, 3); printf("\n");

	printf("\n넓이 우선 탐색\n");
	visited_init();
	bfs_list(&g, 0); printf("\n");

	visited_init();
	bfs_list(&g, 1); printf("\n");

	visited_init();
	bfs_list(&g, 2); printf("\n");
	
	visited_init();
	bfs_list(&g, 3); printf("\n");
}