/* CRISTIAN CASIAN-CRISTI 30422
* QuickSort on worst case has the complexity of O(n^2)
* in average case is O(nlogn)
*/

#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler("test");


void swap(int* a,int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

// algorithms are the same but here only we do the comparation

int Partition(int *v, int low, int high,Operation op)
{	
	op.count();
	int pivot = v[high];
	int leftwall = low - 1;
	for (int i = low; i < high ; i++)
	{
		op.count();
		if (v[i] < pivot)
		{
			
			leftwall++;
			swap(&v[i], &v[leftwall]);
			op.count(3);
		}
	}
	
	swap(&v[leftwall + 1], &v[high]);
	op.count(3);
	return leftwall + 1;
}

int Partitiondemo(int* v, int low, int high)
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


void QuickSort(int *v, int low, int high,int size,Operation op)
{
	
	if (low < high)
	{
		
		int mid = Partition(v, low, high,op);
		QuickSort(v, low, mid - 1,size,op);
		QuickSort(v, mid + 1, high,size,op);
	}

}
void QuickSortdemo(int* v, int low, int high, int size)
{

	if (low < high)
	{

		int mid = Partitiondemo(v, low, high);
		QuickSortdemo(v, low, mid - 1, size);
		QuickSortdemo(v, mid + 1, high, size);
	}

}

int parent(int i)
{
	return (i - 1) / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;

}

void max_heapify(int* v, int i, int size, Operation op) //heapify
{
	int l = left(i);
	int r = right(i);
	int max_value = 0;
	if (l < size && v[l] > v[i])
	{
		max_value = l;
		op.count();
		op.count();
	}
	else
		max_value = i;
	if (r < size && v[r] > v[max_value])
	{
		max_value = r;
		op.count();
		op.count();
	}
	if (max_value != i)
	{
		op.count(3);
		int aux = v[i];
		v[i] = v[max_value];
		v[max_value] = aux;
		max_heapify(v, max_value, size, op);
	}

}
void max_heapifydemo(int* v, int i, int size) // here I create an identical function like the previous one but without the operations to call it when I make the sort
{
	int l = left(i);
	int r = right(i);
	int max_value = 0;;
	if (l < size && v[l] > v[i])
		max_value = l;
	else
		max_value = i;
	if (r < size && v[r] > v[max_value])
		max_value = r;
	if (max_value != i)
	{
		int aux = v[i];
		v[i] = v[max_value];
		v[max_value] = aux;
		max_heapifydemo(v, max_value, size);
	}

}

void build_max_heapBU(int* v, int size,Operation op) // we build the bottom up heap
{
	for (int i = size / 2 - 1; i >= 0; i--)
		max_heapify(v, i, size, op);
}

void heapsort_BU(int* v, int size,Operation op)
{
	build_max_heapBU(v, size,op);
	for (int i = size; i >= 2; i--)
	{
		op.count(3);
		int aux = v[0];
		v[0] = v[i - 1];
		v[i - 1] = aux;
		size = size - 1;
		max_heapify(v, 0, size,op);
	}
}

void demo()
{
	const int size = 20;
	int v[size];

    FillRandomArray(v, size, 10, 500, true, UNSORTED);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	QuickSortdemo(v, 0, size - 1,size);

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
		Operation op = profiler.createOperation("op_heapBU", i);
		CopyArray(m, v, i);//function to copy from an array to another
		heapsort_BU(v, i,op);
		Operation op1 = profiler.createOperation("op_QuickSort", i);
		CopyArray(v, m, i);
		QuickSort(v, 0, i - 1, i, op1);
		
	}
}

void insertSortRecursive(int* v, int size)
{
	if (size <= 1)
		return;
	insertSortRecursive(v, size - 1);
	int last = v[size - 1];
	int i = size - 2;
	while (i >= 0 && v[i] > last)
	{
		v[i + 1] = v[i];
		i--;
	}
	v[i + 1] = last;
}
void demoInsert()
{
	const int size = 20;
	int v[size];

	FillRandomArray(v, size, 10, 500, true, UNSORTED);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	insertSortRecursive(v, size);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

}

int main()
{
	demo();
	/*perf(0);

		profiler.createGroup("op_average","op_heapBU", "op_QuickSort");

		profiler.showReport();*/

			return 0;

}

