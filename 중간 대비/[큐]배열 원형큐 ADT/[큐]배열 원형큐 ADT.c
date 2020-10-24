#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return q->front == q->rear;
}

int is_full(QueueType *q)
{
	return q->front == (q->rear + 1) % MAX_QUEUE_SIZE;
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q)) 
		error("큐가 포화 상태입니다");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
		q->data[q->rear] = item;
	}
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백 상태입니다");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}

element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백 상태입니다");
	else
		return q->data[q->front];
}

int main(void)
{
	QueueType q;

	init(&q);
	printf("front = %d, rear = %d\n", q.front, q.rear);

	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);

	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));

	printf("%d\n", is_empty(&q));
	printf("front = %d, rear = %d\n", q.front, q.rear);
}