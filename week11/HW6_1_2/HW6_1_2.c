#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
typedef int element;
typedef struct GraphNode
{  
   int vertex;
   struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType *g)
{
	int v;
	g->n=0;
	for(v=0;v<MAX_VERTICES;v++)
		g->adj_list[v]=NULL;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node_u, *node_v;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "그래프: 정점 번호 오류");		
		return;
	}

	node_u = (GraphNode *)malloc(sizeof(GraphNode));
	if (node_u == NULL) {
		fprintf(stderr, "메모리 할당 에러!\n"); return;  
	}
	node_u->vertex = v;
	node_u->link = g->adj_list[u];
	g->adj_list[u] = node_u;

	node_v = (GraphNode *)malloc(sizeof(GraphNode));
	if (node_v == NULL) {
		fprintf(stderr, "메모리 할당 에러!\n"); return;  
	}
	node_v->vertex = u;
	node_v->link = g->adj_list[v];
	g->adj_list[v] = node_v;
}

void remove_node(GraphNode **phead, element item) { // 4장 리스트에서 학습한 함수에서 ListNode --> GraphNode로 변경했음
     GraphNode *p, *prevp;
     
     if (*phead == NULL)
          printf("리스트는 비어있습니다.\n");
     else if ((*phead)->vertex == item) {
          p = *phead;
          *phead = (*phead)->link;
          free(p);
     }
     else {
          p = *phead;
          do {
               prevp = p;
               p = p->link;
          }while (p != NULL && p->vertex != item);
          if (p != NULL) {
               prevp->link = p->link;
               free(p);
          }
          else
               printf("%d은 리스트에 없음\n", item);
     }
}
// 간선 삭제 연산, v를 u의 인접 리스트에서 삭제한다.
void delete_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ){
		fprintf(stderr, "그래프: 정점 번호 오류");		
		return;
	}

	node = g->adj_list[u];
	remove_node(&node, v);   
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


void write_graph(GraphType *g, char *filename)
{
     int u;
     FILE *fp;
     GraphNode *ptr;
     
     if (filename == NULL) fp = stdout;
     else {
          fp = fopen(filename, "w");
	     if (fp == NULL) 
	     {
		     printf("file %s open error!\n", filename);
	          return;
	     }
     }
 
	 for (u = 0; u < g->n; u++) {
		 ptr = g->adj_list[u];
		 while (ptr != NULL) {
			 fprintf(fp, "%d->", ptr->vertex);
			 ptr = ptr->link;
		 }
		 fprintf(fp, "end\n");
	 }
	 printf("\n");

     if (filename != NULL) fclose(fp);
}

int main(void)
{
	GraphType g;
	graph_init(&g);

	read_graph(&g, "input.txt");
	write_graph(&g, NULL);	// to stdout

	insert_edge(&g, 1, 3);
	write_graph(&g, NULL);	// to stdout

	delete_edge(&g, 2, 0);
	write_graph(&g, NULL);	// to stdout

	write_graph(&g, "output.txt");
}
