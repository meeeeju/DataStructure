#include <cstdio>
#define MAX_SIZE 100
typedef struct element {
	int key;
	/*other fields*/

}element;
element stack[MAX_SIZE];
int top = -1;

void push(element item)     /* stack 에서 toop<0 ?  empty, top>=max_size-1 ? full */
{
	if (top >= MAX_SIZE - 1)
		stackFULL();
	stack[++top] = item;
}

void stackFULL()
{
	fprintf(stderr, "stack is full,cannot add element");
	exit(1);
}

int pop()
{
	if (top < 0)
	{
		exit(1);
	}
	else
		return stack[top--].key;
}

elements pop()
{
	if (top < 0)   //if (top==-1)
	{
		exit(1);
	}
	else
		return stack[top--];
}

/*동적 할당  */
/*#define REALLOC(p,s)\
 if (!((p)=realloc(p,s)))\
 { \
fprintf(stderr, "INsufficient memory"); \
exit(1);\
}
/*#define MALLOC(p, s) if (!((p)=malloc(p,s)))\
{\
fprintf(stderr,"insufficient memory");\
exit(1);\
}
*/


typedef struct elements {
	int key;
	/*other fields*/

}elements;
elements *stack;
int capacity = 1;
int top = -1;

int main() {
	stack = (element*)malloc(sizeof(*stack));
}


void push(elements item)     /* stack 에서 toop<0 ?  empty, top>=capacity-1 ? full */
{
	if (top >= capacity- 1)
		stackFULL();
	stack[++top] = item;
}

void stackFULL()   //주의!!
{
	REALLOC(stack, 2 * capacity * sizeof(*stack));
	capacity = 2 * capacity;
}

int pop()
{
	if (top < 0)
	{
		exit(1);
	}
	else
		return stack[top--].key;
}

elements pop()
{
	if (top < 0)
	{
		exit(1);
	}
	else
		return stack[top--];
}

