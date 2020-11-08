#include <stdio.h> 
#include <string.h> 
void reverse_string(char *str, int s, int e) 
{
	char temp;

	if (s >= e)
		return;
	else {
		temp = str[s];
		str[s] = str[e];
		str[e] = temp;

		reverse_string(str, s + 1, e - 1);
	}
} 
/* 교수님 코드 
void reverse_string(char *str, int s, int e) 
{
	char tmp;
	if (s >= e) return;
	
	// str[s]와 str[e]를 바꾸고 재귀 부름
} */
int main()
{
	char str[100]; 

	printf("Enter any string:"); 
	scanf("%s", str);

	reverse_string(str, 0, strlen(str) - 1); 
	printf("Reversed String is: %s", str); 
	printf("\n");
	return 0; 
} 