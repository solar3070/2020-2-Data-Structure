#include <stdio.h> 
#include <string.h> 
void reverse_string(char *str, int s, int e) 
{
	char temp;

	while (s < e) {
		// str[s]�� str[e]�� �ٲٰ�
		temp = str[s];
		str[s] = str[e];
		str[e] = temp;
		// s�� ������Ű�� e�� ����
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