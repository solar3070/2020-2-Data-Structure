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
int previous[MAX_VERTICES]; /* 경유 노드 */

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

void print_path(int start, int end) 
{
	if (start == end)
		printf("%d ", start);
	else {
		print_path(start, previous[end]);
		printf("-> %d ", end);
	}
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start; // 초기화
	}

	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found); // found는 전역변수라 안넣어줘도 되지만 함수의 의미를 더 잘 파악하기 위해
		found[u] = TRUE;
		// printf("%d -> %d(%d)\n", start, u, distance[u]);
		print_path(start, u); // previous는 전역변수라 안넣어줘도 됨 넣어도 상관x
		// if (distance[u] == INF) printf(" (경로 없음)\n");
		//else
		printf(" (%d)\n", distance[u]);

		for (w = 0; w < g->n; w++)
			if (!found[w]) 
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					previous[w] = u;
				}	
	}
}

int main(void)
{
	GraphType g;
	
	graph_init(&g);
	read_graph(&g, "graph.txt");

	shortest_path(&g, 0);
	return 0;
}