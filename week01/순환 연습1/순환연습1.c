#include <stdio.h>

int fact(int n)
{
	if (!n)
		return 1;
	else
		return n * fact(n - 1);
}

int main(void)
{
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);

	printf("%d! = ", n);
	printf("%d\n", fact(n));
}
