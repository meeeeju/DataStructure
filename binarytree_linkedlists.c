#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX_Queue 20
#define Max_Stack 20
typedef struct node* treepointer;
typedef struct node
{
	int data;
	treepointer rightchild;
	treepointer leftchild;
};
treepointer queue[MAX_Queue] = { 0 };
int rear = -1; int front = -1;

treepointer stack[Max_Stack];
int top = -1;

void addq(treepointer node);
treepointer deleteq();     //level단계로 traversal 하는 함수,binarytree구현할때 필요


void push(treepointer node);
treepointer pop();

treepointer coopy(treepointer original);   //tree 복사한다.
int equal(treepointer first, treepointer second);   //binartree가 같은지 검사한다

void levelorder(treepointer ptr, FILE* f);

void iterINorer(treepointer node);   //재귀문 쓰지않고 반복문으로 inorder traversal 하는 함수

void inorder(treepointer ptr, FILE* f);
void preorder(treepointer ptr, FILE* f);
void postorder(treepointer ptr, FILE* f);


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
	int* btlist;   //파일에서 데이터 값 읽어와서 저장해둘려고


	treepointer head = NULL;  treepointer temp;   treepointer copy = NULL;

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
	head = temp;
	addq(temp);

	for (i = 1; i < size; i++)
	{

		temp = (treepointer)malloc(sizeof(*temp));
		temp->data = btlist[i];
		temp->leftchild = NULL;
		temp->rightchild = NULL;

		if (queue[front + 1]->leftchild == NULL)
			queue[front + 1]->leftchild = temp;
		//rear=addq(temp,queue,rear);
		else if (queue[front + 1]->rightchild == NULL)
		{
			queue[front + 1]->rightchild = temp;
			if (queue[front + 1]->leftchild->data == -1)      //data=-1일 경우 노드를 끊어준다.
				queue[front + 1]->leftchild = NULL;
			if (queue[front + 1]->rightchild->data == -1)
				queue[front + 1]->rightchild = NULL;
			deleteq();
		}
		addq(temp);

	}
	fclose(f);
	fopen_s(&f, "ouput.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수없습니다.");
		exit(1);
	}
	copy = coopy(head);

	levelorder(copy, f);
	fclose(f);


}

treepointer coopy(treepointer original)
{
	treepointer temp;
	if (original)
	{
		temp = (treepointer)malloc(sizeof(*temp));
		temp->leftchild = coopy(original->leftchild);
		temp->rightchild = coopy(original->rightchild);
		temp->data = original->data;
		return temp;
	}
	return NULL;
}
int equal(treepointer first, treepointer second)
{
	return
		((!first && !second) || (first && second && (first->data == second->data) && equal(first->leftchild, second->leftchild) && equal(first->rightchild, second->rightchild))

			);
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
			fprintf(f, "%3d", ptr->data);
			if (ptr->leftchild)
				addq(ptr->leftchild);
			if (ptr->rightchild)
				addq(ptr->rightchild);
		}

		else
			break;

	}
}
void levelorder(treepointer node)
{
	rear = front = -1;
	if (!node)
		return;
	addq(node);
	for (;;)
	{
		node=deleteq();
		if (node)
		{
			printf("%d", node->data);
			if (node->leftchild)
				addq(node->leftchild);
			if (node->rightchild)
				addq(node->rightchild);
		}
		else
			break;
	}
}
void addq(treepointer node)
{
	if (rear >= MAX_Queue - 1)
		exit(1);
	else
		queue[++rear] = node;

}
treepointer deleteq()
{
	if (front == rear)
		return NULL;  //exit(1)해도 됨,단 level order traversal할때는 NULL로 해줘야된다.
	return queue[++front];
}

void iterINorer(treepointer node)  //stack필요함
{
	for (;;)
	{
		for (; node; node = node->leftchild)
			push(node);
		node = pop();
		if (!node)
			break;
		printf("%3d", node->data);
		node = node->rightchild;

	}
}
void iterinorfer(treepointer node)
{
	for (;;)
	{
		for (; node; node->rightchild)
			push(node);
		node = pop();
		if (!node)
			break;
		printf("%d", node->data);
		node = node->rightchild;
	}
}
void iterinorder(treepointer node)
{
	int i;
	for (;;)
	{
		if (!node)
			return;
		for (; node; node->left)
			push(node);
		node = pop();
		if (!node)
			break;
		printf("%d", node->data);
		node = node->rightchild;

	}




}
void push(treepointer node)
{

	if (top >= Max_Stack)
		exit(1);
	else
		stack[++top] = node;
}
treepointer pop()
{

	if (top == -1)
		return NULL;
	return stack[top--];
}



void inorder(treepointer ptr, FILE* fp)
{
	if (ptr)
	{
		inorder(ptr->leftchild, fp);
		fprintf(fp, "%3d", ptr->data);
		inorder(ptr->rightchild, fp);
	}
}
void preorder(treepointer ptr, FILE* fp)
{
	if (ptr)
	{
		fprintf(fp, "%3d", ptr->data);
		preorder(ptr->leftchild, fp);
		preorder(ptr->rightchild, fp);
	}
}
void postorder(treepointer ptr, FILE* fp)
{
	if (ptr)
	{
		postorder(ptr->leftchild, fp);
		postorder(ptr->rightchild, fp);
		fprintf(fp, "%3d", ptr->data);
	}
}

void inorder(treepointer node)
{
	if (node)
	{
		inorder(node->leftchild);
		printf("%d", node->data);
		inorder(node->rightchild);
	}
}