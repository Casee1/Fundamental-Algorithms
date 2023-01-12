/*InsersionSort we split the vector in two parts and we know the first one is always sorted 
* From the second part we choose the first number and compare it with the first part and we find its place
* BEST CASE: the vector is sorted
* AVERAGE CASE: random
* WORST CASE: the vector is in descending form
*/
/*BubbleSort we compare each element with the other elements and if one is bigger then other we make the switch
* BEST CASE: the vector is sorted
* WORST CASE: the vector is in descneding form
* AVERAGE CASE: random
*/
/*SelectionSort: we find the minimum from the vector and we put it in the first place 
BEST CASE:the vector is sorted
AVERAGE CASE: random
WORST CASE: the vector is sorted till n-1 and in the last position we have the minimum 
*/

#include <iostream>
#include "Profiler.h"

Profiler profiler("test"); 
using namespace std;

void InsertionSort(int* a, int size)
{
	Operation comp = profiler.createOperation("ins_comp", size); //to count the number of comparisons
	Operation assign = profiler.createOperation("ins_assig", size); //to count the number of assignments
	int aux;
	for (int i = 1; i < size; i++)
	{
		aux = a[i];
		assign.count();
		int j = i - 1;
		comp.count();
		while (j >= 0 && aux < a[j])
		{
			a[j + 1] = a[j];
			assign.count();
			j--;
		}

		if (j != i - 1)
		{
			assign.count();
			a[j + 1] = aux;
		}

	}
	profiler.addSeries("ins_op", "ins_assig", "ins_comp"); //creates a graph for a sum of comparisons and assignments
}

void SelectSort(int* a, int size)
{
	Operation comp = profiler.createOperation("sel_comp", size);
	Operation assign = profiler.createOperation("sel_assig", size);
	int aux,min;
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			comp.count();
			if (a[min] > a[j])
				min = j;
		}
		if (min != i)
		{
			assign.count(3);
			aux = a[min];
			a[min] = a[i];
			a[i] = aux;
		}
	}
	profiler.addSeries("sel_op", "sel_assig", "sel_comp");
}

void BubbleSort(int* a, int size)
{
	Operation comp = profiler.createOperation("bubble_comp", size);
	Operation assign = profiler.createOperation("bubble_assig", size);
	int i = 0, k = 1,aux,w=size-1;
	do
	{
		k = 0;
		for (i = 0; i < w; i++)
		{
			comp.count();
			if (a[i + 1] < a[i])
			{
				assign.count(3);
				k = 1;
				aux = a[i];
				a[i] = a[i + 1];
				a[i + 1] = aux;
			}
		}
		w--;
		comp.count();
	} while (k);
	profiler.addSeries("bubble_op", "bubble_assig", "bubble_comp");
}

void insertion_demo() {

	const int size = 20;
	int v[size];
	FillRandomArray(v, size, 10, 100, true, UNSORTED);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	InsertionSort(v, size);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

}

void bubble_demo() {
	int v[100] = {};
	int size = 100;

	FillRandomArray(v, size, 10, 500, true, UNSORTED);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n\n";

	BubbleSort(v, size);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

}

void selection_demo() {
	int v[100] = {};
	int size = 6;

	FillRandomArray(v, size, 6, 500, true, DESCENDING);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << "\n\n";

	SelectSort(v, size);

	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}

}
void perf(int cas)
{
	int const MAX_S = 5000;
	int const STEP = 100;
	int v[MAX_S], m[MAX_S];
	for (int i = 100; i <= MAX_S; i += STEP)
	{
		if (cas == 0)
			FillRandomArray(v, i, 10, 100000, false, UNSORTED); //function to generate a random array 
		else if (cas == 1)
			FillRandomArray(v, i, 10, 100000, false, ASCENDING);
		else
			FillRandomArray(v, i, 10, 100000, false, DESCENDING);
		CopyArray(m, v, i); //function to copy from an array to another
		InsertionSort(v, i);
		CopyArray(v, m, i);
		if (cas == 2)
		{
			FillRandomArray(v, i - 1, 10, 100000, false, ASCENDING);
			v[i - 1] = 1;
			SelectSort(v, i);
			CopyArray(v, m, i);
		}
		else
		{
			SelectSort(v, i);
			CopyArray(v, m, i);
		}

		BubbleSort(v, i);
		CopyArray(v, m, i);


	}

	if (cas == 0)
	{
		profiler.createGroup("Average_OP", "bubble_op", "ins_op", "sel_op"); //create a graph with the all 3 operations 
		profiler.createGroup("Average_assign", "bubble_assig", "ins_assig", "sel_assig");
		profiler.createGroup("Average_comp", "bubble_comp", "ins_comp", "sel_comp");
	}
	else if (cas == 1)
	{
		profiler.createGroup("Best_OP", "bubble_op", "ins_op", "sel_op");
		profiler.createGroup("Best_assign", "bubble_assig", "ins_assig", "sel_assig");
		profiler.createGroup("Best_comp", "bubble_comp", "ins_comp", "sel_comp");
	}
	else
	{
		profiler.createGroup("Worst_OP", "bubble_op", "ins_op", "sel_op");
		profiler.createGroup("Worst_assign", "bubble_assig", "ins_assig", "sel_assig");
		profiler.createGroup("Worst_comp", "bubble_comp", "ins_comp", "sel_comp");
	}
}

int main()
{
	/*perf(0); //average case 
	profiler.reset("BEST");
	perf(1); //best case
	profiler.reset("WORST");
	perf(2); //worst case 
	profiler.showReport();*/

	//insertion_demo();
	//bubble_demo();
	//selection_demo();
}