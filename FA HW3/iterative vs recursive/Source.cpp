/* CRISTIAN CASIAN-CRISTI 30422
* QuickSort on worst case has the complexity of O(n^2)
* in average case is O(nlogn)
*/

#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler("test");

void insertSortRecursive(int* v, int size, Operation op)
{
	if (size <= 1) //base case
	{
		return;
	}
	insertSortRecursive(v, size - 1,op); //sort first n-1 elements
	op.count();
	// insert lase element at his correct position in sorted array
	int last = v[size - 1];
	int i = size - 2;
	//move first n-1 elements from the array, that are greater than the kay to one position ahead of their current position
	while (i >= 0 && v[i] > last)
	{
		op.count();
		op.count();
		v[i + 1] = v[i];
		i--;
	}
	op.count();
	v[i + 1] = last;
}

void insertSortRecursivedemo(int* v, int size)// i use this function for demo, it s the same like the previous one 
{
	if (size <= 1)
		return;
	insertSortRecursivedemo(v, size - 1);
	int last = v[size - 1];
	int i = size - 2;
	while (i >= 0 && v[i] > last)
	{
		v[i + 1] = v[i];
		i--;
	}
	v[i + 1] = last;
}

void InsertionSort(int* a, int size) // insertion iterative it's the same like that one in the first homework
{
	Operation op = profiler.createOperation("ins_op", size); //to count 
	int aux;
	for (int i = 1; i < size; i++)
	{
		aux = a[i];
		op.count();
		int j = i - 1;
		while (j >= 0 && aux < a[j])
		{
			op.count();
			a[j + 1] = a[j];
			op.count();
			j--;
		}

		if (j != i - 1)
		{
			op.count();
			a[j + 1] = aux;
		}

	}
}

void demo()
{
	const int size = 20;
	int a[size];

	FillRandomArray(a, size, 10, 500, true, UNSORTED);

	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";

	insertSortRecursivedemo(a, size);

	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";

}

void perf(int cas)
{
	int const MAX_S = 5000;
	int const STEP = 100;
	int v[MAX_S], m[MAX_S];
	for(int j=1;j<=5;j++)
	{
		for (int i = 100; i <= MAX_S; i += STEP)
		{
			if (cas == 0)
				FillRandomArray(v, i, 10, 5000, false, UNSORTED); //function to generate a random array unsorted for average case 
			else if (cas == 1)
				FillRandomArray(v, i, 10, 5000, false, DESCENDING); // function to generate an descending array for worst case 
			else
				FillRandomArray(v, i, 10, 5000, false, ASCENDING); //function to generate an ascending array for best case
			CopyArray(m, v, i);//function to copy from an array to another
			InsertionSort(v, i);
			CopyArray(v, m, i);
			Operation op1 = profiler.createOperation("Recursive_op", i); //to count the operations
			insertSortRecursive(v, i, op1);
			CopyArray(v, m, i);

			profiler.startTimer("Iterative", i); // here we start the timer
			InsertionSort(v, i);   //we call the function
			profiler.stopTimer("Iterative", i); // we stop the timer

			CopyArray(v, m, i);
			profiler.startTimer("Recursive", i);
			insertSortRecursive(v, i, op1);
			profiler.stopTimer("Recursive", i);
		}
	}
}

int main()
{
	demo();
	perf(0);
	profiler.divideValues("ins_op", 5);
	profiler.divideValues("Recursive_op", 5);

	profiler.createGroup("op_average", "ins_op", "Recursive_op");
	profiler.createGroup("Time_average", "Iterative", "Recursive");

	profiler.reset("WORST");

	perf(1);
	profiler.divideValues("ins_op", 5);
	profiler.divideValues("Recursive_op", 5);

	profiler.createGroup("op_worst", "ins_op", "Recursive_op");
	profiler.createGroup("Time_worst", "Iterative", "Recursive");


	profiler.showReport();
}