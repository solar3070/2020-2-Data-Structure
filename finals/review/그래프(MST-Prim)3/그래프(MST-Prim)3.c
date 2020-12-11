#include <stdio.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES]; // distance[u] = 신장트리집합에서 u까지의 최소 거리
int selected[MAX_VERTICES]; // 신장트리 집합에 있는가 없는가

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int get_min_vertex(int n) // Dijkstra의 choose함수
{
	int i, v;
	for (i = 0; i < n; i++) // v를 초기화해주는 부분. 안해주고 바로 거리를 비교할 수는 없기 때문에
		if (!selected[i]) { // 선택되지 않은(집합에 없는) 정점 하나 선택 
			v = i;
			break;
		}
	for (i = 0; i < n; i++) // 집합에 인접한 정점들 중 가중치가 가장 작은 애를 선택하는 과정
		if (!selected[i] && distance[i] < distance[v]) // 선택되지 않은 정점 중 위에서 선택한 정점의 거리보다 작은 거리가 있다면 그걸 선택
			v = i; 
	return v;
}

void prim(GraphType *g, int s)
{
	int u, v, i;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		printf("정점 %d 추가", u);

		for (v = 0; v < g->n; v++)
			if (!selected[v] && g->weight[u][v] < distance[v])
				distance[v] = g->weight[u][v];
	}
} 

int main(void)
{
	/*
	GraphType g = { 7, 
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};*/
	GraphType g = { 7, 
	{{ 0, 14, INF, INF, INF, 5, 9 },
	{ 14,  0, 11, INF, INF, INF, 2 },
	{ INF, 11, 0, 4, INF, INF, 13 },
	{ INF, INF, 4, 0, 8, INF, 10 },
	{ INF, INF, INF, 8, 0, 12, 3 },
	{ 5, INF, INF, INF, 12, 0, 7 },
	{ 9, 2, 13, 10, 3, 7, 0 } }
	};
	prim(&g, 0); // 0은 시작점
}