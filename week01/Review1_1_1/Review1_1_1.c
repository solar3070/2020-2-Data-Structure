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
/* ������ �ڵ� 
void reverse_string(char *str, int s, int e) 
{
	char tmp;
	if (s >= e) return;
	
	// str[s]�� str[e]�� �ٲٰ� ��� �θ�
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