#include <stdio.h> 
#include <string.h> 
void reverse_string(char *str, int s, int e) 
{
	char temp;

	while (s < e) {
		// str[s]와 str[e]를 바꾸고
		temp = str[s];
		str[s] = str[e];
		str[e] = temp;
		// s를 증가시키고 e는 감소
		s++;
		e--;
	}
} 

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