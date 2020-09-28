#include <stdio.h> 
#include <string.h> 
void reverse_string(char *str, int s, int e) 
{
	int i, temp;

	for (i = s; i <= (e - s) / 2; i++) {
		temp = str[i];
		str[i] = str[e - i];
		str[e - i] = temp;
	}
} 
/* 교수님 코드 
void reverse_string(char *str, int s, int e) 
{
	char temp;

	while (s < e) {
		// str[s]와 str[e]를 바꾸고
		// s를 증가시키고 e는 감소
	}
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