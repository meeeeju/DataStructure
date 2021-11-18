#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void weightedunion(int i, int j);
int collapsingFind(int i);

int* parent;  // parent는 일차원 동적 배열->보통 전역으로 선언시편함

void weightedunion(int i, int j);    ///1과 2를 합쳐야 댈때 1의 root(집합크기) 와 2의 root(집합크기) 중 더큰 쪽으로 합치기 
//만약에 root의 크기가 같을시 j쪽으로 합침!!
int collapsingFind(int i);            // i의 root가 누구인지 알아낼때 쓴다.
void weightedunion(int i, int j)
{
	int rooti, rootj, temp;
	for (rooti = i; parent[rooti] >= 0; rooti = parent[rooti])
		;
	for (rootj = j; parent[rootj] >= 0; rootj = parent[rootj])
		;
	temp = parent[rootj] + parent[rooti];
	if (parent[rooti] >= parent[rootj])    //주의 음수임!
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
	return root;                  //lead는 일종의 temp 느낌
} 