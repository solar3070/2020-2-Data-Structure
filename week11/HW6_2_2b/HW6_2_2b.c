#include <stdio.h>
#include <stdlib.h>
#include "queue.h"  // <------

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode
{  
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	// ������ ����
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}

// ���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1) > MAX_VERTICES ){ 
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node_u, *node_v;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "�׷���: ���� ��ȣ ����");		
		return;
	}

	node_u = (GraphNode *)malloc(sizeof(GraphNode));
	if (node_u == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����!\n"); return;  
	}
	node_u->vertex = v;
	node_u->link = g->adj_list[u];
	g->adj_list[u] = node_u;

	node_v = (GraphNode *)malloc(sizeof(GraphNode));
	if (node_v == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����!\n"); return;  
	}
	node_v->vertex = u;
	node_v->link = g->adj_list[v];
	g->adj_list[v] = node_v;
}

int visited[MAX_VERTICES];

// �ʺ� �켱 Ž��(���� ����Ʈ)
// �� �ڵ忡 ������ ����ϱ� ���� �ڵ带 �����ϴ� ���� HW6_2_2�� �����̴�
void bfs_list(GraphType *g, int v) 
{  
	GraphNode *w;
	QueueType q;
	init(&q);    				// ť �ʱ� ȭ 
	visited[v] = TRUE;      // ���� v �湮 ǥ�� 
	enqueue(&q, v);			// ���������� ť�� ���� 
	while(!is_empty(&q)){			
		v = dequeue(&q);		// ť�� ����� ���� ���� 
		for(w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
			if(!visited[w->vertex]){	// �̹湮 ���� Ž�� 
				printf("(%d %d)\n", v, w->vertex);
				visited[w->vertex] = TRUE;   // �湮 ǥ��
				enqueue(&q, w->vertex);	//������ ť�� ����
			}
	}
}

void read_graph(GraphType *g, char *filename)
{
	int number, u, v;
	GraphNode *node;
	FILE *fp;
	fp = fopen(filename, "rt");
	if (fp == NULL) 
	{
		printf("file open error!\n");
		return;
	}

	fscanf(fp, "%d\n", &g->n);
	while (fscanf(fp, "%d %d\n", &u, &v) != EOF) 
		insert_edge(g, u, v);

	fclose(fp);
}

int main(void)
{
	GraphType graph;
	int u, v;

	graph_init(&graph);
	read_graph(&graph, "infile.txt");

	printf("Enter ����:");
	scanf("%d", &v);

	bfs_list(&graph, v);
}
