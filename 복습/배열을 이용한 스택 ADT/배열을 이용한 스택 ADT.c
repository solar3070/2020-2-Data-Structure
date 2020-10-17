#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	return s->top == -1;
}

int is_full(StackType *s)
{
	return s->top == MAX_STACK_SIZE - 1;
}

void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void)
{
	StackType s;

	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}

/*
StackType s // 구조체 변수로 선언할 때는
init(&s);
push(&s, 1); // 이렇게 매개변수로 주소값을 보내줌

StackType *s; // 구조체 포인터로 선언할 때는
s = (StackType *)malloc(sizeof(StackType)); // 동적 할당 해줘야 함
init(s);
push(s, 1); // 매개 변수로 그냥 포인터 보내줌
*/
