#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void weightedunion(int i, int j);
int collapsingFind(int i);

int* parent;  // parent�� ������ ���� �迭->���� �������� ���������

void weightedunion(int i, int j);    ///1�� 2�� ���ľ� � 1�� root(����ũ��) �� 2�� root(����ũ��) �� ��ū ������ ��ġ�� 
//���࿡ root�� ũ�Ⱑ ������ j������ ��ħ!!
int collapsingFind(int i);            // i�� root�� �������� �˾Ƴ��� ����.
void weightedunion(int i, int j)
{
	int rooti, rootj, temp;
	for (rooti = i; parent[rooti] >= 0; rooti = parent[rooti])
		;
	for (rootj = j; parent[rootj] >= 0; rootj = parent[rootj])
		;
	temp = parent[rootj] + parent[rooti];
	if (parent[rooti] >= parent[rootj])    //���� ������!
	{
		parent[rooti] = rootj;
		parent[rootj] = temp;
	}
	else
	{
		parent[rootj] = rooti;
		parent[rooti] = temp;
	}
}

int collapsingFind(int i)
{
	int root, trail, lead;
	for (root = i; parent[root] >= 0; root = parent[root])
		;
	for (trail = i; trail != root; trail = lead)
	{
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;                  //lead�� ������ temp ����
} 