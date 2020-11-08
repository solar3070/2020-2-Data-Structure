#include <stdio.h> 
#include <string.h> 
void print_reverse(char *str, int end) 
{
	printf("%c", str[end]);
	if (end == 0)
		return;
	else 
		print_reverse(str, end - 1);
}

int main()
{
	char str[100]; 

	printf("Enter any string:"); 
	scanf("%s", str);

	printf("Reversed String is: ");
	print_reverse(str, strlen(str) - 1); // str과 마지막 인덱스를 매개변수로 
	printf("\n");
	return 0; 
} 