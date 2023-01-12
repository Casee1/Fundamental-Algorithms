#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler profiler("test");


//typedef struct node_type
//{
//	int id;
//	struct node_type* left, * right;
//} NodeT;
//void inorder(NodeT* p, int level)
//{
//	if (p != NULL)
//	{
//		inorder(p->left, level + 1);
//		for (int i = 0; i < level; i++) printf(" ");
//		printf("%d\n", p->id);
//		inorder(p->right, level + 1);
//	}
//}
//NodeT* createNode(int id, NodeT* left, NodeT* right)
//{
//	NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
//	newNode->id = id;
//	newNode->left = left;
//	newNode->right = right;
//	return newNode;
//}


typedef struct NodeT{
	int value;
	NodeT* left=NULL;
	NodeT* right = NULL;
	NodeT* parent = NULL;
	int size; //how many nodes are under the current node, inclusive the current one 
};

NodeT* tree_min(NodeT* x)
{
	while (x->left != NULL)
	{
		x = x->left;
	}
	return x;
}
NodeT* succesor(NodeT* x)
{
	if (x->right != NULL)
	{
		return tree_min(x->right);
	}
	NodeT* y = x->parent;
	while (y != NULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

NodeT* calculate_size(NodeT* root,Operation op)
{
	while (root != NULL) {
		op.count();
		root->size--;
		root = root->parent;
	}
	return root;
}
NodeT* calculate_sizedemo(NodeT* root)
{
	while (root != NULL) {
		root->size--;
		root = root->parent;
	}
	return root;
}

NodeT* Build_Tree(int* arr, int left, int right,NodeT* parent,Operation op)
{

	if (left > right)
	{
		return 0;
	}
	else
	{
		NodeT* root = (NodeT*)malloc(sizeof(NodeT)); //alocate
		int mid = (left + right) / 2;
		op.count();
		root->size = (right - left) + 1;
		root->value = arr[mid];
		root->parent = parent;
		root->left = Build_Tree(arr, left, mid-1,root,op); //left part
		root->right = Build_Tree(arr, mid + 1, right,root,op); //right part
		return root;
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
		root->size = (right - left) + 1;
		root->value = arr[mid];
		root->parent = parent;
		root->left = Build_Treedemo(arr, left, mid - 1, root); //left part
		root->right = Build_Treedemo(arr, mid + 1, right, root); //right part
		return root;
	}
}
int demoBT(NodeT* x, int i)
{
	if (x == NULL)
		return 0;
	i = i + 4;
	demoBT(x->right, i);
	cout << endl;
	for (int j = 4; j < i; j++)
	{
		cout << "   ";
	}
	cout << x->value << "(" << x->size << ")";
	demoBT(x->left, i);
}
//void inorder(NodeT* root, int size)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	size = size + 4;
//	inorder(root->right, size);
//	cout << endl;
//	for (int i = 4; i < size; i++)
//	{
//		cout << "    ";
//	}
//	cout << root->value << "'" << root->size << "'" << endl;
//	inorder(root->left, size);
//}

NodeT* OS_Select(NodeT* x,int i,Operation op)
{
	int rank;
	if (x->left == 0 && x->right == 0)
	{
		return x;
	}
	if (x->left != 0)
	{
		op.count();
		rank = x->left->size + 1; //is the rank of x within the subtree rooted at x
	}
	else
	{
		rank = 1;
	}

	if (i == rank)
	{
		return x;
	}
	else if (i < rank)
	{
		return OS_Select(x->left, i,op); //i'th smallest element resides in x' the left subtree
	}
	else
	{
		return OS_Select(x->right, i - rank,op); // i'th smallest element resides in x' the right subtree
	}

}
NodeT* OS_Selectdemo(NodeT* x, int i)
{
	int rank;
	if (x->left == 0 && x->right == 0)
	{
		return x;
	}
	if (x->left != 0)
	{
		rank = x->left->size + 1; //is the rank of x within the subtree rooted at x
	}
	else
	{
		rank = 1;
	}

	if (i == rank)
	{
		return x;
	}
	else if (i < rank)
	{
		return OS_Selectdemo(x->left, i); //i'th smallest element resides in x' the left subtree
	}
	else
	{
		return OS_Selectdemo(x->right, i - rank);  // i'th smallest element resides in x' the right subtree
	}

}
//void demoSelect()
//{
//	NodeT* root = NULL;
//	cout << "Demo for Select is: ";
//	cout << OS_Selectdemo(root, 7)->value<<endl;
//}

NodeT* OS_Delete(NodeT* root,int i,Operation op) {
	NodeT* delete_node = OS_Select(root, i, op);
	//NodeT* delete_node = {};

	if (delete_node != 0) {
		if (delete_node->left == 0 && delete_node->right == 0) {

			if (delete_node->parent != 0)
				if (delete_node->value < delete_node->parent->value) {
					delete_node->parent->left = 0;
				}

				else {
					delete_node->parent->right = 0;
				}
			calculate_size(delete_node->parent,op); 
			//calculate_size(delete_node->parent, op);
		}
		else if (delete_node->left == 0 && delete_node->right != 0)
		{

			if (delete_node->parent != 0)
			{
				if (delete_node->value < delete_node->parent->value) {
					delete_node->parent->left = delete_node->right;
					delete_node->right->parent = delete_node->parent;
				}
				else {
					delete_node->parent->right = delete_node->right;
					delete_node->right->parent = delete_node->parent;
				}
				calculate_size(delete_node->parent,op);
				//calculate_size(delete_node, op);
			}
		}
		else if (delete_node->left != 0 && delete_node->right == 0)
		{
			if (delete_node->parent != 0) {
				if (delete_node->value < delete_node->parent->value) {
					delete_node->parent->left = delete_node->left;
					delete_node->left->parent = delete_node->parent;
				}
				else {
					delete_node->parent->right = delete_node->left;
					delete_node->left->parent = delete_node->parent;
				}
				calculate_size(delete_node->parent,op);
				//calculate_size(delete_node, op);
			}
		}
		else if (delete_node->left != 0 && delete_node->right != 0) {
			NodeT* copy = new NodeT();
			copy = OS_Select(delete_node,i+1,op);
			/*copy = succesor(delete_node);
			calculate_size(copy, op);*/
			delete_node->value = copy->value;
			//OS_Delete(root, , op);
			/*int aux = copy->value;
			copy->value = delete_node->value;
			delete_node->value = aux;
			free(copy);*/
		}
	}
	return root;
}
void OS_Delete_demo(NodeT* root, int i) {
	NodeT* delete_node = OS_Selectdemo(root, i);

	if (delete_node != 0) {//if the selected node exists
		if (delete_node->left == 0 && delete_node->right == 0) {//case 1: the node has no children, is a leaf

			if (delete_node->parent != 0)//if the tree has only one node
				if (delete_node->value < delete_node->parent->value) {//looking if is on the left or on the right of his parent
					delete_node->parent->left = 0;//if is in the left of his parent  parent->left gets null
				}

				else {
					delete_node->parent->right = 0;//if is in the right parent->right gets null
				}
			calculate_sizedemo(delete_node->parent);//function to calculate the size

		}
		else if (delete_node->left != 0 && delete_node->right == 0)//if the child is in the left
		{
			if (delete_node->parent != 0)
				if (delete_node->value < delete_node->parent->value) {
					delete_node->parent->left = delete_node->left;
					delete_node->left->parent = delete_node->parent;
				}
				else {
					delete_node->parent->right = delete_node->left;
					delete_node->left->parent = delete_node->parent;
				}
			calculate_sizedemo(delete_node->parent);
		}
		else if (delete_node->left == 0 && delete_node->right != 0)//case 2: the node has one child on the right
		{//parent of his child gets the child
			if (delete_node->parent != 0)
				if (delete_node->value < delete_node->parent->value) {
					delete_node->parent->left = delete_node->right;
					delete_node->right->parent = delete_node->parent;
				}
				else {
					delete_node->parent->right = delete_node->right;
					delete_node->right->parent = delete_node->parent;
				}
			calculate_sizedemo(delete_node->parent);
		}
		else if (delete_node->left != 0 && delete_node->right != 0) {//case 3: if the node has 2 children
			NodeT* copy = new NodeT();//copy for calculate succesor
			copy = OS_Selectdemo(delete_node, i + 1);
			//copy = copy->right;
			/*while (copy->left != 0)
			{
				copy = copy->left;
			}*/
			OS_Delete_demo(root, i+1);//delete the succcesor
			delete_node->value = copy->value;//swap and delete the leaf
		}
	}
}

void perf()
{
		int const MAX_S = 10000;
		int const STEP = 100;
		int v[MAX_S], m[MAX_S];
		for (int i = 100; i <= MAX_S; i += STEP)
		{
			Operation op = profiler.createOperation("OP", i); //for select
			Operation op1 = profiler.createOperation("OP1", i); //for delete
			Operation op2 = profiler.createOperation("OP2", i); //for build
			for (int j = 1; j <= 5; j++)
			{
				srand(time(0));
				NodeT* parent = {};
				FillRandomArray(v, i, 1, i, true, ASCENDING);
				//Build_Tree(v, 1, i, parent, op);
				parent = Build_Tree(v, 1, i, parent, op2);
				for (int k = i; k >= 2; k--)
				{

					int p = rand() % k + 1;
					NodeT* node_selected = OS_Select(parent, p, op);
					OS_Delete(parent, p, op1);
				}
				//OS_Delete(parent, i, op2);
			}
		}
		profiler.divideValues("OP", 5);
		profiler.divideValues("OP1", 5);
		profiler.divideValues("OP2", 5);
		profiler.createGroup("TOTAL_OP","OP", "OP1", "OP2");
		profiler.showReport();
}

void demo()
{
	NodeT* root = NULL;
	int v[] = { 1,2,3,4,5,6, 7, 8, 9,10,11,12,13,14,15 };
	int n = sizeof(v) / sizeof(v[0]);
	root = Build_Treedemo(v, 0, n - 1,root);
	cout << "The BST is:" << endl;
	demoBT(root, 0);
	cout << endl;
	cout << "demo select1 is: ";
	cout << OS_Selectdemo(root, 12)->value << endl;
	cout << "delete demo1 is: ";
	OS_Delete_demo(root, OS_Selectdemo(root,12)->value);
	cout << endl;
	demoBT(root, 0);
	cout << endl;
	cout << "demo select2 is: ";
	cout << OS_Selectdemo(root, 4)->value << endl;
	cout << "delete demo2 is: ";
	OS_Delete_demo(root, OS_Selectdemo(root, 4)->value);
	cout << endl;
	demoBT(root, 0);
	cout << endl;
	cout << "demo select3 is: ";
	cout << OS_Selectdemo(root, 7)->value << endl;
	cout << "delete demo3 is: ";
	OS_Delete_demo(root, 7);
	cout << endl;
	demoBT(root, 0);
}

int main()
{
	demo();
	//perf();
}


