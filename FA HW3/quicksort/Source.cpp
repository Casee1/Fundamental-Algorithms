/* CRISTIAN CASIAN-CRISTI 30422
* QuickSort on worst case has the complexity of O(n^2)
* in average case is O(nlogn)
*/

#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler("test");


void swap(int* a, int* b) //function to swap two vectors
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int Partition(int* v, int low, int high, Operation comp, Operation assign)
{
	assign.count();
	int pivot = v[high]; //consider the last element as pivot and moves all smaller element to left of it and grater elements to right
	int leftwall = low - 1; //index of smaller element and indicates the right position of pivot found
	for (int i = low; i < high; i++)
	{
		comp.count();
		if (v[i] < pivot)
		{

			leftwall++;
			swap(&v[i], &v[leftwall]);
			assign.count(3);
		}
	}

	swap(&v[leftwall + 1], &v[high]);
	assign.count(3);
	return leftwall + 1;
}

int Partitiondemo(int* v, int low, int high) // it s the same like the previous but i used this function for demo
{
	int pivot = v[high]; 

	int leftwall = low - 1;
	for (int i = low; i < high; i++)
	{

		if (v[i] < pivot)
		{

			leftwall++;
			swap(&v[i], &v[leftwall]);

		}
	}

	swap(&v[leftwall + 1], &v[high]);
	return leftwall + 1;
}

int PartitionBEST(int* v, int low, int high, Operation comp, Operation assign)
{
	assign.count();
	int pivot = v[(high+low)/2]; // for best case partition is the same like the previous one but we choose the pivot to be the middle
	int leftwall = low - 1;
	for (int i = low; i < high; i++)
	{
		comp.count();
		if (v[i] < pivot)
		{

			leftwall++;
			swap(&v[i], &v[leftwall]);
			assign.count(3);
		}
	}

	swap(&v[leftwall + 1], &v[high]);
	assign.count(3);
	return leftwall + 1;
}


void QuickSort(int* v, int low, int high, int size, Operation comp, Operation assign)
{

	if (low < high)
	{

		int mid = Partition(v, low, high, comp, assign); //partitioning index, v[mid] is now at right place
		QuickSort(v, low, mid - 1, size, comp, assign); //separately sort elements before and after partition
		QuickSort(v, mid + 1, high, size, comp, assign);
	}

}

void QuickSortdemo(int* v, int low, int high, int size) // the same but i used it to demo
{

	if (low < high)
	{

		int mid = Partitiondemo(v, low, high);
		QuickSortdemo(v, low, mid - 1, size);
		QuickSortdemo(v, mid + 1, high, size);
	}

}

void QuickSortBEST(int* v, int low, int high, int size, Operation comp, Operation assign) // the same but it's for best case with pivot in the middle
{

	if (low < high)
	{

		int mid = PartitionBEST(v, low, high, comp, assign);
		QuickSortBEST(v, low, mid - 1, size, comp, assign);
		QuickSortBEST(v, mid + 1, high, size, comp, assign);
	}

}

void demo()
{
	const int size = 20;
	int v[size];

	FillRandomArray(v, size, 10, 500, true, DESCENDING);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	QuickSortdemo(v, 0, size - 1, size);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

}

void perf(int cas)
{
	int const MAX_S = 5000;
	int const STEP = 100;
	int v[MAX_S], m[MAX_S];
	for (int i = 100; i <= MAX_S; i += STEP)
	{
		if (cas == 0)
			FillRandomArray(v, i, 10, 5000, false, UNSORTED); //function to generate a random array unsorted for average case 
		else if (cas == 1)
			FillRandomArray(v, i, 10, 5000, false, DESCENDING); // function to generate an descending array for worst case 
		else
			FillRandomArray(v, i, 10, 5000, false, ASCENDING); //function to generate an ascending array for best case
		Operation comp = profiler.createOperation("QuickSort_comp", i);
		Operation assign = profiler.createOperation("QuickSort_assign", i);
		CopyArray(m, v, i);
		if (cas == 2)
			QuickSortBEST(v, 0, i-1, i, comp, assign);
		else
			QuickSort(v, 0, i - 1, i, comp, assign);

	}
}

int main()
{
	demo();
	/*perf(0);
		profiler.addSeries("op_QuickSort", "QuickSort_assign", "QuickSort_comp");

		profiler.createGroup("op_average", "op_QuickSort");
		profiler.createGroup("assign_average", "QuickSort_assign");
		profiler.createGroup("comp_average", "QuickSort_comp");

		profiler.reset("WORST");

	perf(1);
		profiler.addSeries("op_QuickSort", "QuickSort_assign", "QuickSort_comp");

		profiler.createGroup("op_WORST", "op_QuickSort");
		profiler.createGroup("assign_WORST", "QuickSort_assign");
		profiler.createGroup("comp_WORST", "QuickSort_comp");

		profiler.reset("BEST");
	perf(2);
		profiler.addSeries("op_QuickSort", "QuickSort_assign", "QuickSort_comp");

		profiler.createGroup("op_BEST", "op_QuickSort");
		profiler.createGroup("assign_BEST", "QuickSort_assign");
		profiler.createGroup("comp_BEST", "QuickSort_comp");

		profiler.showReport();*/
	return 0;
}