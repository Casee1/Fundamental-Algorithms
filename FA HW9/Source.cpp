//typedef struct edge
//{
//	int sourse;
//	int target;
//	int weight;
//};
//void swap(edge** a, edge** b) //function to swap two vectors
//{
//	edge* aux = *a;
//	*a = *b;
//	*b = aux;
//}
//int Partitiondemo(edge** v, int low, int high) // it s the same like the previous but i used this function for demo
//{
//	edge* pivot = v[high];
//
//	int leftwall = low - 1;
//	for (int i = low; i < high; i++)
//	{
//
//		if (v[i] < pivot)
//		{
//
//			leftwall++;
//			swap(&v[i], &v[leftwall]);
//
//		}
//	}
//
//	swap(&v[leftwall + 1], &v[high]);
//	return leftwall + 1;
//}
//void QuickSortdemo(edge** v, int low, int high) // the same but i used it to demo
//{
//
//	if (low < high)
//	{
//
//		int mid = Partitiondemo(v, low, high);
//		QuickSortdemo(v, low, mid - 1);
//		QuickSortdemo(v, mid + 1, high);
//	}
//
//}
//
//
//edge** Kruskhal(edge** edges, NodeT** v, int nr_edges, int nr_vertices)
//{
//	edge** A = (edge**)malloc(nr_edges * sizeof(edge*));
//	for (int i = 0; i < nr_vertices; i++)
//	{
//		v[i] = make_set(i);
//	}
//	QuickSortdemo(edges, 0, nr_edges);
//	int k = 0;
//	for (int i = 0; i < nr_edges; i++)
//	{
//		if (find_set(v[edges[i]->sourse]) != find_set(v[edges[i]->target]))
//		{
//			A[k] = edges[i];
//			k++;
//			union1(v[edges[i]->sourse], v[edges[i]->target]);
//
//		}
//	}
//	return A;
//
//}
//edge** Kruskhaldemo(edge** edges, NodeT** v, int nr_edges, int nr_vertices)
//{
//	edge** A = (edge**)malloc(nr_edges * sizeof(edge*));
//	for (int i = 0; i < nr_vertices; i++)
//	{
//		v[i] = make_set(i);
//	}
//	QuickSortdemo(edges, 0, nr_edges);
//	int k = 0;
//	for (int i = 0; i < nr_edges; i++)
//	{
//		if (find_set(v[edges[i]->sourse]) != find_set(v[edges[i]->target]))
//		{
//			A[k] = edges[i];
//			k++;
//			union1(v[edges[i]->sourse], v[edges[i]->target]);
//
//		}
//	}
//	return A;
//
//}
//
//void demo_operations()
//{
//	NodeT* v[11];
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int nr_edges = sizeof(arr) / sizeof(arr[0]);
//	for (int i = 0; i < nr_edges; i++)
//	{
//		v[i] = make_set(arr[i]);
//		cout << "index "<<" " << i<<" " << "with element" << " " << v[i]->value << endl;
//	}
//	cout << endl;
//
//	union1(v[0], v[1]); //should make union between 1 and 2
//	union1(v[3], v[4]); //should make union between 4 and 5
//	union1(v[3], v[9]); //should make union between 4 and 10
//	union1(v[2], v[3]); //should make union between 3 and 4
//	union1(v[8], v[5]); //should make union betweeen 9 and 6
//	cout << endl;
//	for (int j = 0; j < nr_edges; j++)
//	{
//		cout << arr[j] <<" "<< "with root "<<" "<< find_set(v[j])->value << endl;
//	}
//}
//
//int main()
//{
//	/*demo_operations();
//	cout << endl;
//	cout << "------------------";
//	cout << endl;
//	Kruskhal_demo*/
//	perf();
//}
#include <iostream>
#include<list>
#include "Profiler.h"
using namespace std;
Profiler profiler("test");
#define SIZE 10000
list <int> solution[SIZE];

int v[1000];
int op;

struct NodeT
{
	int value;
	NodeT* parent; //we need it to go to the root
	int rank = 1;

};


NodeT* Make_Set(int i)
{
	NodeT* x = (NodeT*)malloc(sizeof(NodeT));
	x->value = i;
	x->rank = 1;
	x->parent = NULL;
	op =op + 4;
	return x;
}
NodeT* Make_Setdemo(int x)
{
	NodeT* y = (NodeT*)malloc(sizeof(NodeT));
	y->value = x;
	y->rank = 1;
	y->parent = NULL;
	return y;
}

NodeT* Find_Set(NodeT* x)// has the complexity O(log n) if the tree is balanced
{
	op++;
	if (x->parent == NULL)
	{
		return x;
	}
	else
	{
		op =op + 2;
		x->parent = Find_Set(x->parent);
		return x->parent;
	}
}
NodeT* Find_Setdemo(NodeT* x)// has the complexity O(log n) if the tree is balanced
{
	if (x->parent == NULL)
	{
		return x;
	}
	else
	{
		x->parent = Find_Setdemo(x->parent);
		return x->parent;
	}
}

void Link(NodeT* x, NodeT* y)// O(1)
{
	op++;
	if (y->rank > x->rank)
	{
		op++;
		x->parent = y;
	}
	else
	{
		op = op+2;
		y->parent = x;
		if (y->rank == x->rank)
		{
			op++;
			y->rank++;
		}
	}
}
void Linkdemo(NodeT* x, NodeT* y)// O(1)
{
	if (y->rank > x->rank)
	{
		x->parent=y;
	}
	else
	{
		y->parent = x;
		if (y->rank == x->rank)
		{
			y->rank++;
		}
	}
}

void Union(NodeT* x, NodeT* y) // has the complexity O(log n)
{
	Link(Find_Set(x), Find_Set(y));
}

void demo_operations()
{
	NodeT* v1[10];
	int Array[] = { 1,2,3,4,5,6,7,8,9,10 }; //given array
	int nr_edges = sizeof(Array) / sizeof(Array[0]); //size of nr of edges
	for (int i = 0; i < nr_edges; i++)
	{
		v1[i] = Make_Setdemo(Array[i]); //make the sets 
		cout << "index " << i << " with element " << v1[i]->value << endl; // print to see the elements and it's index
	}
	cout << endl;

	Union(v1[0], v1[2]); //should make union between 1 and 2 
	Union(v1[3], v1[5]); //should make union between 4 and 5
	Union(v1[3], v1[8]); //should make union between 4 and 10
	Union(v1[2], v1[4]); //should make union between 3 and 4
	Union(v1[9], v1[7]); //should make union between 9 and 6

	for (int j = 0; j < nr_edges; j++)
	{
		cout << Array[j] << " with root " << Find_Set(v1[j])->value << endl; //print the elements and it's root
	}
}

struct Edge
{
	int source;
	int target;
	int weight;
};

int Partition(Edge** v, int left, int right)
{
	int i = left;
	int j = right;
	while (i < j)
	{
		do
		{
			i++;
		} while (i < right && v[i]->weight <= v[left]->weight);
		do
		{
			j--;
		} while (j > left && v[j]->weight > v[left]->weight);
		if (i < j)
		{
			swap(v[i], v[j]);
		}
	}
	swap(v[left], v[j]);
	return j;
}

//void swap(edge** a, edge** b) //function to swap two vectors
//{
//	edge* aux = *a;
//	*a = *b;
//	*b = aux;
//}
//int Partitiondemo(edge** v, int low, int high) // it s the same like the previous but i used this function for demo
//{
//	edge* pivot = v[high];
//
//	int leftwall = low - 1;
//	for (int i = low; i < high; i++)
//	{
//
//		if (v[i] < pivot)
//		{
//
//			leftwall++;
//			swap(&v[i], &v[leftwall]);
//
//		}
//	}
//
//	swap(&v[leftwall + 1], &v[high]);
//	return leftwall + 1;
//}

void Quick_Sort(Edge** v, int left, int right)
{
	if (left < right)
	{
		int k = Partition(v, left, right);
		Quick_Sort(v, left, k);
		Quick_Sort(v, k + 1, right);
	}
}

Edge** Kruskal(Edge** Edges, NodeT** v, int nr_edges, int nr_vertices)
{
	for (int i = 0; i < nr_vertices; i++)
	{
		v[i] = Make_Set(i); 
	}
	Edge** A = (Edge**)malloc(nr_edges * sizeof(Edge*));
	Quick_Sort(Edges, 0, nr_edges);
	int k = 0;
	for (int j = 0; j < nr_edges; j++)
	{
		if (Find_Set(v[Edges[j]->source]) != Find_Set(v[Edges[j]->target]))
		{
			A[k] = Edges[j];
			k++;
			Union(v[Edges[j]->source], v[Edges[j]->target]);
		}
	}
	return A;
}

void demo_Kruskal()
{
	int nr_vertices = 5;
	int nr_edges = 7;
	Edge** Edges = (Edge**)malloc(nr_edges * sizeof(Edge*));

	for (int i = 0; i < nr_edges; i++)
	{
		Edges[i] = (Edge*)malloc(sizeof(Edge));
		cin >> Edges[i]->source >> Edges[i]->target >> Edges[i]->weight; //i'm giving from the keyboard the values for the source,targert and weight
	}

	NodeT** v = (NodeT**)malloc(nr_vertices * sizeof(NodeT*)); //vertices

	Edge** solution = Kruskal(Edges, v, nr_edges, nr_vertices); //call the algorithm

	for (int i = 0; i < nr_vertices - 1; i++)
	{
		cout << solution[i]->source << " to " << solution[i]->target << " cost: " << solution[i]->weight;
		cout << endl;
	}
}

void perf()
{
	int size = 10000;
	for (int i = 100; i <= SIZE; i = i + 100) //i is nr of vertices
	{
		op = 0;
		int nr_edges = 4 * i;
		Edge** Edges = (Edge**)malloc(nr_edges * sizeof(Edge*));// allocate space for edges and vertices
		NodeT** v = (NodeT**)malloc(i * sizeof(NodeT*));
		int index = 0;
		for (int j = 0; j < i; j++)
			for (int k = 1; k <= 4; k++)
			{
				Edges[index] = (Edge*)malloc(sizeof(Edge));
				Edges[index]->source = j;
				Edges[index]->target = (k + j) % i;
				Edges[index]->weight = rand() % 100000;
				index++;
			}

		Edge** solution = Kruskal(Edges, v, nr_edges, i);

		Operation op1 = profiler.createOperation("Operations", i);
		op1.count(op);


	}
	profiler.showReport();
}

int main()
{
	demo_operations();
	demo_Kruskal();
	//perf();

	return 0;
}
