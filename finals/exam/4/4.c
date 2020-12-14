#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10

int visited[MAX_VERTICES];

typedef struct GraphNode
{  
   int vertex;
   struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}

void insert_edge(GraphType *g, int u, int v) // *방향*그래프에 간선 삽입
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "그래프: 정점 번호 오류");		
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int is_edge_in(GraphType *g, int u, int v) // 이 함수만을 제출
{
	GraphNode *node;
	for (node = g->adj_list[u]; node; node = node->link)
		if (node->vertex == v)
			return 1;
	return 0;
}

int main(void) // 변경하지 말라
{
	GraphType g;
	int u, v;
	int i;

	graph_init(&g);
	scanf("%d", &g.n);
	scanf("%d %d", &u, &v);
	while (u != -1 && v != -1) {
		insert_edge(&g, u, v);
		scanf("%d %d", &u, &v);
	}

	for (i = 0; i < 3; i++) { // 3번 반복
		scanf("%d %d", &u, &v);
		printf("%d\n", is_edge_in(&g, u, v));
	}
}
