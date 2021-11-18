//winner tree구성함

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1000
typedef struct wintree {
	int key;
	int run;
}wintree;
wintree* winner;
void Winner_tree(int** array, int* runarray, int num_run, int col, FILE* f);
int main()
{
	FILE* f;
	int i, j, size, datanum, data, col;  //size는 run의 갯수 ,datanum은 총 데이터 갯수

	int** array;
	int* runarray;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다,");
		exit(1);
	}

	fscanf(f, "%d %d", &size, &datanum);
	col = datanum / size;
	array = (int**)malloc(sizeof(*array) * size);
	for (i = 0; i < size; i++)
		array[i] = malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < col; j++)
			fscanf(f, "%d", &array[i][j]);
	}

	runarray = (int*)calloc(size, sizeof(int));

	winner = (wintree*)malloc(sizeof(*winner) * size * 2); //그냥 초기화해줌
	for (i = 0; i < 2 * size; i++)
	{
		winner[i].key = 0;
		winner[i].run = 0;
	}

	fclose(f);
	fopen_s(&f, "output.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다,");
		exit(1);
	}

	Winner_tree(array, runarray, size, col, f);
	fclose(f);




}

void Winner_tree(int** array, int* runarray, int num_run, int col, FILE* f)   //col=3
{
	int i, j, k, compare;
	int index;
	for (i = 0; i < num_run; i++)
	{
		if (runarray[i] > col - 1)
			winner[i + num_run].key = MAX;
		else
			winner[i + num_run].key = array[i][runarray[i]];
		winner[i + num_run].run = i;
	}
	i = num_run;
	compare = i / 2;
	while (i > 1)
	{
		for (j = 0; j < compare; j++)
		{
			winner[i / 2] = ((winner[i].key <= winner[i + 1].key) ? winner[i] : winner[i + 1]);
			i = i + 2;
		}
		i = compare;
		compare = compare / 2;

	}
	fprintf(f, "%3d", winner[1].key);
	for (i = 1; i < num_run * col; i++)
	{
		index = winner[1].run;
		runarray[index]++;
		if (runarray[index] > col - 1)
			winner[index + num_run].key = MAX;
		else
			winner[index + num_run].key = array[index][runarray[index]];

		//winner[index + num_run].key = array[index][runarray[index]];
		k = index + num_run;
		while (k > 1)
		{
			if (k % 2 == 0)
				winner[k / 2] = ((winner[k].key <= winner[k + 1].key) ? winner[k] : winner[k + 1]);
			else
				winner[k / 2] = ((winner[k].key <= winner[k - 1].key) ? winner[k] : winner[k - 1]);
			k = k / 2;
		}
		fprintf(f, "%3d", winner[1].key);
	}
}