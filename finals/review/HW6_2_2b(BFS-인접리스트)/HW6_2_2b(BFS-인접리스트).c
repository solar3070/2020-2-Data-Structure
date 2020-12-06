#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{  
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES ){ 
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node_u, *node_v;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 정점 번호 오류");
		return;
	}
	node_u = (GraphNode *)malloc(sizeof(GraphNode));
	node_u->vertex = u;
	node_u->link = g->adj_list[v];
	g->adj_list[v] = node_u;

	node_v = (GraphNode *)malloc(sizeof(GraphNode));
	node_v->vertex = v;
	node_v->link = g->adj_list[u];
	g->adj_list[u] = node_v;
}

void bfs_list(GraphType *g, int v) 
{  
	GraphNode *u;
	QueueType q;
	init(&q);    				
	visited[v] = TRUE;      
	enqueue(&q, v);		
	while(!is_empty(&q)) {			
		v = dequeue(&q);	
		for(u = g->adj_list[v]; u; u = u->link) 
			if(!visited[u->vertex]){
				visited[u->vertex] = TRUE;
				printf("(%d %d)\n", v, u->vertex);
				enqueue(&q, u->vertex);	
			}
	}
}

void read_graph(GraphType *g, char *filename)
{
	int u, v;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("file open error!\n");
		return;
	}

	fscanf(fp, "%d", &g->n);
	while (fscanf(fp, "%d %d", &u, &v) != EOF) 
		insert_edge(g, u, v);

	fclose(fp);
}

int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "infile.txt");

	printf("Enter 정점: ");
	scanf("%d", &v);

	bfs_list(&graph, v);
}
