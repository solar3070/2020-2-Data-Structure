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

int get_min_vertex(int n)
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

	for (i = 0; i < g->n; i++) { // 모든 정점이 선택될 때까지
		u = get_min_vertex(g->n); // distance가 가장 작은 정점 반환받음
		selected[u] = TRUE; // 신장트리집합에 추가
		printf("정점 %d 추가\n", u);

		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF) // 정점 u와 간선이 있고 (이 조건 없어도 밑에서 걸러짐)
				if (!selected[v] && g->weight[u][v] < distance[v]) // v가 집합에 없고(사이클 방지), u가 추가된 집합에서 v까지의 거리가 기존 집합에서 v까지의 거리보다 작다면  
					distance[v] = g->weight[u][v]; // 집합에서의 v까지의 거리 갱신 (g->weight[u][v]은 u와 v의 거리, distance[v]는 집합에서 v까지의 최소 거리)
	}
} 

int main(void)
{
	GraphType g = { 7, 
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	prim(&g, 0); // 0은 시작점
}