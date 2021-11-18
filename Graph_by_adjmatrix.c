//Graph  를 adj_matrix를 이용하여 구성하고  DFS BFS 방식 이용하여 순회하여  출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define True 1
#define False 0
typedef struct Graph_matrix
{
	int nvertex;
	int nedge;
	int** adjmatrix;

}Graph_matrix;

typedef struct list {
	int* list;
	int n;
}list;

void dfs_mat(Graph_matrix graph1, list visit_dfs, int v, FILE* f);
int main()
{
	FILE* f;
	fopen_s(&f, "input.txt", "r");
	if (f == NULL)
	{
		printf("no file open");
		exit(1);
	}


	Graph_matrix graph1;
	int i, j;
	int v, u;
	list visit;
	fscanf(f, "%d %d", &graph1.nvertex, &graph1.nedge);


	visit.n = graph1.nvertex;
	visit.list = (int*)calloc(visit.n, sizeof(int));
	graph1.adjmatrix = (int**)malloc(sizeof(*graph1.adjmatrix) * graph1.nvertex);
	for (i = 0; i < graph1.nvertex; i++)
	{
		graph1.adjmatrix[i] = (int*)malloc(sizeof(int) * graph1.nvertex);
		for (j = 0; j < graph1.nvertex; j++)                                //초기화 시키는 작업
		{
			graph1.adjmatrix[i][j] = 0;
		}
	}
	for (i = 0; i < graph1.nedge; i++)                       //연결된 노드 연결시키기  edge가 존재하면 0->1
	{
		fscanf(f, "%d %d", &v, &u);
		graph1.adjmatrix[v][u] = 1;
		graph1.adjmatrix[u][v] = 1;
	}

	dfs_mat(graph1, visit, 0, stdout);

}

void dfs_mat(Graph_matrix graph1, list visit_dfs, int v, FILE* f)   //v->w
{
	int w;
	visit_dfs.list[v] = True;
	fprintf(f, "%3d", v);
	for (w = 0; w < visit_dfs.n; w++)
	{
		if (graph1.adjmatrix[v][w] && !visit_dfs.list[w])
			dfs_mat(graph1, visit_dfs, w, f);
	}
}

//bfs방식 구현 하는 방법 필요
