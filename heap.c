//작성한 코드는 Max_heap 기준이다.
//min_heap으로 바꾸고 싶다면  조건문을 살짝 바꿔주면 됨
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_ELEMENTS 30
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
#define SWAP(a, b, tmp) { tmp = a; a = b; b = tmp; }
typedef struct element {
	int key;
}element;

element heap[MAX_ELEMENTS] = { -1 };

void push(element item, int* n);
element pop(int* n);

void inorder(element* heap, int i, int size);
void adjust(element a[], int root, int n);
void heapsort(element a[], int n);

int main()
{
	FILE* f;
	int k, n, size,num;
	element temp;

	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("파일을열수없습니다.");
		exit(1);
	}

	fscanf(f, "%d", &size);
	for (k = 1; k <= size; k++)   //size는 heap의 size
	{
		fscanf(f, "%d", &heap[k].key);
	}

	heapsort(heap, size);
	//inorder(heap, 1, size);
	//printf("\n");
	fclose(f);
	fopen_s(&f, "output.txt", "w");
	if (f == NULL)
	{
		printf("파일을 열 수 없습니다.");
		exit(1);
	}

	num = size;
	for (k = 1; k <= num; k++)
		fprintf(f, "%3d", pop(&size).key);
	fclose(f);
}

void heapsort(element a[], int n)   //n자리에 size가 들어감!!
{
	int i, j;
	element temp;
	for (i = n / 2; i > 0; i--)
	{
		adjust(a, i, n);
	}

	printf("\n");

	for (i = n - 1; i > 0; i--)
	{
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
	}

}
void adjust(element a[], int root, int n)
{

	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (a[child].key > a[child + 1].key))    //root에 최솟값이 가도록설정
			child++;
		if (rootkey <  a[child].key)
			break;
		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;

}
void inorder(element* heap, int i, int size)
{
	if (i <= size)
	{
		inorder(heap, 2 * i, size);
		if (heap[i].key != -1)
			printf("%3d", heap[i].key);
		inorder(heap, 2 * i + 1, size);
	}
}
element pop(int* n)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n))
	{
		fprintf(stderr, "the heap is empty");
		exit(1);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n)
	{
		if ((child < *n) && (heap[child].key  <heap[child + 1].key))
			child++;
		if (temp.key >= heap[child].key)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;

	}
	heap[parent] = temp;
	return item;
}
void push(element item, int* n)
{

	int i;
	if (HEAP_FULL(*n))
	{
		fprintf(stderr, "the heap is full.\n");
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}