#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
	int num;
	char str[20];
} element;
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
		printf("empty");
		return s->data[s->top];
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

void stack_print(StackType *s)
{
	int i;

	if (is_empty(s))
		printf("<empty>\n");
	else {
		for (i = s->top; i >= 0; i--)
			if (i == s->top)
				printf("[%d, %s] <- top\n", s->data[i].num, s->data[i].str);
			else
				printf("[%d, %s]\n", s->data[i].num, s->data[i].str);
	}
	printf("--\n");
}


int main(void)
{
	StackType s;
	element d, temp;

	init(&s);

	while (1) {
		while(getchar() != '\n');
		scanf("%s", d.str);

		if (strcmp(d.str, "quit") == 0)
			break;
		else if (strcmp(d.str, "process") == 0) {
			temp = pop(&s);
			printf("%s %d\n", temp.str, temp.num);
		}
		else {
			scanf("%d", &d.num);
			push(&s, d);
		}
	}
}