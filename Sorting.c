 //Sorting 하는 방법들 (1장도 추가함)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define compare(x,y)(((x)<(y))?-1:((x)==(y))?0:1)
#define SWAP(x,y,temp) {temp=x; x=y; y=temp;}

//insertion_sort
void insertionSort(int a[], int n);
void insert(int e, int a[], int i);
//quick_sort
void Quicksort(int a[], int left, int right);

//<1장에서 함>
int binsearch(int list[], int sele, int left, int right);
void sort(int list[], int n);


/*merge_sort*/
void Mergesort(int a[], int n);
void Merge(int l[], int a[], int h[], int nl, int nh);

void insertionSort(int a[], int n) 
{
	int j,temp;
	for (j = 2; j <= n; j++)
	{
		temp = a[j];
		insert(temp, a, j - 1);   //j-1까지 sorting된거임

}
void insert(int e, int a[], int i)
{
	a[0] = e;
	while (e < a[i])
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}


void Quicksort(int a[], int left, int right)
{
	int pivot, i, j;
	int temp = 0;
	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left];
		do {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i < j)  SWAP(a[i], a[j], temp);

		} while (i < j);
		SWAP(a[left], a[j], temp);
		Quicksort(a, left, j - 1);
		Quicksort(a, j + 1, right);
	}

}


void sort(int list[], int n)   //주의 min이 여기서 값이 아니라 index값임
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (list[min] > list[j])
			{
				min = j;
			}
			SWAP(list[i],list[min], temp);
		}
	}
}

//#define compare(x,y)(((x)<(y))?-1:((x)==(y))?0:1)
int binsearch(int list[], int sele, int left, int right)    //주의 배열의 인덱스가 반환된다. +sorting 된 배열에만 가능
{
	int middle, x;
	while (left <= right)
	{

		middle = (left + right) / 2;
		x = compare(list[middle], sele);
		switch (x)
		{
		case -1: left = middle + 1;
			break;

		case 0: return middle;
		case 1:
			right = middle - 1;
			//break;

		}
	}
	return -1;
}


void Merge(int l[], int a[], int h[], int nl, int nh)
{
	int i, j, k;
	i = j = k = 0;

	while (i < nl && j < nh)
	{
		if (l[i] <= h[j])
		{
			a[k] = l[i];
			i++;
		}
		else
		{
			a[k] = h[j];
			j++;
		}
		k++;
	}
	while (i < nl)
	{
		a[k] = l[i];
		i++; k++;
	}
	while (j < nh)
	{
		a[k] = h[j];
		j++; k++;
	}

}
void Mergesort(int a[], int n)
{
	int middle, i;
	int* left, * right;
	if (n < 2)
		return;
	middle = n / 2;
	left = (int*)malloc(sizeof(int) * middle);
	right = (int*)malloc(sizeof(int) * (n - middle));
	for (i = 0; i < middle; i++)
		left[i] = a[i];
	for (i = middle; i < n; i++)
		right[i - middle] = a[i];
	Mergesort(left, middle);
	Mergesort(right, n - middle);
	Merge(left, a, right, middle, n - middle);
}

