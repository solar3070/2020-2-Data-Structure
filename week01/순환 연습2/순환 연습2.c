#include <stdio.h>

void print_fact_exp(int n)
{
	if (n == 0 || n == 1)
		printf("1");
	else {
		printf("%d * ", n);
		print_fact_exp(n - 1);
	}
}
/* 교수님 코드 
void print_fact_exp(int n)
{
	if (n > 1) {
		// 출력, n 감소 후 재귀
	}
	else 
		printf("1");
} */
int main(void)
{
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);

	printf("%d! = ", n);
	print_fact_exp(n);
	printf("\n");
}
