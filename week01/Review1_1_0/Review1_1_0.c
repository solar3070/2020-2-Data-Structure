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
/* 교수님 코드 
void print_reverse(char *str, int end) 
{
	char tmp;

	printf("%c", str[end]);
	if (end == 0)
		return;
	else
		//코드 추가
} */
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