#include <stdio.h>
#include <stdlib.h> 

typedef struct {
	int midterm;
	int final;
} Score;

void printScore(Score *p)
{
	printf("�߰���� ������ %d\n", p->midterm );
	printf("�б⸻��� ������ %d\n", p->final );
}

Score* biggerScore(Score *p1, Score *p2)
{
	int sum1, sum2;

	sum1 = p1->midterm + p1->final;
	sum2 = p2->midterm + p2->final;

	return sum1 > sum2 ? p1 : p2;
}

Score* totalScore(Score *p1, Score *p2) 
{
	Score *sum = (Score*)malloc(sizeof(Score));

	sum->midterm = p1->midterm + p2->midterm;
	sum->final = p1->final + p2->final;

	return sum;
}

Score *createScore(int m, int f)
{
	Score *newP = (Score*)malloc(sizeof(Score));

	newP->midterm = m;
	newP->final = f;

	return newP;
}

int main(void) {
	Score *p1, *p2, *p3;
	p1 = (Score *)malloc(sizeof(Score));
	p2 = (Score *)malloc(sizeof(Score));

	p1->midterm = 50;
	p1->final = 100;
	p2->midterm = 70;
	p2->final = 70;

	printScore(p1);
	printScore(p2); 

	printf("-----------------------------\n");
	printf("���� ������ ���� ����:\n");
	printScore(biggerScore(p1, p2));

	printf("-----------------------------\n");
	printf("�� ������ �� ��:\n");
	printScore(totalScore(p1, p2)); 

	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}