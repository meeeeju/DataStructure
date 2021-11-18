//chain을 이용한 Hashing
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define TRUE 1
#define FALSE 0
typedef struct info
{
	char name[10];
	int kor;
	int math;
	int eng;
}info;
typedef struct chainnode* chainptr;
typedef struct chainnode
{
	info student;
	chainptr next;
}chainnode;


int Hashing(char* key, int bucket);
unsigned int stringToInt(char* key);
chainptr searching(chainptr* h, char* name, int bucket);
chainptr insertail(chainptr h, info stu);

int main()
{
	FILE* f, * fp;
	int i, j, b, n, hashaddr; //b는 bucket 수,n은 학생 수
	int* checklist;
	info stu;
	chainptr* ht;
	chainptr finder;




	fopen_s(&f, "input.txt", "r");
	fopen_s(&fp, "output.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	fscanf(f, "%d %d", &b, &n);

	ht = (chainptr*)malloc(sizeof(chainptr) * b);
	//checklist=(int*)calloc(b,sizeof(int));
	for (i = 0; i < b; i++)
	{
		ht[i] = NULL;
	}

	for (i = 0; i < n; i++)
	{
		fscanf(f, "%s %d %d %d", stu.name, &stu.kor, &stu.math, &stu.eng);

		hashaddr = Hashing(stu.name, b);

		ht[hashaddr] = insertail(ht[hashaddr], stu);
	}

	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(f, "%s", stu.name);
		finder = searching(ht, stu.name, b);
		fprintf(fp, "%s %d %d %d\n", finder->student.name, finder->student.kor, finder->student.math, finder->student.eng);
	}


}

unsigned int stringToInt(char* key)
{

	int number = 0;
	while (*key)
		number += *key++;
	if (number < 0)
		return -number;
	return number;
}

int Hashing(char* key, int bucket)
{
	int code;
	code = stringToInt(key);
	return code % bucket;
}
chainptr insertail(chainptr h, info stu)
{
	chainptr temp;
	chainptr current;
	current = h;
	temp = (chainptr)malloc(sizeof(*temp));
	strcpy(temp->student.name, stu.name);
	temp->student.kor = stu.kor;
	temp->student.math = stu.math;
	temp->student.eng = stu.eng;
	temp->next = NULL;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = temp;
	}
	else
		h = temp;
	return h;
}
chainptr searching(chainptr* h, char* name, int bucket)
{
	int hashadd;
	chainptr current;
	hashadd = Hashing(name, bucket);
	current = h[hashadd];
	while (current)
	{
		if (strcmp(current->student.name, name) == 0)
			return current;
		current = current->next;
	}
	return NULL;

}