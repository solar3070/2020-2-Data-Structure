#include <stdio.h>
#include <stdlib.h>

// 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
// ===== 스택 코드의 시작 ===== 
#define MAX_STRING 100

typedef struct {
	char data[MAX_STRING];
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
	return (s->top == (MAX_STRING - 1));
}

// 삽입함수
void push(StackType *s, char item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
char pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크함수
char peek(StackType *s)
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
			printf("%d <- top\n", s->data[i]);
		else
			printf("%d\n", s->data[i]);
	printf("--\n");
}

int palindrome(char str[])
{
	StackType s;
	int i;

	init_stack(&s);

	for (i = 0; str[i] != '\0'; i++)
		push(&s, str[i]);

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] != pop(&s))
			return 0;
	return 1;
}

int main(void)
{
	char word[MAX_STRING];

	printf("Enter a word to check palindrome: ");
	scanf("%s", word);

	if (palindrome(word))
		printf("palindrome입니다.\n");
	else
		printf("palindrome이 아닙니다.\n");
}
