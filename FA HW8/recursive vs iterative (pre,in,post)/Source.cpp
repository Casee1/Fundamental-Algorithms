#include <iostream>
#include "Profiler.h"

using namespace std;
Profiler profiler("test");

typedef struct NodeT {
	int value;
	NodeT* left;
	NodeT* right;
	NodeT* parent;
};

void recursive(NodeT* root,int ord,Operation op)
{
	if (root == NULL)
		return;
	if (ord == -1)
	{
		op.count();
	}
	recursive(root->left,ord,op);
	recursive(root->right,ord,op);
}

void recursivedemo(NodeT* root, int ord)
{
	if (root == NULL)
		return;
	if (ord == -1)
	{
		cout << root->value << " ";
	}
	recursivedemo(root->left, ord);
	if (ord == 0)
	{
		cout << root->value << " ";
	}
	recursivedemo(root->right, ord);
	if (ord == 1)
	{
		cout << root->value << " ";
	}
}

void iterativedemo(NodeT* root,int ord)
{
	int dir = 1;
	while (root->parent != NULL || dir != 3)
	{
		if (dir == 1)
		{
			if (ord == -1)
			{
				cout << root->value<<" ";
			}
			if (root->left != NULL) {
				root = root->left;
				dir = 1;
			}
			else
			{
				dir = 2;
			}
		}
		else if (dir == 2)
		{
			if (ord == 0)
			{
				cout << root->value<<" ";
			}
			if (root->right != NULL) {
				root = root->right;
				dir = 1;
			}
			else
				dir = 3;
		}
		else if (dir == 3)
		{
			if (ord == 1)
			{
				cout << root->value<<" ";
			}
			if (root == root->parent->left)
				dir = 2;
			else if (root == root->parent->right)
				dir = 3;
			root = root->parent;
		}
	}
	if (ord == 1)
	{
		cout << root->value << " ";
	}
}

void iterative(NodeT* root, int ord,Operation op)
{
	int dir = 1;
	while (root->parent != NULL || dir != 3)
	{
			
		if (dir == 1)
		{
			op.count();
			if (root->left != NULL) {
				root = root->left;
				dir = 1;
			}
			else
			{
				dir = 2;
			}
		}
		else if (dir == 2)
		{
			if (root->right != NULL) {
				root = root->right;
				dir = 1;
			}
			else
				dir = 3;
		}
		else if (dir == 3)
		{
			if (root == root->parent->left) {
				dir = 2;
			}
			else if (root == root->parent->right) {
				dir = 3;
			}

			root = root->parent;
		}
	}
	if (ord == 1)
	{
		cout << root->value << " ";
	}
}

NodeT* Build_Treedemo(int* arr, int left, int right, NodeT* parent)
{

	if (left > right)
	{
		return 0;
	}
	else
	{
		NodeT* root = (NodeT*)malloc(sizeof(NodeT)); //alocate
		int mid = (left + right) / 2;
		root->value = arr[mid];
		root->parent = parent;
		root->left = Build_Treedemo(arr, left, mid - 1, root); //left part
		root->right = Build_Treedemo(arr, mid + 1, right, root); //right part
		return root;
	}
}

void demo()
{
	NodeT* root = NULL;
	int v[] = { 1,2,3,4,5,6, 7, 8, 9,10,11 };
	int n = sizeof(v) / sizeof(v[0]);
	root = Build_Treedemo(v, 0, n - 1, root);
	cout << "FOR RECURSIVE: " << endl;
	recursivedemo(root, -1);
	cout << endl;
	recursivedemo(root, 0);
	cout << endl;
	recursivedemo(root, 1);
	cout << endl;
	cout << "FOR ITERATIVE: ";
	cout << endl;
	iterativedemo(root, -1);
	cout << endl;
	iterativedemo(root, 0);
	cout << endl;
	iterativedemo(root, 1);
}

void perf()
{
	int step = 100;
	const int max_size = 10000;
	int v[max_size] = {};
	for (int i = 100; i <= max_size; i = i + step)
	{
		Operation op = profiler.createOperation("op", i);
		Operation op1 = profiler.createOperation("op1", i);
		NodeT* build = new NodeT;
		build->parent = NULL;
		FillRandomArray(v, i, 1, i, true, ASCENDING);
		build = Build_Treedemo(v, 1, i, build);
		recursive(build, -1,op);
		iterative(build, -1,op1);
	}
	profiler.createGroup("operations", "op", "op1");
	profiler.showReport();
}

int main()
{
	//demo();
	perf();
}