//sparsematrix로 바꾼후 더하는 함수코드

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define Max 101
#define compare(x,y) ((x)<(y)?0:1)  // 작으면 0 크면1
typedef struct {
	int col;
	int row;
	int value;
}term;
term a[Max];
term b[Max];
term c[Max];
void createarr(term* a, int** b, int row, int col);
int main()
{
	FILE* f;
	int i, j;
	int rown, coln;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.\n");
		exit(1);
	}
	fscanf_s(f, "%d %d", &rown, &coln);
	int** list = (int**)malloc(sizeof(int*) * rown);
	for (i = 0; i < rown; i++)
	{
		list[i] = (int*)malloc(sizeof(int) * coln);
		for (j = 0; j < coln; j++)
		{
			fscanf_s(f, "%d", &list[i][j]);
			//printf("%d", list[i][j]);
		}
	}
	createarr(a, list, rown, coln);
	fscanf_s(f, "%d %d", &rown, &coln);
	int** list1 = (int**)malloc(sizeof(int*) * rown);
	for (i = 0; i < rown; i++)
	{
		list1[i] = (int*)malloc(sizeof(int) * coln);
		for (j = 0; j < coln; j++)
		{
			fscanf_s(f, "%d", &list1[i][j]);
			//printf("%d", list1[i][j]);
		}
	}
	fclose(f);
	createarr(b, list1, rown, coln);
	i = 1; j = 1;
	int  sum = 0; int k = 0; int z;
	while (1)
	{
		if (a[j].row == b[i].row)
		{
			if (a[j].col == b[i].col)
			{
				sum = a[j].value + b[i].value;
				if (sum != 0)
				{
					c[k].row = b[i].row;
					c[k].col = b[i].col;
					c[k].value = sum;
					if ((i == b[0].value) || (j == a[0].value))
					{
						k++;
						break;
					}
					k++;
				}
				i++;
				j++;
			}
			else if (a[j].col > b[i].col)
			{
				c[k].row = b[i].row;
				c[k].col = b[i].col;
				c[k].value = b[i].value;
				if (i == b[0].value)
				{
					k++;
					break;
				}
				k++;
				i++;
			}
			else
			{
				c[k].row = a[j].row;
				c[k].col = a[j].col;
				c[k].value = a[j].value;
				if (j == a[0].value)
				{
					k++;
					break;
				}
				k++;
				j++;
			}
		}
		else if (a[j].row > b[i].row)
		{
			c[k].row = b[i].row;
			c[k].col = b[i].col;
			c[k].value = b[i].value;
			if (i == b[0].value)
			{
				k++;
				break;
			}
			k++;
			i++;
		}
		else
		{
			c[k].row = a[j].row;
			c[k].col = a[j].col;
			c[k].value = a[j].value;
			if (j == a[0].value)
			{
				k++;
				break;
			}
			k++;
			j++;
		}
	}
	//printf("%d", k);
	if (i <= b[0].value)
	{
		for (z = i + 1; z <= b[0].value; z++)
		{
			c[k].row = b[z].row;
			c[k].col = b[z].col;
			c[k].value = b[z].value;
			k++;
		}
	}
	else
	{
		for (z = j + 1; z <= a[0].value; z++)
		{
			c[k].row = a[z].row;
			c[k].col = a[z].col;
			c[k].value = a[z].value;
			k++;
		}
	}
	//printf("%d", k);
	fopen_s(&f, "outputxt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	for (i = 0; i < k; i++)
	{
		fprintf(f, "%d %d %d\n", c[i].row, c[i].col, c[i].value);
		fprintf(stdout, "%d %d %d\n", c[i].row, c[i].col, c[i].value);

	}
	fclose(f);
	free(list);
	free(list1);
}
void createarr(term* a, int** b, int row, int col)
{
	int i, j;
	int k = 1;
	a[0].row = row;
	a[0].col = col;
	for (i = 0; i < a[0].row; i++)
	{
		for (j = 0; j < a[0].col; j++)
		{
			if (b[i][j] != 0)
			{
				a[k].row = i;
				a[k].col = j;
				a[k].value = b[i][j];
				k++;
			}
		}
	}
	a[0].value = k - 1;  //elements의 갯수

}
