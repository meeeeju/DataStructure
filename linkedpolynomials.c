#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define compare(x,y)(((x)<(y))?-1:((x)==(y))?0:1)

typedef struct polynode* polypointer;
typedef struct polynode {
	int coef;
	int expon;
	polypointer link;
}polynode;
typedef struct poly {
	int coef;
	int expon;
}poly;
polypointer a, b;

void tailinsert(polypointer* first, poly p);
void attach(float coeff, int expon, polypointer* ptr);
polypointer padd();

int main()
{
	FILE* f;
	int size, i = 0; poly p1;
	polypointer c, current, curr;



	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	fscanf(f, "%d", &size);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d %d", &p1.coef, &p1.expon);
		tailinsert(&a, p1);
	}
	fscanf(f, "%d", &size);
	for (i = 0; i < size; i++)
	{
		fscanf(f, "%d %d", &p1.coef, &p1.expon);
		tailinsert(&b, p1);
	}
	fclose(f);

	fopen_s(&f, "ouptut.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}
	c = padd();
	current = c;
	while (current)
	{
		fprintf(f, "%-3d %-3d\n", current->coef, current->expon);
		current = current->link;
	}
	current = c;
	while (current)
	{
		curr = current->link;
		free(current);
		current = curr;
	}
	//메모리 할당해제 해주기;'
	fclose(f);

}


void tailinsert(polypointer* first, poly p) {   //polypointer a,b 삽입!!  
	polypointer  node1;
	polypointer current;
	current = *first;
	node1 = (polypointer)malloc(sizeof(*node1));
	node1->coef = p.coef;
	node1->expon = p.expon;
	node1->link = NULL;
	if (current)
	{
		while (current->link)
			current = current->link;
	}
	if (current)
		current->link = node1;
	else
		*first = node1;
}

polypointer padd()
{
	polypointer c, rear, temp;
	int sum, com;
	rear = (polypointer)malloc(sizeof(*rear));
	c = rear;
	while (a && b)
	{
		com = compare(a->expon, b->expon);
		switch (com)
		{
		case -1: attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0: sum = a->coef + b->coef;
			if (sum)
				attach(sum, a->expon, &rear);
			a = a->link; b = b->link;
			break;
		case 1: attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;

}

void attach(float coeff, int expon, polypointer* ptr)
{
	polypointer temp;
	temp = (polypointer)malloc(sizeof(*temp));
	temp->coef = coeff;
	temp->expon = expon;
	(*ptr)->link = temp;
	*ptr = temp;
}

//함수 해제 시켜줘야함
