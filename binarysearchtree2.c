
//bst delete 하는 함수 구현함!!

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20
#include <stdio.h>
typedef struct bstnode* bstptr;
typedef struct bstnode {
	int data;
	bstptr left;
	bstptr right;
}bstnode;
bstptr queue[MAX_SIZE] = { 0 };
int rear = -1; int front = -1;

void levelorder(bstptr ptr, FILE* fp);
void addq(bstptr node);
bstptr deleteq();

int iter_search(bstptr root, int key);
bstptr Createnode(int data);
bstptr Insert(bstptr root, int data);
void Delete(bstptr root, int data);
int main()
{
	FILE* f, * fp;
	int size, deletesize, data, i, key;
	bstptr root;

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

	root = NULL;
	fscanf(f, "%d %d", &size, &deletesize);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d", &data);
		root = Insert(root, data);

	}
	levelorder(root, fp);
	fprintf(fp, "\n");
	for (i = 0; i < deletesize; i++)
	{
		fscanf(f, "%d", &data);
		if (iter_search(root, data))
		{
			Delete(root, data);
			levelorder(root, fp);
			fprintf(fp, "\n");
		}
		else
			fprintf(fp, "-1\n");
	}
	fclose(f);
	fclose(fp);



}
bstptr Createnode(int data)
{
	bstptr temp;
	temp = (bstptr)malloc(sizeof(*temp));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
bstptr Insert(bstptr root, int data)
{
	if (root == NULL)
	{
		root = Createnode(data);
		return root;
	}
	else if (data <= root->data)
		root->left = Insert(root->left, data);
	else if (data > root->data)
		root->right = Insert(root->right, data);
	return root;
}
void Delete(bstptr root, int data)
{
	bstptr tree, temp, prev = NULL, pr = NULL;
	int flag; //right 2 left 1
	while (root)
	{
		if (data == root->data)
		{
			tree = root;
			if (tree->left)
			{
				temp = tree->left;
				if (temp->right)
				{
					while (temp->right)
					{
						prev = temp;
						temp = temp->right;
					}
					prev->right = NULL;
					tree->data = temp->data;
					free(temp);
					return;
				}
				else
				{
					if (flag == 1)
						pr->left = temp;
					else
						pr->right = temp;
					temp->right = tree->right;

				}
			}
			else if (tree->right)
			{
				temp = tree->right;
				while (temp->left)
				{
					prev = temp;
					temp = temp->left;
				}
				prev->left = NULL;
				tree->data = temp->data;
				free(temp);
				return;
			}
			else
			{//tree의 전 노드를 알아야함
				if (flag == 2)
					pr->right = NULL;
				else
					pr->left = NULL;

				free(tree);
				return;
			}
		}
		if (data < root->data)
		{
			pr = root;
			flag = 1;
			root = root->left;
		}
		else
		{
			pr = root;
			flag = 2;
			root = root->right;
		}

	}
}
int iter_search(bstptr root, int key)
{
	while (root)
	{
		if (key == root->data)
			return root->data;
		if (key < root->data)
		{
			root = root->left;
			if (root == NULL)  
				return NULL;
		}
		if (key > root->data)
		{
			root = root->right;
			if (root == NULL)
				return NULL;
		}

	}
	return NULL;
}
void levelorder(bstptr ptr, FILE* fp)
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
			fprintf(fp, "%3d", ptr->data);
			if (ptr->left)
				addq(ptr->left);
			if (ptr->right)
				addq(ptr->right);
		}

		else
			break;

	}
}
void addq(bstptr node)
{
	if (rear >= MAX_SIZE - 1)
		exit(1);
	else
		queue[++rear] = node;

}
bstptr deleteq()
{
	if (front == rear)
		return NULL;  //exit(1)해도 됨
	return queue[++front];
}
