#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode *link;
} QueueNode;
typedef struct {
	QueueNode *front, *rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType *q)
{
	q->front = q->rear = NULL;
}

int is_empty(QueueType *q)
{
	return q->front == NULL;
}

int is_full(QueueType *q)
{
	return 0;
}

void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL) 
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->data = item;
		temp->link = NULL;
		if (is_empty(q))
			q->front = q->rear = temp;
		else {
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

element dequeue(QueueType *q)
{
	QueueNode *temp;
	element item;
	if (is_empty(q))
		error("ť�� ����ֽ��ϴ�");
	else {
		temp = q->front;
		item = temp->data;
		q->front = temp->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return item;
	}
}

element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ����ֽ��ϴ�");
	else
		return q->front->data;
}

int main(void)
{
	QueueType q;

	init(&q);

	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);

	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));

	printf("%d\n", is_empty(&q));
}