#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */
int previous[MAX_VERTICES];

void graph_init(GraphType *g)
{
	int i, j;

	g->n = 0;
	for (i = 0; i < MAX_VERTICES; i++)
		for (j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = INF;
}

void read_graph(GraphType *g, char *filename)
{
    int weight, u, v;
	FILE *fp = fopen(filename, "rt");
	if (fp == NULL) 
	{
		printf("file %s open error!\n", filename);
		return;
	}
	
	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d %d", &u, &v, &weight) != EOF) {
		g->weight[u][v] = weight;
		g->weight[v][u] = weight;
	}

	fclose(fp);	

}

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_previous(int previous[], int start, int u) 
{
	if (u == start)
		return;

	print_previous(previous, start, previous[u]);
	printf("%d - > ", previous[u]);
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w]) 
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					previous[w] = u;
				}	
		print_previous(previous, start, u);
		printf("%d (%d)\n", u, distance[u]);
	}
}

int main(void)
{
	GraphType g;
	
	graph_init(&g);
	read_graph(&g, "graph.txt");

	shortest_path(&g, 4);
	return 0;
}