#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void print_status(GraphType* g)
{
	static int step = 1;
	int i;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("\tfound:    ");
	for (i = 0; i< g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

int choose(int n) // prim의 get_min_vertex와 동일 결과
{
	int i, min = INT_MAX, minpos = -1;
	
	for (i = 0; i < n; i++)
		if (!found[i] && distance[i] < min) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void dijkstra(GraphType *g, int start)
{
	int u, v, i;
	for (i = 0; i < g->n; i++) 
		distance[i] = g->weight[start][i];
	distance[start] = 0; // 어차피 g->weight[start][i]는 0이라서 안써도 결과 나옴
	found[start] = TRUE;

	for (i = 0; i < g->n-1; i++) { // g->n으로 하면 found마지막까지 채워짐
		print_status(g);
		u = choose(g->n);
		found[u] = TRUE;

		for (v = 0; v < g->n; v++)
			if (!found[v])
				if (distance[u] + g->weight[u][v] < distance[v])
					distance[v] = distance[u] + g->weight[u][v];
	}
}

int main(void)
{
	GraphType g = { 7, 
	{{ 0, 7, INF, INF, 3, 10, INF },
	{ 7,  0, 4, 10, 2, 6, INF },
	{ INF, 4, 0, 12, INF, INF, INF },
	{ INF, 10, 12, 0, 11, 9, 4 },
	{ 3, 2, INF, 11, 0, INF, 5 },
	{ 10, 6, INF, 9, INF, 0, INF },
	{ INF, INF, INF, 4, 5, INF, 0 }} 
	};
	dijkstra(&g, 0);
}
/*
GraphType g = { 5, 
	{{ 0, 10, INF, 60, INF},
	{10, 0, 45, 30, 60},
	{INF, 45, 0, 5, 20},
	{60, 30, 5, 0, INF},
	{INF, 60, 20, INF, 0}}
	};
*/