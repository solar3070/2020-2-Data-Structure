#include <stdio.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 3
#define MAX_STRING 100

typedef struct {
	char name[MAX_STRING];
	char sex;
} element;

typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
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

// 삽입 함수
int enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		error("아직 대상자가 없습니다. 대기자가 꽉 찼으니 다음 기회를 이용하세요.");
		return 0;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;

	return 1;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

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
		printf("아직 대상자가 없습니다. 기다려주십시오.\n");
	else {
		printf("커플이 탄생했습니다! %s와 %s\n", w->data[w->front + 1].name, m->data[m->front + 1].name);
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

	printf("미팅 주선 프로그램입니다.\n");
	do {
		printf("i<nsert, 고객입력>, c<heck, 대기자 체크>, q<uit>: ");
		scanf("%c", &select);
		while (getchar() != '\n');
		
		switch(select) {
		case 'i': 
			printf("이름을 입력: ");
			scanf("%s", newPerson.name);
			while (getchar() != '\n');
			printf("성별을 입력<m or f>: ");
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
			printf("남성 대기자 %d명: ", get_count(&manQ));
			print_queue(&manQ);
			printf("여성 대기자 %d명: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;
		}
	}while (select != 'q');
}