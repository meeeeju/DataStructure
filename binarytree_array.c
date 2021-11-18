#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 30

void maketree(int* tree, int size);   //�迭�� �̿��ؼ� tree ����
void printchild(int* tree, int data, int size, FILE* fp);  //tree�� i��° �ε����� �ڽ� ���

//BT��ȸ
void inorder(int* tree, int i, FILE* fp); //lvr  inorder
void preorder(int* tree, int i, FILE* fp);  //vlr preorder
void postorder(int* tree, int i, FILE* fp);   //lrv  postorder

void  iterInorder(int* node, int size, FILE* fp);   //��iterative������� INorder traversal�ϴ� �Լ�
void push(int node);
int pop();

int top = -1;
int stack[MAX];




void maketree(int* tree, int size)
{
	tree = (int*)malloc(sizeof(*tree) * (size + 1));
	tree[0] = -1;
	int array1[] = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i = 1; i <= size; i++)
	{
		tree[i] = array1[i];
	}
}
	
void printchild(int* tree, int data, int size, FILE* fp)
{
	int empty = -1;
	//left child
	if (2 * data <= size)
		fprintf(fp, "%3d", tree[2 * data]);
	else
		fprintf(fp, "%3d", empty);
	//right child
	if ((2 * data + 1) <= size)
		fprintf(fp, "%3d", tree[(2 * data) + 1]);
	else
		fprintf(fp, "%3d", empty);

}

void inorder(int* tree, int i, int size, FILE* fp)  //lvr    
{

	if (i <= size)
	{
		//if (tree[2*i]!=-10000 )
		inorder(tree, 2 * i, size, fp);
		if (tree[i] != -1)
			fprintf(fp, "%3d", tree[i]);
		//if (tree[2 * i+1] != -10000)
		inorder(tree, 2 * i + 1, size, fp);

	}


}
void preorder(int* tree, int i, int size, FILE* fp)
{

	if (i <= size)
	{
		if (tree[i] != -1)
			fprintf(fp, "%3d", tree[i]);
		preorder(tree, 2 * i, size, fp);
		preorder(tree, 2 * i + 1, size, fp);

	}

}
void postorder(int* tree, int i, int size, FILE* fp)
{

	if (i <= size)
	{
		postorder(tree, 2 * i, size, fp);
		postorder(tree, 2 * i + 1, size, fp);
		if (tree[i] != -1)
			fprintf(fp, "%3d", tree[i]);

	}

}
void  iterInorder(int* node, int size, FILE* fp)     //node:tree�迭
{
	top = -1;
	int i = 1, j, data;   //�� ���� root�� 1�̶� i=1���� ����
	int k, empty = -1;
	for (;;)
	{
		for (; i <= size; i = 2 * i)
		{
			if (node[i] != -1)
			{
				push(i);
			}
			else
				break;
		}
		if (top == -1)
			break;
		i = pop();

		printf("%3d", node[i]);

		i = 2 * i + 1;
	}

}
void push(int node)
{
	int i, empty = -1;
	if (top >= MAX)
		exit(1);
	else
		stack[++top] = node;
}
int pop()
{

	if (top == -1)
		exit(1);
	return stack[top--];
}