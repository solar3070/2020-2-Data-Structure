#include <stdio.h>
#include <stdlib.h>

// ���Ŀ� ������ �ʿ��ϸ� ���⸸ �����Ͽ� ���δ�. 
// ===== ���� �ڵ��� ���� ===== 
#define MAX_STACK_SIZE 3
#define MAX_STRING 100

typedef int element;
typedef struct {
	element data;
	char ch[MAX_STRING];
	int top;
} StackType;

StackType stack[MAX_STACK_SIZE];

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType *s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType *s, element item, char *ch)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		stack[++(s->top)].data = item;
		(s->top).ch = ch;
	}
}

// �����Լ�
StackType pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return stack[(s->top)--];
}

// ��ũ�Լ�
StackType peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return stack[s->top];
}
// ===== ���� �ڵ��� �� ===== 

void stack_print(StackType *s)
{
	int i;

	if (is_empty(s)) {
		printf("<empty>\n--\n");
		return;
	}
	
	for (i = s->top; i >= 0; i--) 
		if (i == s->top)
			printf("[%d, %s] <- top\n", stack[i].data, stack[i].ch);
		else
			printf("[%d, %s]\n", stack[i].data, stack[i].ch);
	printf("--\n");
}

int main(void)
{
	StackType s;

	init_stack(&s);

	stack_print(&s);

	push(&s, 10, "ten");
	stack_print(&s);
	push(&s, 20, "twenty");
	stack_print(&s);
	push(&s, 30, "thirty");
	stack_print(&s);
	push(&s, 40, "fourty");
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	push(&s, 50, "fifty");
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
}
