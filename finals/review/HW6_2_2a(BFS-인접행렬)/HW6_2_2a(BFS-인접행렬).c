#include <stdio.h>
#include "queue.h"

#define MAX_VERTICES 50

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void graph_init(GraphType *g)
{
	int u, v;
	g->n = 0;
	for (u = 0; u < MAX_VERTICES; u++)
		for (v = 0; v < MAX_VERTICES; v++)
			g->adj_mat[u][v] = 0;
}

void read_graph(GraphType *g, char *filename)
{
	int u, v;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d\n", &u, &v) != EOF) {
		g->adj_mat[u][v] = 1;
		g->adj_mat[v][u] = 1;
	}

	fclose(fp);
}

void bfs_mat(GraphType *g, int v) 
{
	int u;
	QueueType q;
	init(&q);
	visited[v] = 1;
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (u = 0; u < g->n; u++)
			if (g->adj_mat[v][u] && !visited[u]) {
				visited[u] = 1;
				printf("(%d %d)\n", v, u);
				enqueue(&q, u);
			}
	}
}

int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "infile.txt");

	printf("Enter Á¤Á¡: ");
	scanf("%d", &v);

	bfs_mat(&graph, v);
}