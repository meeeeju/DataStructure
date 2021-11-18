#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct node* nodeptr;
typedef struct node {
	int data;
	nodeptr link;
}node;
void insertTRail(nodeptr* last, int data);   //10 20 30 �־��ָ� 30�̲�����  
void insertFront(nodeptr* last, int data);    //10 20 30 �־��ָ� 10�̲���  30 20 10 �̷���
int length(nodeptr last);           //��� ���� �˷���

int main()
{
	FILE* f;
	int i, size, data;
	nodeptr head, temp, trail, current;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("no file");
		exit(1);
	}

	//header node �ִ� ����
	//temp = (nodeptr)malloc(sizeof(*temp));
	//temp->data = -1;
	//temp->link = NULL;
	//head = temp;
	//trail = head;

	//���� ����
	trail = NULL;


	fscanf(f, "%d", &size);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d", &data);
		insertTRail(&trail, data);
	}
	//current = head;
	current = trail;
	do
	{
		current = current->link;
		printf("%d", current->data);
	} while (current != trail);           //current->data != -1


}

void insertTRail(nodeptr* last, int data)
{
	nodeptr temp;
	temp = (nodeptr)malloc(sizeof(*temp));
	temp->data = data;
	temp->link = NULL;
	if (!(*last))
	{
		*last = temp;
		temp->link = temp;
		//(*last)->link = *last;
	}
	else
	{
		temp->link = (*last)->link;
		(*last)->link = temp;
	}
	*last = (*last)->link;
}

void insertFront(nodeptr* last, int data)
{
	nodeptr temp;
	temp = (nodeptr)malloc(sizeof(*temp));
	temp->data = data;
	temp->link = NULL;
	if (!(*last))
	{
		*last = temp;
		temp->link = temp;
		//(*last)->link = *last;
	}
	else
	{
		temp->link = (*last)->link;
		(*last)->link = temp;
	}

}

int length(nodeptr last)
{
	nodeptr temp;
	int count = 0;
	if (last)
	{
		temp = last;
		do {
			count++;
			temp = temp->link;
		} while (temp != last);
	}
	return count;
}