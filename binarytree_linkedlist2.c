//입력한 데이터의 Satisfiability Problem 해결하는 프로그램 논리식을 연산시켜준다.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 30
#define TRUE 1
#define FALSE 0
typedef enum { false, true, not, and, or , nothing, x, y, z } logical;
typedef struct node* treepointer;
typedef struct node {
	logical data;
	short int value;
	treepointer rightchild;
	treepointer leftchild;

}node;
typedef struct combi {
	logical x;
	logical y;
	logical z;
}combi;
treepointer queue[MAX];
int front = -1;
int rear = -1;
int flag = 0;

treepointer deleteq();
void addq(treepointer node);
void inorder(treepointer root, combi logic);
void postordereval(treepointer node);       //논리식계산하는 프로그램
combi combination(int count);

int main()
{

	FILE* f;

	int size, i;
	char btlist[50][10] = { 0 };
	logical* btlist2;
	treepointer head = NULL;  treepointer temp;
	combi c;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}


	fscanf(f, "%d", &size);
	for (i = 0; i < size; i++)
		fscanf(f, "%s", btlist[i]);  //문자열 입력받음
	btlist2 = (logical*)malloc(sizeof(*btlist2) * size);

	fclose(f);
	fopen_s(&f, "output.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	for (i = 0; i < size; i++)
	{
		if (strcmp(btlist[i], "not") == 0)
			btlist2[i] = not;
		if (strcmp(btlist[i], "and") == 0)
			btlist2[i] = and;
		if (strcmp(btlist[i], "or") == 0)
			btlist2[i] = or ;
		if (strcmp(btlist[i], "-1") == 0)
			btlist2[i] = nothing;
		if (strcmp(btlist[i], "x") == 0)
			btlist2[i] = x;
		if (strcmp(btlist[i], "y") == 0)
			btlist2[i] = y;
		if (strcmp(btlist[i], "z") == 0)
			btlist2[i] = z;
	}


	rear = -1; front = -1;
	temp = (treepointer)malloc(sizeof(*temp));
	temp->data = btlist2[0];
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	temp->value = 0;
	head = temp;
	addq(temp);

	for (i = 1; i < size; i++)
	{
		temp = (treepointer)malloc(sizeof(*temp));
		temp->data = btlist2[i];
		temp->value = 0;
		temp->leftchild = NULL;
		temp->rightchild = NULL;

		if (queue[front + 1]->leftchild == NULL)
		{
			queue[front + 1]->leftchild = temp;
		}

		//rear=addq(temp,queue,rear);
		else if (queue[front + 1]->rightchild == NULL)
		{
			queue[front + 1]->rightchild = temp;

			if ((queue[front + 1]->leftchild->data) == nothing)
			{
				queue[front + 1]->leftchild = NULL;
			}

			if ((queue[front + 1]->rightchild->data) == nothing)
			{
				queue[front + 1]->rightchild = NULL;
				//free(temp);
			}
			deleteq();
		}
		addq(temp);

	}
	for (i = 1; i <= 8; i++)
	{
		c = combination(i);
		fprintf(stdout, "%d %d %d: ", c.x, c.y, c.z);
		inorder(head, c);

		postordereval(head);
		fprintf(stdout, "%d\n", head->value);

	}
	c.x = 1; c.y = 1; c.z = 1;
	fprintf(stdout, "%d %d %d: ", c.x, c.y, c.z);
	inorder(head, c);

	postordereval(head);
	fprintf(stdout, "%d\n", head->value);


	fclose(f);



}

combi combination(int count)
{
	int i, j, k;
	int counting = 0;
	combi a;
	for (i = 0; i <= 1; i++)
	{
		for (j = 0; j <= 1; j++)
		{
			for (k = 0; k <= 1; k++)
			{
				counting++;
				if (count == counting)
				{
					a.x = i;
					a.y = j;
					a.z = k;
					return a;
				}
			}
		}
	}
}
void postordereval(treepointer node)
{

	if (node)
	{
		postordereval(node->leftchild);
		postordereval(node->rightchild);
		switch (node->data)
		{
		case not: node->value = !(node->rightchild->value);
			break;
		caseand :  node->value = node->rightchild->value && node->leftchild->value;
			break;
		case or : node->value = node->rightchild->value || node->leftchild->value;
			break;
		case true: node->value = TRUE;
			break;
		case false: node->value = FALSE;
		}


	}



}
void inorder(treepointer root, combi logic)
{

	if (root)
	{
		inorder(root->leftchild, logic);
		if (root->data == x)
		{
			root->data = logic.x;
		}
		if (root->data == y)
		{
			root->data = logic.y;
		}
		if (root->data == z)
		{
			root->data = logic.z;
		}
		inorder(root->rightchild, logic);

	}
}
void addq(treepointer node)
{
	if (rear >= MAX - 1)
		exit(1);
	else
		queue[++rear] = node;

}
treepointer deleteq()
{
	if (front == rear)
		return NULL;
	return queue[++front];
}