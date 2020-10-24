#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 3

typedef struct {
	char name[20];	
} element;
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
		error("ť�� ��ȭ�����Դϴ�\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q)) 
		error("ť�� ��������Դϴ�\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType *q)
{
	if (is_empty(q)) 
		error("ť�� ��������Դϴ�\n");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; 
}

int get_count(QueueType *q) // �ڿ����̶�� �� ���� ����
{
	if (q->rear >= q->front)
		return q->rear - q->front;
	else
		return MAX_QUEUE_SIZE - (q->front - q->rear);
}

void print_queue(QueueType *q)
{
	int i;
	if (!is_empty(q))
		for (i = (q->front + 1) % MAX_QUEUE_SIZE; i <= q->rear; i++) // ��(q->front + 1) % MAX_QUEUE_SIZE
			printf("%s ", q->data[i].name);
	printf("\n");
}

void match(QueueType *q1, QueueType *q2, element item)
{
	if (is_empty(q2)) 
		if (is_full(q1))
			printf("���� ����ڰ� �����ϴ�. ����ڰ� �� á���� ���� ��ȸ�� �̿����ֽʽÿ�.\n");
		else {
			printf("���� ����ڰ� �����ϴ�. ��ٷ��ֽʽÿ�.\n");
			enqueue(q1, item);
		}
	else {
		enqueue(q1, item);
		printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", q1->data[(q1->front + 1) % MAX_QUEUE_SIZE].name, q2->data[(q2->front + 1) % MAX_QUEUE_SIZE].name); // ��(q->front + 1) % MAX_QUEUE_SIZE
		dequeue(q1);
		dequeue(q2);
	}
}

int main(void)
{
	QueueType manQ, womanQ;
	element newPerson;
	char choice, gender;

	init(&manQ); init(&womanQ);

	printf("���� �ּ� ���α׷��Դϴ�.\n");

	printf("i(nsert, �� �Է�), c(heck, ����� üũ), q(uit): ");
	scanf("%c", &choice);

	while (choice != 'q') {
		if (choice == 'i') {
			printf("�̸��� �Է�: ");
			scanf("%s", newPerson.name);
			printf("������ �Է�(m or f): ");
			scanf(" %c", &gender);

			if (gender == 'm')
				match(&manQ, &womanQ, newPerson);
			else
				match(&womanQ, &manQ, newPerson);
		}
		else {
			printf("���� ����� %d��: ", get_count(&manQ));
			print_queue(&manQ);
			printf("���� ����� %d��: ", get_count(&womanQ));
			print_queue(&womanQ);
		}
		printf("i(sert, �� �Է�), c(heck, ����� üũ), q(uit): ");
		scanf(" %c", &choice);
	}
} 