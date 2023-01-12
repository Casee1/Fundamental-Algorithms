#include <iostream>
#include "Profiler.h"
#include <stack>

using namespace std;
Profiler profiler("test");

enum {
	COLOR_WHITE = 0,
	COLOR_GRAY,
	COLOR_BLACK
};

struct Node {
	int color;
	Node* parent;
	int f;
	int d;
	int adj_Size;
	Node** Adj;
	int value;
	int in;
	int lowlink;
};

stack <Node*> stacktopological;
int error,in=0,nrComponents=0;
stack <Node*> S;


struct graph {
	int nr_nodes;
	Node** u;
};

void DFS_Visitperf(Node* u, int *time, Node* parent,Operation op)
{
	time = time + 1;
	u->d = *time;
	u->color = COLOR_GRAY;
	u->parent = parent;
	op.count(4);
	for (int i = 0; i < u->adj_Size; i++)
	{
		op.count(2);
		Node* j = u->Adj[i];
		if (j->color == COLOR_WHITE)
		{
			op.count();
			DFS_Visitperf(j, time, u,op);
		}
	}
	op.count(3);
	u->color = COLOR_BLACK;
	time = time + 1;
	u->f = *time;
}
void DFS_Visit(Node* u, int* time, Node* parent)
{
	time = time + 1;
	u->d = *time;
	u->color = COLOR_GRAY;
	u->parent = parent;
	for (int i = 0; i < u->adj_Size; i++)
	{
		Node* j = u->Adj[i];
		if (j->color == COLOR_WHITE)
		{
			DFS_Visit(j, time, u);
		}
	}
	u->color = COLOR_BLACK;
	time = time + 1;
	u->f = *time;
}

void DFS(graph* g)
{
	Node* u = new Node();
	for (int i = 0; i < g->nr_nodes; i++)
	{
		u->color = COLOR_WHITE;
		u->parent = NULL;
	}
	int time = 0;
	for (int i = 0; i < g->nr_nodes; i++)
	{
		if (g->u[i]->color == COLOR_WHITE)
		{
			DFS_Visit(g->u[i], &time, NULL);
		}
	}
}
void DFSperf(graph* g,Operation op)
{
	Node* u = new Node();
	for (int i = 0; i < g->nr_nodes; i++)
	{
		op.count(2);
		u->color = COLOR_WHITE;
		u->parent = NULL;
	}
	op.count();
	int time = 0;
	for (int i = 0; i < g->nr_nodes; i++)
	{
		op.count();
		if (g->u[i]->color == COLOR_WHITE)
		{
			op.count();
			DFS_Visitperf(g->u[i], &time, NULL,op);
		}
	}
}

void initialization(graph* g, int size)
{
	g->nr_nodes = size;
	g->u = (Node**)malloc(size * sizeof(Node));
	for (int i = 0; i < size; i++)
	{
		g->u[i] = (Node*)malloc(sizeof(Node));
		g->u[i]->parent = NULL;
		g->u[i]->color = COLOR_WHITE;
		g->u[i]->Adj = (Node**)malloc(size * sizeof(Node));
		g->u[i]->adj_Size = 0;
		g->u[i]->f = -1;
		g->u[i]->d = -1;
		g->u[i]->value = i;
		g->u[i]->in = -1;
		g->u[i]->lowlink = -1;
	}
}
void print(graph* g)
{
	for (int i = 0; i < g->nr_nodes; i++)
	{
		if (g->u[i]->parent)
		{
			cout << "node " << i << ": " << g->u[i]->parent->value << endl;
		}
		else
			cout << "I don't have parent for node " << i << endl;
	}

}

void demo_dfs()
{
	graph g;
	int size = 8;
	initialization(&g, size);
	g.u[0]->Adj[g.u[0]->adj_Size++] = g.u[2];//0->2
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[0];//1->0
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[3];//1->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[1];//2->1
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[3];//2->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[4];//2->4
	g.u[3]->Adj[g.u[3]->adj_Size++] = g.u[5];//3->5
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[6];//4->6
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[5];//4->5
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[3];//5->3
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[7];//5->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[7];//6->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[4];//6->4

	DFS(&g);

	print(&g);
	cout << endl;

}

void topological(Node* u, int* time, Node* parent)
{
	//int err = 0;
	time = time + 1;
	u->color = COLOR_GRAY;
	u->parent = parent;
	u->d = *time;
	for (int i = 0; i < u->adj_Size; i++)
	{
		Node* index = u->Adj[i];
		if (index->color == COLOR_WHITE)
		{
			topological(index, time, u);
		}
		if (index->color == COLOR_GRAY)
		{
			error = 1;
		}
	}
	time = time + 1;
	u->f = *time;
	u->color = COLOR_BLACK;
	stacktopological.push(u);
}
void topological_sort(graph* g)
{
	int time = 0;
	for (int i = 0; i < g->nr_nodes; i++)
	{
		if (g->u[i]->color == COLOR_WHITE)
		{
			topological(g->u[i], &time, NULL);
		}
	}
}
void demo_topological_sort()
{
	graph g;
	int size = 8;
	initialization(&g, size);
	g.u[0]->Adj[g.u[0]->adj_Size++] = g.u[2];//0->2
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[0];//1->0
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[3];//1->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[1];//2->1
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[3];//2->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[4];//2->4
	g.u[3]->Adj[g.u[3]->adj_Size++] = g.u[5];//3->5
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[6];//4->6
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[5];//4->5
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[3];//5->3
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[7];//5->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[7];//6->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[4];//6->4

	topological_sort(&g);

	cout << endl;

	//cout << "I have " << nrComponents << endl; //connected components
	if (error != 0)
	{
		while (stacktopological.empty() == 0)
		{
			cout << stacktopological.top()->value << " ";
			stacktopological.pop();
		}
	}
}

void strong_connect(graph* g, Node* u)
{
	u->in = in;
	u->lowlink = in;
	in = in + 1;
	S.push(u);
	u->color = COLOR_GRAY;
	for (int i = 0; i < u->adj_Size; i++)
	{
		Node* intermediar = u->Adj[i];
		if (intermediar->color == COLOR_WHITE)
		{
			strong_connect(g, intermediar);
			u->lowlink = min(u->lowlink, intermediar->lowlink);
		}
		else if (intermediar->color == COLOR_GRAY)
		{
			u->lowlink = min(u->lowlink, intermediar->in);
		}
	}
		stacktopological.push(u);
		if (u->lowlink == u->in)
		{
			nrComponents++;
			Node* intermediar;
			do
			{
				intermediar = S.top();
				S.pop();
				intermediar->color = COLOR_BLACK;
				cout << intermediar->value << " ";
			} while (intermediar != u);
			cout << endl;
		}	
}
void Tarjan(graph* g)
{
	for (int i = 0; i < g->nr_nodes; i++)
	{
		g->u[i]->color = COLOR_WHITE;
		g->u[i]->parent = NULL;
		g->u[i]-> in = -1;
		g->u[i]->lowlink = -1;
	}
	for (int i = 0; i < g->nr_nodes; i++)
	{
		if (g->u[i]->in == -1)
		{
			strong_connect(g, g->u[i]);
		}
	}
}
void demo_Tarjan()
{
	graph g;
	int size = 8;
	initialization(&g, size);
	g.u[0]->Adj[g.u[0]->adj_Size++] = g.u[2];//0->2
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[0];//1->0
	g.u[1]->Adj[g.u[1]->adj_Size++] = g.u[3];//1->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[1];//2->1
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[3];//2->3
	g.u[2]->Adj[g.u[2]->adj_Size++] = g.u[4];//2->4
	g.u[3]->Adj[g.u[3]->adj_Size++] = g.u[5];//3->5
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[6];//4->6
	g.u[4]->Adj[g.u[4]->adj_Size++] = g.u[5];//4->5
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[3];//5->3
	g.u[5]->Adj[g.u[5]->adj_Size++] = g.u[7];//5->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[7];//6->7
	g.u[6]->Adj[g.u[6]->adj_Size++] = g.u[4];//6->4

	Tarjan(&g);

}

void perf()
{
	for (int i = 1000; i <= 4500; i =i+ 100)
	{
		graph g;
		initialization(&g, 100);// initialize 100 nodes
		for (int k = 0; k < 100; k++)
		{
			for (int j = 1; j <= n / 100; j++)
			{
				g.u[k]->Adj[g.u[k]->adj_Size++] = g.u[(k + j) % 100];
			}
		}
		Operation oper = profiler.createOperation("EDGES", i);
		DFSperf(&graph, oper);
	}
	for (int i = 100; i <= 200; i = i + 10)
	{
		graph g;
		initialization(&g, i);
		int edges = 0;
		for (int k = 0; k < i && edges < 4500; k++)
		{
			for (int j = 1; j <= 4500 / i + 1 && edges < 4500; j++)
			{
				graph.u[k]->Adj[graph.u[k]->adj_Size++] = graph.u[(k + j) % 100];
				edges++;
			}
		}
		Operation oper = profiler.createOperation("NODES", i);
		DFSperf(&graph, oper);
	}
	profiler.showReport();
}

int main()
{
	cout << "DFS";
	cout << endl;
	//demo_dfs();
	cout << endl;
	cout << "TARJAN";
	cout << endl;
	//demo_Tarjan();
	cout << endl;
	cout << "TOPOLOGICAL";
	cout << endl;
	demo_topological_sort();

	//perf();
}