#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 3
#define MAX_STRING 100

typedef struct {
	int num;
	char eng[MAX_STRING];
} element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

void stack_print(StackType *s)
{
	int i;

	if (is_empty(s)) {
		printf("<empty>\n--\n");
		return;
	}

	for (i = s->top; i >= 0; i--) 
		if (i == s->top)
			printf("[%d, %s] <- top\n", s->data[i].num, s->data[i].eng);
		else
			printf("[%d, %s] \n", s->data[i].num, s->data[i].eng);
	printf("--\n");
}

int main(void)
{
	StackType s;
	element e;

	init_stack(&s);
	stack_print(&s);

	e.num = 10;
	strcpy(e.eng, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.eng, "twenty");
	push(&s, e);
	stack_print(&s);

	e.num = 30;
	strcpy(e.eng, "thity");
	push(&s, e);
	stack_print(&s);

	e.num = 40;
	strcpy(e.eng, "fourty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	e.num = 50;
	strcpy(e.eng, "fifty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
}