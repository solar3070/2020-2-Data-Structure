#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode {
	element data;
	struct StackNode *link;
} StackNode;
typedef struct {
	StackNode *top;
} StackType;

void init(StackType *s)
{
	s->top = NULL;
}

int is_empty(StackType *s)
{
	return s->top == NULL;
}

int is_full(StackType *s)
{
	return 0;
}

void push(StackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당 에러\n");
		return;
	}
	else {
		temp->data = item;
		temp->link = s->top;
		s->top = temp;
	}
}

element pop(StackType *s)
{
	StackNode *temp;
	element item;
	if (is_empty(s)) {
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}
	else {
		temp = s->top;
		item = temp->data;
		s->top = temp->link;
		free(temp);
		return item; 
	}
}

element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}
	return s->top->data;
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

	printf("%d\n", is_empty(&s));
}

/*
	StackType *s = (StackType *)malloc(sizeof(StackType));

	init(s);

	push(s, 1);
	push(s, 2);
	push(s, 3);

	printf("%d\n", pop(s));
	printf("%d\n", pop(s));
	printf("%d\n", pop(s));
	printf("%d\n", is_empty(s));
*/