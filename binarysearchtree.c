#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct bstnode* bstptr;
typedef struct bstnode {
	int data;
	bstptr left;
	bstptr right;

}btnode;

bstptr Createnew(int data);
bstptr Insert(bstptr root, int data);

int iter_search(bstptr root, int key);
int recur_search(bstptr root, int key);

int main()
{
	FILE* f; FILE* fp;
	int size, sizefound, i;
	int filedata = 0, key = 0;
	bstptr root;
	//root = NULL;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("������ �� �� �����ϴ�.");
		exit(1);
	}
	fopen_s(&fp, "ouput.txt", "w");
	if (fp == NULL)
	{
		printf("������ �� �� �����ϴ�.");
		exit(1);
	}

	fscanf(f, "%d %d", &size, &sizefound);
	root = NULL;
	for (i = 1; i <= size; i++)
	{
		fscanf(f, "%d", &filedata);
		root = Insert(root, filedata);
	}

	for (i = 1; i <= sizefound; i++)
	{
		fscanf(f, "%d", &filedata);
		if (search(root, filedata))
			fprintf(fp, "1\n");
		else
			fprintf(fp, "-1\n");
	}
	fclose(f);
	fclose(fp);

}

bstptr Createnew(int data)
{
	bstptr temp;
	temp = (bstptr)malloc(sizeof(*temp));
	temp->data = data;
	temp->right = temp->left = NULL;

	return temp;
}
bstptr Insert(bstptr root, int data)
{
	if (root == NULL)
	{
		root = Createnew(data);
		return root;
	}
	else if (data <= root->data)   //root�� data���� �۴ٸ� ��������
	{
		root->left = Insert(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = Insert(root->right, data);
	}
	return root;
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
			/*if (root == NULL)
				return NULL;*/   // �ڿ� ���� else  ���ָ� �����൵ ��
		}
		else
		{
			root = root->right;
			if (root == NULL)
				return NULL;
		}
	}
	return NULL;
}

int recur_search(bstptr root, int key)
{
	if (!root) return NULL;
	if (key == root->data)
		return root->data;
	if (key < root->data)
		return (recur_search(root->left, key));
	return (recur_search(root->right, key));

}

int iter_search(bstptr root, int key)
{
	while(root)
	{
		if (key == root->data)
			return key;
		else if (key > root->data)
		{
			root = root->right;
		}
		else
			root = root->left;
	}
	return NULL;
}