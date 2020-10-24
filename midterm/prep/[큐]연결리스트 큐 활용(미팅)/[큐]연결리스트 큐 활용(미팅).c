#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char name [20];
} element;
typedef struct QueueNode {
	element item;
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
		error("�޸𸮸� �Ҵ��� �� �����ϴ�\n");
	else {
		temp->item = item;
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
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q))
		error("ť�� ����ֽ��ϴ�\n");
	else {
		item = temp->item;
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
		error("ť�� ����ֽ��ϴ�\n");
	return q->front->item;
}

int get_count(QueueType *q)
{
	QueueNode *temp = q->front;
	int cnt = 0;
	while (temp != NULL) {
		cnt++;
		temp = temp->link;
	}
	return cnt;
}

void print_queue(QueueType *q)
{
	QueueNode *temp;
	for (temp = q->front; temp != NULL; temp = temp->link)
		printf("%s ", temp->item.name);
	printf("\n");
}

void match(QueueType *q1, QueueType *q2, element item)
{
	if (is_empty(q2)) {
			printf("���� ����ڰ� �����ϴ�. ��ٷ��ֽʽÿ�.\n");
			enqueue(q1, item);
		}
	else {
		enqueue(q1, item);
		printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", q1->front->item.name, q2->front->item.name);
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