#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphType {  // �׷����� ������ķ� ǥ���ϱ� 
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r<MAX_VERTICES; r++)
		for (c = 0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	//g->adj_mat[end][start] = 1;
}

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	return (s->top == -1);
}
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

int topo_sort(GraphType *g) // ������ �Լ��� ����: �� �Լ����� ����
{
	int v, i, j;
	StackType s;
	int *in_degree = (int *)malloc(g->n * sizeof(int)); // ���� ����
	
	for (i = 0; i < g->n; i++)
		in_degree[i] = 0; // ���� ���� �ʱ�ȭ
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			if (g->adj_mat[i][j] == 1)
				in_degree[j]++; 

	init(&s);
	for (i = 0; i < g->n; i++)
		if (in_degree[i] == 0) // ���� ������ 0�̸� ���ÿ� ����
			push(&s, i);

	while (!is_empty(&s)) {
		v = pop(&s);
		printf("%d->", v);

		for (i = 0; i < g->n; i++)
			if (g->adj_mat[v][i] == 1) {
				in_degree[i]--; // ���� ���� ����
				if (in_degree[i] == 0)
					push(&s, i);
			}
	}
}

int main(void)
{
	GraphType g;
	int u, v;
	graph_init(&g);
	scanf("%d", &g.n);

	scanf("%d %d", &u, &v);
	while (u != -1) {
		insert_edge(&g, u, v);
		scanf("%d %d", &u, &v);
	}
	topo_sort(&g);
	printf("���ĳ�\n");
}