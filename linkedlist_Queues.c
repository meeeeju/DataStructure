typedef struct {
	int key;
}element;
typedef struct queue* queuepointer;
typedef struct queue {
	element data;
	queuepointer link;
}queue;
queuepointer front, rear;
void addq(element item);
int deleteq();

void addq(element item)
{
	queuepointer temp;
	temp = (queuepointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (!front)
		front = temp;
	else
		rear->link = temp;
	rear = temp;
}
int deleteq()
{
	queuepointer temp = front;
	element item;
	if (!temp)
		return -1;
	item = temp->data;
	front = temp->link;
	free(temp);
	return item.key;

}