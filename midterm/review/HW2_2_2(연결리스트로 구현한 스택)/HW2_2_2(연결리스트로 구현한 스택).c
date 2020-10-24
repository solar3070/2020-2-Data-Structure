#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int num;
	char str[20];
} element;
typedef struct StackNode {
	element item;
	struct StackNode *link;
} StackNode;
typedef struct {
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType *s)
{
	return s->top == NULL;
}

int is_full(LinkedStackType *s)
{
	return 0;
}

void push(LinkedStackType *s, element item)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당 에러\n");
		return;
	}
	temp->item = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType *s)
{
	StackNode *temp;
	element item;
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	temp = s->top;
	item = temp->item;
	s->top = temp->link;
	free(temp);
	return item;
}

element peek(LinkedStackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	return s->top->item;
}

void stack_print(LinkedStackType *s)
{
	StackNode *temp;

	if (is_empty(s))
		printf("<empty>\n");
	else {
		temp = s->top;
		while (temp != NULL) {
			if (temp == s->top)
				printf("[%d, %s] <- top\n", temp->item.num, temp->item.str);
			else
				printf("[%d, %s]\n", temp->item.num, temp->item.str);
			temp = temp->link;
		}
	}
	printf("--\n");
}

int main(void)
{
	LinkedStackType s;
	element d;

	init(&s);
	stack_print(&s);
	d.num = 10; strcpy(d.str, "ten");
	push(&s, d);
	stack_print(&s);
	d.num = 20; strcpy(d.str, "twenty");
	push(&s, d);
	stack_print(&s);
	d.num = 30; strcpy(d.str, "thirty");
	push(&s, d);
	stack_print(&s);
	d.num = 40; strcpy(d.str, "fourty");
	push(&s, d);
	stack_print(&s);
	pop(&s);
	d.num = 50; strcpy(d.str, "fifty");
	stack_print(&s);
	push(&s, d);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
}