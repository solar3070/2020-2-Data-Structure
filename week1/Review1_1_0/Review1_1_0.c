#include <stdio.h> 
#include <string.h> 
void print_reverse(char *str, int end) 
{
	if (!end)
		printf("%c", str[end]);
	else {
		printf("%c", str[end]);
		print_reverse(str, end - 1);
	}
} 
/* ������ �ڵ� 
void print_reverse(char *str, int end) 
{
	char tmp;

	printf("%c", str[end]);
	if (end == 0)
		return;
	else
		//�ڵ� �߰�
} */
int main()
{
	char str[100]; 

	printf("Enter any string:"); 
	scanf("%s", str);

	printf("Reversed String is: ");
	print_reverse(str, strlen(str) - 1); // str�� ������ �ε����� �Ű������� 
	printf("\n");
	return 0; 
} 