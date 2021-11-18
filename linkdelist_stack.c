typedef struct {
	int key;
}element;
typedef struct stack* stackpointer;
typedef struct  stack {
	element data;
	stackpointer  link;

}stack;
stackpointer top;
void push(element item);
int pop();
void push(element item)
{
	stackpointer temp;
	temp = (stackpointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = top;  //temp가 가장 위에 오게 하고 top이 다시 temp를 가르키게함
	top = temp;
}
int pop()
{
	stackpointer temp = top;
	element item;
	if (!temp)
	{
		return -1;
	}
	item = temp->data;
	top = temp->link;
	free(temp);
	return item.key;
}