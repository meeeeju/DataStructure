//stack Ȱ���� epression 3�� (stack and queue)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 100
typedef enum {
	lparen = 0, rparen, plus, minus, times, divide, mod, eos, operand//���� �����൵�� 0�ϰ�쿡��! 
}precedence;

//precedence�� �켱���� �� �˷��ִ¤� �迭
int isp[] = { 0,19,12,12,13,13,13,0 };  //���� ��
int icp[] = { 20,19,12,12,13,13,13,0 }; //���� ��

int stack[MAX];
int top = -1;

/*infix->postfix*/
void printToken(precedence item, int* n, char expr[]);
void postfix(char infix[], char pofix[], int* np);
precedence getToken(char* symbol, int* n, char expr[]);
/*postfix ���*/
int evaluate(char postfix[]);

int pop();
void push(int item);

int main()
{
	FILE* f;

	int i, j, result;
	char expr[20];
	char post_fix[20] = { 0 };
	int np = 0; //infix����
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("������ �� �� �����ϴ�.");
		exit(1);
	}
	fscanf(f, "%s", expr);
	postfix(expr, post_fix, &np);
	post_fix[np] = '\0';

	printf("%s\n", post_fix);
	printf("%d\n", np);

	result = evaluate(post_fix);
	printf("%d", result);

	//char expr[20];
	//expr[0] = 'a';
	//expr[1] = 'b';
	//printf("%s", expr);


}

void push(int item)
{
	if (top >= MAX - 1)
	{
		printf("stack is full");
		exit(1);
	}
	stack[++top] = item;
}
int pop()
{
	if (top == -1)
	{
		printf("stack is empty");
		exit(1);
	}
	return stack[top--];
}
void postfix(char infix[], char pofix[], int* np)
{
	char symbol;

	precedence token;
	int n = 0;

	stack[0] = eos;
	top = 0;
	for (token = getToken(&symbol, &n, infix); token != eos; token = getToken(&symbol, &n, infix))
	{
		if (token == operand)
		{
			//printf("%c", symbol);
			pofix[(*np)++] = symbol;
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
				printToken(pop(), np, pofix);
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				printToken(pop(), np, pofix);
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token, np, pofix);
	printf("\n");
}
precedence getToken(char* symbol, int* n, char expr[])
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;       //  ' ' ��ſ� '\0'���ִ� ���� : \0�� ���ڷ� ����� �ΰ� �ٸ�����
	default: return operand;

	}
}
void printToken(precedence item, int* n, char expr[])   //precedence�� int �� �������
{
	//expr[(*n)++] = '+';
	switch (item)
	{
	case 2: expr[(*n)++] = '+';
		break;
	case 3:  expr[(*n)++] = '-';
		break;
	case 4:  expr[(*n)++] = '*';
		break;
	case 5:  expr[(*n)++] = '/';
		break;
	case 6:  expr[(*n)++] = '%';
		break;
	default: break;

	}
}

int evaluate(char postfix[])
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n, postfix);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');
		else
		{
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus:push(op1 + op2);
				break;
			case minus:push(op1 - op2);
				break;
			case times:push(op1 * op2);
				break;
			case divide:push(op1 / op2);
				break;
			case mod:push(op1 % op2);

			}
		}
		token = getToken(&symbol, &n, postfix);
	}
	return pop();
}      

