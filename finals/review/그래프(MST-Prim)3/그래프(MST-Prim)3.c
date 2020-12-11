#include <stdio.h>

#define MAX_VERTICES 100
#define INF 1000L
#define TRUE 1
#define FALSE 0

int distance[MAX_VERTICES]; // distance[u] = ����Ʈ�����տ��� u������ �ּ� �Ÿ�
int selected[MAX_VERTICES]; // ����Ʈ�� ���տ� �ִ°� ���°�

typedef struct {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int get_min_vertex(int n) // Dijkstra�� choose�Լ�
{
	int i, v;
	for (i = 0; i < n; i++) // v�� �ʱ�ȭ���ִ� �κ�. �����ְ� �ٷ� �Ÿ��� ���� ���� ���� ������
		if (!selected[i]) { // ���õ��� ����(���տ� ����) ���� �ϳ� ���� 
			v = i;
			break;
		}
	for (i = 0; i < n; i++) // ���տ� ������ ������ �� ����ġ�� ���� ���� �ָ� �����ϴ� ����
		if (!selected[i] && distance[i] < distance[v]) // ���õ��� ���� ���� �� ������ ������ ������ �Ÿ����� ���� �Ÿ��� �ִٸ� �װ� ����
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
		printf("���� %d �߰�", u);

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
	prim(&g, 0); // 0�� ������
}