 //preorder순서로 나며 출력하기열되 문자열과, inorder로 나열도 두 문자열을 입력받아서 
//binary tree를 구성하고 구성된 binary tree를 level order방식으로 순회하기

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#define MAX 20

typedef struct node* treepointer;
struct node {
	char data;
	struct node* left;
	struct node* right;
};
treepointer queue[MAX];
int rear, front;


int search(char arr[], int strt, int end, char value);
struct node* newNode(char data);
struct node* buildTree(char in[], char pre[], int inStrt, int inEnd);
void printInorder(struct node* node);
void levelorder(treepointer ptr, FILE* f);
void addq(treepointer node);
treepointer deleteq();

int main()
{
	FILE* f; FILE* fp;
	char in[MAX];
	char pre[MAX];
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	fopen_s(&fp, "output.txt", "w");
	if (fp == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	fscanf(f, "%s", pre);
	fscanf(f, "%s", in);
	int len = strlen(pre);
	struct node* root = buildTree(in, pre, 0, len - 1);


	levelorder(root, fp);
}


struct node* buildTree(char in[], char pre[], int inStrt, int inEnd)
{
	static int preIndex = 0;

	if (inStrt > inEnd)
		return NULL;

	struct node* tNode = newNode(pre[preIndex++]);

	if (inStrt == inEnd)
		return tNode;

	int inIndex = search(in, inStrt, inEnd, tNode->data);

	tNode->left = buildTree(in, pre, inStrt, inIndex - 1);
	tNode->right = buildTree(in, pre, inIndex + 1, inEnd);

	return tNode;
}


int search(char arr[], int strt, int end, char value)
{
	int i;
	for (i = strt; i <= end; i++) {
		if (arr[i] == value)
			return i;
	}
}

struct node* newNode(char data)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}


void printInorder(struct node* node)
{
	if (node == NULL)
		return;

	printInorder(node->left);
	printf("%c ", node->data);
	printInorder(node->right);
}


void levelorder(treepointer ptr, FILE* f)
{
	rear = -1;
	front = -1;
	if (!ptr)
		return;
	addq(ptr);
	for (;;)
	{
		ptr = deleteq();
		if (ptr)
		{
			fprintf(f, "%3c", ptr->data);
			if (ptr->left)
				addq(ptr->left);
			if (ptr->right)
				addq(ptr->right);
		}

		else
			break;

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
		return NULL;  //exit(1)해도 됨
	return queue[++front];
}