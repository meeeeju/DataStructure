//2장 array이용해서 polynomial 
//polynomials 구현 코드를 참고하여 구조체 배열에 다항식을 입력 받은 후 더한 결과를 출력하는 프로그램//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define max 101
#include <stdlib.h>
#define compare(x,y)(((x)<(y))?-1:((x)==(y))?0:1)
typedef struct {
	float coef; //계수
	int expon;    //차수
}polynomial;
polynomial terms[max];
int avail = 0;
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void attach(float coefficient, int exponent);
int main()
{
	FILE *f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	int n, m, i;
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(f, "%f", &terms[i].coef);
		fscanf(f, "%d", &terms[i].expon);

	}
	fscanf(f, "%d", &m);
	for (; i < n + m; i++)
	{
		fscanf(f, "%f", &terms[i].coef);
		fscanf(f, "%d", &terms[i].expon);
	}
	fclose(f);
	fopen_s(&f, "output.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);

	}
	avail = m + n;
	int startd, finishd;
	padd(0, n - 1, n, n + m - 1, &startd, &finishd);
	//printf("%d", startd);
	//printf("%d", finishd);
	for (i = startd; i <= finishd; i++)
	{
		printf("%.0f %d", terms[i].coef, terms[i].expon);
		fprintf(f, "%.0f %d", terms[i].coef, terms[i].expon);
		fprintf(f, "\n");
		printf("\n");
	}



}
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
	float coeff;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
	{
		switch (compare(terms[starta].expon, terms[startb].expon))
		{
		case -1: attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: coeff = terms[starta].coef + terms[startb].coef;
			if (coeff)
				attach(coeff, terms[startb].expon);
			starta++;
			startb++;
			break;
		case 1: attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}

	}
	for (; starta <= finisha; starta++)
	{
		attach(terms[starta].coef, terms[starta].expon);
	}
	for (; startb <= finishb; startb++)
	{
		attach(terms[startb].coef, terms[startb].expon);
	}
	*finishd = avail - 1;
}
void attach(float coefficient, int exponent)
{
	if (avail >= max)
	{
		fprintf(stdout, "too many terms");
		//exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail].expon = exponent;
	avail++;
}