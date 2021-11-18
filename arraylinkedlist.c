/*array를 이용한 Singly inked list*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
typedef struct list {
	int index;
	char name[10];
	int next;

}list;
int main()
{
	FILE *f;
	FILE *fp;
	fopen_s(&fp, "output.txt", "w");
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	int size, founder, i, j;
	list arr[20];
	fscanf(f, "%d %d", &size, &founder);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d %s %d", &arr[i].index, arr[i].name, &arr[i].next);
	}

	for (j = 0; j < size; j++)
	{
		if (founder == 0)
			break;
		for (i = 0; i < size; i++)
		{
			if (arr[i].index == founder)
			{
				fprintf(fp, "%s\n", arr[i].name);
				founder = arr[i].next;
				break;
			}
		}

	}
	fclose(f);
	fclose(fp);



}