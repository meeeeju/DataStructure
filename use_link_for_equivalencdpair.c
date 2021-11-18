#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct node* nodepoint;
typedef struct node {
	int data;
	nodepoint link;
}node;
void initialize(nodepoint* seq, int* out, int size);
void inputequivalence(nodepoint art[], int out[], int size, FILE* fp);

int main()
{
	FILE* f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	FILE* fp;
	fopen_s(&fp, "output.txt", "w");
	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	int size, pairs, i, j, k;
	nodepoint* seq;
	int* out;
	nodepoint x;

	fscanf(f, "%d %d", &size, &pairs);
	seq = (nodepoint*)malloc(sizeof(nodepoint) * size);
	out = (int*)malloc(sizeof(int) * size);
	initialize(seq, out, size);

	for (k = 0; k < pairs; k++)
	{
		fscanf(f, "%d %d", &i, &j);
		x = (nodepoint)malloc(sizeof(*x));
		x->data = j; x->link = seq[i]; seq[i] = x;
		x = (nodepoint)malloc(sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;

	}

	inputequivalence(seq, out, size, fp);

	fclose(f);
	fclose(fp);


}

void initialize(nodepoint* seq, int* out, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		out[i] = true;
		seq[i] = NULL;
	}
}

void inputequivalence(nodepoint* art, int* out, int size, FILE* fp)
{
	int i, j;
	nodepoint x, top, y;
	for (i = 0; i < size; i++)
	{
		if (out[i])
		{
			fprintf(fp, "\n %3d", i);
			out[i] = false;
			x = art[i]; top = NULL;
			for (;;)
			{
				while (x)
				{
					j = x->data;
					if (out[j])
					{
						fprintf(fp, "%3d", j); out[j] = false;
						y = x->link;
						x->link = top; top = x;
						x = y;
					}
					else
						x = x->link;
				}
				if (!top) break;
				x = art[top->data]; top = top->link;
			}
		}
	}
}

//input 값

12 9   //12전체 정수의 개수, 9개의 쌍
0 4
3 1
6 10
8 9
7 4
6 8
3 5
2 11
11 0