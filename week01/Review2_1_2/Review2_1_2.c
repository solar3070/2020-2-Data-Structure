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
	Score s1, s2;
	Score *p3;

	s1.midterm = 50;
	s1.final = 100;
	s2.midterm = 70;
	s2.final = 70;

	printScore(&s1);
	printScore(&s2); 

	printf("-----------------------------\n");
	printf("���� ������ ���� ����:\n");
	printScore(biggerScore(&s1, &s2));

	printf("-----------------------------\n");
	printf("�� ������ �� ��:\n");
	printScore(totalScore(&s1, &s2)); 

	printf("-----------------------------\n");
	p3 = createScore(100, 100);
	printScore(p3);
}