#include <stdio.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 3
#define MAX_STRING 100

typedef struct {
	char name[MAX_STRING];
	char sex;
} element;

typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
			int i = q->front;
			do {
				i = (i + 1) % (MAX_QUEUE_SIZE);
				printf("%d | ", q->data[i]);
				if (i == q->rear)
					break;
			} while (i != q->front);
		}
	printf("\n");
}

// ���� �Լ�
int enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		error("���� ����ڰ� �����ϴ�. ����ڰ� �� á���� ���� ��ȸ�� �̿��ϼ���.");
		return 0;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;

	return 1;
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

int get_count(QueueType *q)
{
	if (!q->rear)
		return 0;
	else
		return q->rear - q->front;
}

void print_queue(QueueType *q)
{
	int i;

	for (i = q->front + 1; i <= q->rear; i++)
		printf("%s ", q->data[i].name);
	printf("\n");
}

void couple_matching(QueueType *m, QueueType *w)
{
	if (!m->rear || !w->rear)
		printf("���� ����ڰ� �����ϴ�. ��ٷ��ֽʽÿ�.\n");
	else {
		printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", w->data[w->front + 1].name, m->data[m->front + 1].name);
		dequeue(w);
		dequeue(m);
	}
}

int main(void)
{
	QueueType manQ, womanQ;
	element newPerson;
	char select;

	init_queue(&manQ);
	init_queue(&womanQ);

	printf("���� �ּ� ���α׷��Դϴ�.\n");
	do {
		printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>: ");
		scanf("%c", &select);
		while (getchar() != '\n');
		
		switch(select) {
		case 'i': 
			printf("�̸��� �Է�: ");
			scanf("%s", newPerson.name);
			while (getchar() != '\n');
			printf("������ �Է�<m or f>: ");
			scanf("%c", &newPerson.sex);
			while (getchar() != '\n');

			if (newPerson.sex == 'm') {
				if (enqueue(&manQ, newPerson)) 
					couple_matching(&manQ, &womanQ);
			}
			else {
				if (enqueue(&womanQ, newPerson))
					couple_matching(&manQ, &womanQ);
			}
			break;
		case 'c': 
			printf("���� ����� %d��: ", get_count(&manQ));
			print_queue(&manQ);
			printf("���� ����� %d��: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;
		}
	}while (select != 'q');
}