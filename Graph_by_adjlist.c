#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define True 1
#define False 0
typedef struct adjlist* adjpoint;
typedef struct adjlist
{
	int vertex;
	int cost;
	adjpoint link;

}adjlist;

typedef struct Graph_adjlist
{
	adjpoint* graph;  //������ �����͹迭
	int n;  //vertex
	int nedge;
}Graph_adjlist;

typedef struct list {
	int* list;
	int n;
}list;

typedef struct queue* queuepointer;   //linkedlist queue ����
typedef struct queue {
	int vertex;
	queuepointer link;
}queue;
queuepointer front, rear;
void addq(int item);
int deleteq();

adjpoint insertail(adjpoint h, int data);   //graph����� �ٶ� �ʿ���

//graph Ž�� ���
void dfs(int v, list visited, Graph_adjlist graph, FILE* f);
void  bfs(int v, list visited, Graph_adjlist graph, FILE* f);


int main()
{

	Graph_adjlist graph1;
	adjpoint* temp;
	list visited;
	int v,u,i, j;
	
	graph1.n = visited.n=4;     //�̺κп� fscanf�� ���� ���� �� �о����
	graph1.nedge = 6;

	//list �� graph ���� �� �ʱ�ȭ
	visited.list = (int*)calloc(visited.n,sizeof(int));

	graph1.graph = (adjpoint*)malloc(sizeof(*graph1.graph) *graph1.n);
	for (i = 0; i < graph1.n; i++)
		graph1.graph[i] = NULL;

	//graph ����
	for (i = 0; i <graph1.nedge; i++)
	{
		fscanf(stdout, "%d %d", &v, &u);

		graph1.graph[v] = insertail(graph1.graph[v], u);
		graph1.graph[u] = insertail(graph1.graph[u], v);

	}
	


}

adjpoint insertail(adjpoint h, int data)
{
	adjpoint temp;
	adjpoint current;
	current = h;
	temp = (adjpoint)malloc(sizeof(*temp));
	temp->vertex = data;
	temp->link = NULL;
	if (current)
	{
		while (current->link)
			current = current->link;
		current->link = temp;
	}
	else
		h = temp;
	return h;
}

void dfs(int v,list visited, Graph_adjlist graph, FILE* f)  //depth
{
	adjpoint w;
	visited.list[v] = True;
	fprintf(f, "%3d", v);
	for (w = graph.graph[v]; w; w = w->link)
	{
		if (!visited.list[w->vertex])
			dfs(w->vertex, visited, graph, f);
	}

}
void bfs(int i, list visited, Graph_adjlist graph, FILE* f)
{
	int v;
	adjpoint w;
	rear = front = NULL;
	printf("%d", i);
	visited.list[i] = True;
	addq(i);
	
	while (front)
	{
		v = delteq();
		for (w = graph.graph[v]; w; w = w->link)
		{
			if (!visited.list[w->vertex])
			{
				printf("%d", w->vertex);
				addq(w);
				visited.list[w->vertex] = True;
			}
		}
		
		
	}
}



void bfs(int v,list visited, Graph_adjlist graph, FILE* f)       
{
	adjpoint w;
	front = rear = NULL;  //queue�ʱ�ȭ
	fprintf(f, "%5d", v);
	visited.list[v] = True;
	addq(v);
	while (front)
	{
		v = deleteq(); //int ������ ��ȯ
		for (w = graph.graph[v]; w; w = w->link)
		{
			if (!visited.list[w->vertex])
			{
				fprintf(f, "%5d", w->vertex);
				visited.list[w->vertex] = True;
				addq(w->vertex);
			}
		}
	}
}



void addq(int item)
{
	/*temp�����ؼ� item�� �ʾ��ְ� �ʱ�ȭ ��Ű���۾�*/
	queuepointer temp;
	temp = (queuepointer)malloc(sizeof(*temp));
	temp->vertex = item;
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
	int item;
	if (!temp)
		return NULL;
	item = temp->vertex;
	front = temp->link;
	free(temp);
	return item;
}
