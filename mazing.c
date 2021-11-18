//2장
//미로 찾는 문제
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TRUE 1;
#define FALSE 0
#define MAX 100
typedef struct element
{
	int row;
	int col;
	int dir;
}element;

typedef struct
{
	int vert;
	int hor;
}offsets;

element stack[MAX];
int top = -1;

int n, m;
int** mark, ** maze;

offsets move[8];

void push(element item);
element pop();
void path();

int main()
{
	FILE* f;
	int  i, j;   //dir은 한 position에서의 방향


	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	fscanf(f, "%d %d", &n, &m);

	//makr maze 생성 및 초기화
	maze = (int**)malloc(sizeof(int*) * (n + 2));
	mark = (int**)malloc(sizeof(int*) * (n + 2));
	for (i = 0; i < n + 2; i++)
	{
		maze[i] = (int*)malloc(sizeof(int) * (m + 2));
		mark[i] = (int*)calloc(m + 2, sizeof(int));

	}

	for (i = 0; i < m + 2; i++)
	{
		maze[0][i] = 1;
		maze[n + 1][i] = 1;
		maze[i][0] = 1;
		maze[i][m + 1] = 1;
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			fscanf(f, "%d", &maze[i][j]);
		}
	}

	//방위표 만들어 주기
	move[0].vert = -1; move[0].hor = 0;
	move[1].vert = -1; move[1].hor = 1;
	move[2].vert = 0;  move[2].hor = 1;
	move[3].vert = 1; move[3].hor = 1;
	move[4].vert = 1; move[4].hor = 0;
	move[5].vert = 1;  move[5].hor = -1;
	move[6].vert = 0; move[6].hor = -1;
	move[7].vert = -1; move[7].hor = -1;

	path();


}

void push(element item)
{
	if (top >= MAX - 1)
	{
		printf("스택이 가득 찼습니다.");
		exit(1);
	}
	stack[++top] = item;
}

element pop()
{
	if (top == -1)
	{
		printf("stack is empty");
		exit(1);
	}
	return stack[top--];
}
void path()
{
	element position;
	int row, col, i, nextrow, nextcol, dir, found = FALSE;   //row는 현재 nextrow 는 그다음
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0; //주의 dir 은 현재 방향이 아니라 가야 할 방향
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row; col = position.col;  dir = position.dir;
		while (dir < 8 && !found)
		{
			nextrow = row + move[dir].vert;
			nextcol = col + move[dir].hor;
			if (nextrow == n && nextcol == m)
			{
				found = TRUE;
			}
			else if (!maze[nextrow][nextcol] && !mark[nextrow][nextcol])
			{
				mark[nextrow][nextcol] = 1;
				position.row = nextrow; position.col = nextcol;
				position.dir = ++dir;
				push(position);
				row = nextrow; col = nextcol;  dir = 0;

			}
			else
				dir++;
		}
	}
	if (found)
	{
		printf("the path is : \n");
		printf("row col\n");
		for (i = 0; i <= top; i++)
		{
			printf("%2d %5d\n ", stack[i].row, stack[i].col);

		}
		printf("%2d %5d\n", row, col);
		printf("%2d %5d\n", n, m);
	}
	else
	{
		printf("no path exits");
	}


}