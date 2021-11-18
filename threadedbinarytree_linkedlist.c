#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
typedef struct node* treepointer;
typedef struct node
{
	int data;

	int leftthread;
	int rightthread;

	treepointer rightchild;
	treepointer leftchild;
};
treepointer queue[MAX_SIZE] = { 0 };
int rear = -1; int front = -1;


treepointer prevnode, lastnode;
int flag = 0;


treepointer deleteq();
void addq(treepointer node);
void inorder(treepointer tree);

void makethread(treepointer node);
void tinorder(treepointer tree);
treepointer insucc(treepointer tree);



int main()
{
	FILE* f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	int size, i;
	int* btlist;
	treepointer head = NULL;  treepointer temp;
	treepointer threadhead;

	fscanf(f, "%d", &size);
	btlist = (int*)malloc(sizeof(*btlist) * size);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d", &btlist[i]);
	}
	temp = (treepointer)malloc(sizeof(*temp));
	temp->data = btlist[0];
	temp->leftchild = NULL;
	temp->rightchild = NULL;
	temp->leftthread = FALSE;
	temp->rightthread = TRUE;
	head = temp;
	addq(temp);

	for (i = 1; i < size; i++)
	{

		temp = (treepointer)malloc(sizeof(*temp));
		temp->data = btlist[i];
		temp->leftchild = NULL;
		temp->rightchild = NULL;
		temp->leftthread = TRUE;
		temp->rightthread = TRUE;

		if (queue[front + 1]->leftchild == NULL)
		{

			queue[front + 1]->leftthread = FALSE;
			queue[front + 1]->rightthread = FALSE;
			queue[front + 1]->leftchild = temp;
		}
		//rear=addq(temp,queue,rear);
		else if (queue[front + 1]->rightchild == NULL)
		{
			queue[front + 1]->leftthread = FALSE;
			queue[front + 1]->rightthread = FALSE;
			queue[front + 1]->rightchild = temp;

			if (queue[front + 1]->leftchild->data == -1)
			{
				queue[front + 1]->leftchild = NULL;
				queue[front + 1]->leftthread = TRUE;
			}

			if (queue[front + 1]->rightchild->data == -1)
			{
				queue[front + 1]->rightchild = NULL;
				queue[front + 1]->rightthread = TRUE;
			}


			deleteq();
		}
		addq(temp);
	}
	//inorder(head);
	threadhead = (treepointer)malloc(sizeof(*threadhead));
	threadhead->data = -1;
	threadhead->leftchild = head;
	threadhead->rightchild = NULL;
	threadhead->leftthread = FALSE;
	threadhead->rightthread = FALSE;

	prevnode = threadhead;
	makethread(threadhead);
	threadhead->rightthread = FALSE;
	threadhead->rightchild = threadhead;
	tinorder(threadhead);



}

//void inorder(treepointer tree)
//{
//	if (tree)
//	{
//		inorder(tree->leftchild);
//		if (tree->data != -1)
//			printf( "%3d", tree->data);
//
//		inorder(tree->rightchild);
//	}
//}
void addq(treepointer node)
{
	if (rear >= MAX_SIZE - 1)
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
void makethread(treepointer node)
{

	if (node)
	{
		makethread(node->leftchild);

		if (flag == 1)
		{
			prevnode->rightchild = node;
			flag = 0;
			prevnode = node;
		}

		if (node->leftchild == NULL)
		{
			node->leftchild = prevnode;
			node->leftthread = TRUE;

		}
		if (node->rightchild == NULL)
		{
			node->rightthread = TRUE;
			flag = 1;
			prevnode = node;
		}
		lastnode = node;
		makethread(node->rightchild);
	}
}
void tinorder(treepointer tree)
{
	treepointer temp = tree;
	for (;;)
	{
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3d", temp->data);

	}
}
treepointer insucc(treepointer tree)
{
	treepointer temp;
	temp = tree->rightchild;
	if (!tree->rightthread)
	{
		while (!temp->leftthread)
			temp = temp->leftchild;
	}
	return temp;
}