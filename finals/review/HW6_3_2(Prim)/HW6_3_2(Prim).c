#include <stdio.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES];
int selected[MAX_VERTICES];
int connected_vertex[MAX_VERTICES]; // distance를 갱신되게 한 정점

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void print_arr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%5d", arr[i]);
	printf("\n");
}

int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!selected[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && distance[i] < distance[v])
			v = i;
	return v;
}

void prim(GraphType *g, int s)
{
	int u, v, i;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
		connected_vertex[u] = s;
	}
	distance[s] = 0;

	for (i = 0; i < g->n; i++) { 
		u = get_min_vertex(g->n);
		selected[u] = TRUE;

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
					connected_vertex[v] = u;
				}
				// connected_vertex[u]는 u의 distance를 바뀌게 한 정점 -> 따라서 distance[u]는 connected_vertex[u]와 u사이의 거리
		printf("\n(%d %d) %d\n", connected_vertex[u], u, distance[u]); // u가 집합에 들어왔으므로 distance[u]는 이제 변하지 않음
		printf("selected[] = \t");
		print_arr(selected, g->n);
		printf("dist[] = \t");
		print_arr(distance, g->n);
	}
}

int main(void)
{
	GraphType g = { 6, 
	{{ 0, 10, INF, 20, 70, INF},
	{ 10,  0, 50, 30, 60, INF},
	{ INF, 50, 0, INF, 40, 90},
	{ 20, 30, INF, 0, INF, 80},
	{ 70, 60, 40, INF, 0, INF},
	{ INF, INF, 90, 80, INF, 0}}
	};
	prim(&g, 0);
	return 0;
}