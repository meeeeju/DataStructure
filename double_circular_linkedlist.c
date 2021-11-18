#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef enum list { create, insert, delete, inverse }list;


typedef struct element {
	int data;
}element;
typedef struct node* nodepoint;
typedef struct node {
	nodepoint llink;
	element data;
	nodepoint rlink;

}node;

void prinright(nodepoint node, FILE* fp);
void prinleft(nodepoint node, FILE* fp);
void dinsert(nodepoint node, nodepoint newnode);    
void deletee(nodepoint* node, nodepoint deleted);

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

	int size, data, i, j, num = 0;
	char naming[10];

	nodepoint first = NULL, current, del;
	nodepoint newnode;


	fscanf(f, "%d", &size);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%s %d %d", &naming, &data, &num);
		if (strcmp(naming, "create") == 0)
		{
			first = (nodepoint)malloc(sizeof(*first));
			first->data.data = data;
			first->rlink = first;
			first->llink = first;
			prinright(first, stdout);

		}
		if (strcmp(naming, "delete") == 0)
		{
			del = first;
			for (j = 1; j < data; j++)
				del = del->rlink;
			deletee(&first, del);
			prinright(first, stdout);
		}
		if (strcmp(naming, "insert") == 0)
		{
			newnode = (nodepoint)malloc(sizeof(*newnode));
			newnode->data.data = num;
			current = first;
			for (j = 1; j < data; j++)
				current = current->rlink;
			dinsert(current, newnode);
			prinright(first, stdout);

		}
		if (strcmp(naming, "inverse") == 0)
		{
			current = first;
			for (j = 1; j < data; j++)
				current = current->rlink;

			prinleft(current, stdout);

		}
		fprintf(stdout, "\n");

	}


	fclose(f);
	fclose(fp);
}

void dinsert(nodepoint node, nodepoint newnode)
{
	newnode->llink = node;
	newnode->rlink = node->rlink;
	//node->rlink = newnode;     //순서가 매우매우 중요
	//node->rlink->llink = newnode;
	//node->rlink = newnode;
	newnode->llink->rlink = newnode;
	newnode->rlink->llink = newnode;

}
void deletee(nodepoint* node, nodepoint deleted)   //LRR RLL규칙
{
	if (*node == deleted)
	{
		(*node)->rlink->llink = (*node)->llink;
		(*node)->llink->rlink = (*node)->rlink;
		//(*node)->rlink->llink = (*node)->llink;   //순서상관없움 ㅎ
		*node = (*node)->rlink;

	}
	else
	{
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}

}
void prinright(nodepoint node, FILE* fp)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		fprintf(fp, "%3d", node->data);
		node = node->rlink;
	}
}
void prinleft(nodepoint node, FILE* fp)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		fprintf(fp, "%3d", node->data);
		node = node->llink;
	}

}


//테스트값
7
create 10
insert 1 20
insert 2 30
insert 1 40
inverse 3
delete 3
delete 1