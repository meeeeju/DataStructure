#define MAX 100/*maximum queue size*/
typedef struct {
	int key;
	/*otherelements*/
}element;
element queues[MAX];
int rear = 0;
int front = 0;
void addque(element item)
{
	/*add an item into queues*/
	rear = (rear + 1)*MAX;   // �ϳ� ���� ����
	if (front == rear)
		queueFULL(); /*print error and exit*/
	queues[rear] = item;
}
element deleteq()
{
	if (front == rear)
	{
		exit(1);
	}
	front = (front + 1) % MAX;  // if �� ���� �ϳ� ����
	return queues[front];
}