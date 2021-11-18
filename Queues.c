/*
#define REALLOC(p,s)\
 if (!((p)=realloc(p,s)))\
 { \
fprintf(stderr, "INsufficient memory"); \
exit(1);\
}
#define MALLOC(p, s) if (!((p)=malloc(p,s)))\
{\
fprintf(stderr,"insufficient memory");\
exit(1);\
}
*/


#define MAX 20
typedef struct element{
	int key;
	/*other */
}element;

element queue[MAX];
int rear, front;
int main()
{
	
	rear = -1; front = -1; 

}

void addq(element item)
{
	if (rear == MAX - 1)
	{
		printf("queue is full");
		exit(1);
	}
	queue[++rear] = item;
}
element deleteq()
{
	if (rear == front)
	{
		printf("queue is empty");
		exit(1);
	}
	return queue[++front];
}


//�����ϰ� ���������� ���̴� �����̳� ť�� á���� ���� ��Ű�ų� �����Ҵ����� �޸𸮸� �Ҵ�޴����� ����!
typedef struct {
	int key;
}element;
element *queues;
int rear, front, capacity;

void addq(int item);
element deleteq();
int empty();

int main()
{
	queues = (element*)malloc(sizeof(*queues));
	int capacity = 1;  //Queue size 1
	capacity = 1;
	rear = -1;
	front = -1;  
	


}
void addq(element item)
{
	if (rear >= capacity - 1)
	{
		queues = (element*)realloc(queues, 2 * capacity * sizeof(element));
		capacity *= 2;
	}
	queues[++rear];

}


element deleteq()
{
	if (front == rear)
	{
		printf("queue is empty");
		exit(1);
	}
	return queues[++front];
}
int empty()
{
	if (front == rear)
		return 1;

	return 0;
}
