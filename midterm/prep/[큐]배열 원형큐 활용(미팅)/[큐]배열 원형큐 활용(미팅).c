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
		error("큐가 포화상태입니다\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q)) 
		error("큐가 공백상태입니다\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType *q)
{
	if (is_empty(q)) 
		error("큐가 공백상태입니다\n");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; 
}

int get_count(QueueType *q) // ★원형이라는 걸 잊지 말자
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
		for (i = (q->front + 1) % MAX_QUEUE_SIZE; i <= q->rear; i++) // ★(q->front + 1) % MAX_QUEUE_SIZE
			printf("%s ", q->data[i].name);
	printf("\n");
}

void match(QueueType *q1, QueueType *q2, element item)
{
	if (is_empty(q2)) 
		if (is_full(q1))
			printf("아직 대상자가 없습니다. 대기자가 꽉 찼으니 다음 기회를 이용해주십시오.\n");
		else {
			printf("아직 대상자가 없습니다. 기다려주십시오.\n");
			enqueue(q1, item);
		}
	else {
		enqueue(q1, item);
		printf("커플이 탄생했습니다! %s과 %s\n", q1->data[(q1->front + 1) % MAX_QUEUE_SIZE].name, q2->data[(q2->front + 1) % MAX_QUEUE_SIZE].name); // ★(q->front + 1) % MAX_QUEUE_SIZE
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

	printf("미팅 주선 프로그램입니다.\n");

	printf("i(nsert, 고객 입력), c(heck, 대기자 체크), q(uit): ");
	scanf("%c", &choice);

	while (choice != 'q') {
		if (choice == 'i') {
			printf("이름을 입력: ");
			scanf("%s", newPerson.name);
			printf("성별을 입력(m or f): ");
			scanf(" %c", &gender);

			if (gender == 'm')
				match(&manQ, &womanQ, newPerson);
			else
				match(&womanQ, &manQ, newPerson);
		}
		else {
			printf("남성 대기자 %d명: ", get_count(&manQ));
			print_queue(&manQ);
			printf("여성 대기자 %d명: ", get_count(&womanQ));
			print_queue(&womanQ);
		}
		printf("i(sert, 고객 입력), c(heck, 대기자 체크), q(uit): ");
		scanf(" %c", &choice);
	}
} 