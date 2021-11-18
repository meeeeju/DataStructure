//array를 이용한 Hashing!!


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0


unsigned int stringToInt(char* key);  //개중요!!!!
int Hashing(char* key, int bucket);


typedef struct info {
	char name[10];
	int korean;
	int math;
	int eng;
}info;
int main()
{
	FILE* f, * fp;
	int n, b, i, j, hashaddr;   //n 학생  수 b 버켓 수
	info* hashtable;
	info student, student2;
	int* chlist;  //hashtable에 찼는지 안 찼는지 확인시켜줌
	int checknum = 0;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	fopen_s(&fp, "output.txt", "w");
	if (fp == NULL)
	{
		printf("no file opened");
		exit(1);
	}
	fscanf(f, "%d %d", &b, &n);

	hashtable = (info*)calloc(b, sizeof(info));
	chlist = (int*)calloc(b, sizeof(int));

	for (i = 0; i < n; i++)
	{
		fscanf(f, "%s %d %d %d", student.name, &student.korean, &student.math, &student.eng);
		hashaddr = Hashing(student.name, b);
		if (chlist[hashaddr] == FALSE)
		{
			strcpy(hashtable[hashaddr].name, student.name);
			hashtable[hashaddr].korean = student.korean;
			hashtable[hashaddr].math = student.math;
			hashtable[hashaddr].eng = student.eng;
			chlist[hashaddr] = TRUE;
			checknum++;

		}
		else if (checknum < b)
		{
			for (j = 1; j <= b - 1; j++)
			{
				hashaddr = (hashaddr + j) % b;  //이거개중요!!
				if (chlist[hashaddr] == FALSE)
				{
					strcpy(hashtable[hashaddr].name, student.name);
					hashtable[hashaddr].korean = student.korean;
					hashtable[hashaddr].math = student.math;
					hashtable[hashaddr].eng = student.eng;
					chlist[hashaddr] = TRUE;
					checknum++;
					break;
				}
			}
		}
		else
		{
			fprintf(fp, "%s overflow\n", student.name);
		}
	}

	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(f, "%s", student.name);
		hashaddr = Hashing(student.name, b);
		if (strcmp(hashtable[hashaddr].name, student.name) == 0)  //같으면 0 반환!!!
		{
			student2 = hashtable[hashaddr];
			fprintf(fp, "%s %d %d %d\n", student2.name, student2.korean, student2.math, student2.eng);
		}
		else
		{
			for (j = 1; j <= b - 1; j++)
			{
				hashaddr = (hashaddr + j) % b;
				if (strcmp(hashtable[hashaddr].name, student.name) == 0)
				{
					student2 = hashtable[hashaddr];
					fprintf(fp, "%s %d %d %d\n", student2.name, student2.korean, student2.math, student2.eng);
					break;
				}
				else if (hashtable[hashaddr].name == NULL)
				{
					fprintf(fp, "없음\n");
					break;
				}
			}
			if (j == b)
				fprintf(fp, "없음\n");
		}
	}

	fclose(f);
	fclose(fp);
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















