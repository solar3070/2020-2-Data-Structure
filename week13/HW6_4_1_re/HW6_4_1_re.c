#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];		/* �湮�� ���� ǥ�� */
int previous[MAX_VERTICES]; /* ���� ��� */

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
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
		previous[i] = start; // �ʱ�ȭ
	}

	found[start] = TRUE;    /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found); // found�� ���������� �ȳ־��൵ ������ �Լ��� �ǹ̸� �� �� �ľ��ϱ� ����
		found[u] = TRUE;
		// printf("%d -> %d(%d)\n", start, u, distance[u]);
		print_path(start, u); // previous�� ���������� �ȳ־��൵ �� �־ ���x
		// if (distance[u] == INF) printf(" (��� ����)\n");
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