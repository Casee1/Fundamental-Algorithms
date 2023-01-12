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
void QuickSortdemo(int* v, int low, int high) // the same but i used it to demo
{

	if (low < high)
	{

		int mid = Partitiondemo(v, low, high);
		QuickSortdemo(v, low, mid - 1);
		QuickSortdemo(v, mid + 1, high);
	}

}

int Partition(int* v, int low, int high, Operation op)
{
	op.count();
	int pivot = v[high]; //consider the last element as pivot and moves all smaller element to left of it and grater elements to right
	int leftwall = low - 1; //index of smaller element and indicates the right position of pivot found
	for (int i = low; i < high; i++)
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
void QuickSort(int* v, int low, int high, Operation op)
{

	if (low < high)
	{
		op.count();
		int mid = Partition(v, low, high, op); //partitioning index, v[mid] is now at right place
		QuickSort(v, low, mid - 1, op); //separately sort elements before and after partition
		QuickSort(v, mid + 1, high, op);
	}

}



void InsertionSort(int* a, int size,Operation op)
{
	int aux;
	for (int i = 1; i < size; i++)
	{
		op.count();
		aux = a[i];
		int j = i - 1;
		while (j >= 0 && aux < a[j])
		{
			op.count();
			a[j + 1] = a[j];
			j--;
		}
		op.count();
		if (j != i - 1)
		{
			op.count();
			a[j + 1] = aux;
		}

	}
}
void InsertionSortdemo(int* a, int size)
{
	int aux;
	for (int i = 1; i < size; i++)
	{
		aux = a[i];
		int j = i - 1;
		while (j >= 0 && aux < a[j])
		{
			a[j + 1] = a[j];
			j--;
		}

		if (j != i - 1)
		{
			a[j + 1] = aux;
		}

	}
}



void QuickHybrid(int* v, int left, int right,int threshold,Operation op)
{
	if (right <= left)
		return;
	op.count();
	int size = right - left + 1;
	if (size > threshold)
	{
		op.count();
		int mid = Partition(v, left, right, op);
		op.count();
		QuickHybrid(v, left, mid - 1, threshold,op);
		QuickHybrid(v, mid + 1, right, threshold,op);
	}
	else
	{
		op.count();
		InsertionSort(v + left, size,op);
	}
}
void QuickHybriddemo(int* v, int left, int right, int threshold)
{
	if (right <= left)
		return;
	int size = right - left + 1;
	if (size > threshold)
	{
		int mid = Partitiondemo(v, left, right);
		QuickHybriddemo(v, left, mid - 1, threshold);
		QuickHybriddemo(v, mid + 1, right, threshold);
	}
	else
	{
		InsertionSortdemo(v + left, size);
	}
}



void demo()
{
	int v[31],y[31];
	FillRandomArray(v, 15, 10, 1000, true, UNSORTED);
	CopyArray(y, v, 15);
	QuickHybriddemo(y, 0, 15, 10);
	for (int i = 1; i <= 15; i++)
	{
		cout << y[i] << " ";
	}
	cout << endl;
	CopyArray(y, v, 15);
	QuickSortdemo(y, 0, 15);
	for (int i = 0; i < 15; i++)
	{
		cout << y[i] << " ";
	}
	cout << endl;

}

void perf()
{
	int step = 100;
	const int max_size = 10000;
	int v[max_size], y[max_size];
	for (int j = 1; j <= 5; j++)
	{
		for (int i = 100; i <= max_size; i = i + step)
		{
			Operation op = profiler.createOperation("op", i); //quick normal
			Operation op1 = profiler.createOperation("op1", i); //quick hybrid
			FillRandomArray(v, i, 1, 10000, true, UNSORTED);
			CopyArray(y, v, i);
			QuickHybrid(y, 0, i, 20, op1);
			CopyArray(y, v, i);
			QuickSort(y, 0, i, op);
			if (i == max_size)
			{
				for (int threshold = 10; threshold <= 100; threshold++)
				{
					Operation op2 = profiler.createOperation("op2", threshold);
					CopyArray(y, v, i);
					QuickHybrid(y, 0, i, threshold,op2);
				}
			}
			profiler.startTimer("QuickHybrid", i);
			for (int test = 1; test <= 20; test++)
			{
				CopyArray(y, v, i);
				QuickHybrid(y, 0, i, 20, op1);
			}
			profiler.stopTimer("QuickHybrid", i);

			profiler.startTimer("Quick", i);
			for (int test = 1; test <= 20; test++)
			{
				CopyArray(y, v, i);
				QuickSort(y, 0, i, op);
			}
			profiler.stopTimer("Quick", i);

		}
	}
	profiler.divideValues("op", 5);
	profiler.divideValues("op1", 5);
	profiler.divideValues("op2", 5);
	profiler.createGroup("operation", "op", "op1");
	profiler.createGroup("time", "Quick", "QuickHybrid");
	profiler.showReport();
}

int main()
{
	//demo();
	perf();
}