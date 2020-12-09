#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int previous[MAX_VERTICES];

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int u, v;
	g->n = 0;
	for (u = 0; u < MAX_VERTICES; u++)
		for (v = 0; v < MAX_VERTICES; v++)
			g->weight[u][v] = INF;
}

void read_graph(GraphType *g, char *filename)
{
	int u, v, weight;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "파일 오픈 에러");
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d %d", &u, &v, &weight) != EOF) {
		g->weight[u][v] = weight;
		g->weight[v][u] = weight;
	}

	fclose(fp);
}

int choose(int n)
{
	int i, min = INT_MAX, minpos = -1;

	for (i = 0; i < n; i++)
		if (!found[i] && distance[i] < min) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_path(int s, int u)
{
	if (s == u)
		printf("%d ", u);
	else {
		print_path(s, previous[u]);
		printf("-> %d ", u);
	}
}

int dijkstra(GraphType *g, int s)
{
	int u, v, i;

	for (i = 0; i < g->n; i++) {
		distance[i] = g->weight[s][i];
		previous[i] = s;
	}
	distance[s] = 0;
	found[s] = TRUE;

	for (i = 0; i < g->n-1; i++) {
		u = choose(g->n);
		found[u] = TRUE;

		for (v = 0; v < g->n; v++)
			if (!found[v] && distance[u] + g->weight[u][v] < distance[v]) {
				distance[v] = distance[u] + g->weight[u][v];
				previous[v] = u;
			}

		print_path(s, u);
		printf(" (%d)\n",  distance[u]);
	}
}

int main(void)
{
	GraphType g;
	graph_init(&g);
	read_graph(&g, "input.txt");
	dijkstra(&g, 0);
}