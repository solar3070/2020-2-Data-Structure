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
/* ������ �ڵ� 
void print_fact_exp(int n)
{
	if (n > 1) {
		// ���, n ���� �� ���
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
