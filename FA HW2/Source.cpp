/* CRISTIAN CASIAN-CRISTI 30422
* HOMEWORK 2 HEAP SORT
* BOTTOM_UP HAS THE COMPLEXITY 0(n)
* TOP_DOWN HAS THE COMPLEXITY O(nlogn)
*/




#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler("test");

int parent(int i)
{
    return (i -1)/2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;

}

void max_heapify(int* v, int i, int size, Operation comp, Operation assign) //heapify
{
    int l = left(i);
    int r = right(i);
    int max_value = 0;
    if (l < size && v[l] > v[i])
    {
        max_value = l;
        comp.count();
        assign.count();
    }
    else
        max_value = i;
    if (r < size && v[r] > v[max_value])
    {
        max_value = r;
        comp.count();
        assign.count();
    }
    if (max_value != i)
    {
        assign.count(3);
        int aux = v[i];
        v[i] = v[max_value];
        v[max_value] = aux;
        max_heapify(v, max_value, size,comp,assign);
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

void build_max_heapBU(int* v, int size) // we build the bottom up heap
{
    Operation comp = profiler.createOperation("heapBU_comp", size);
    Operation assign = profiler.createOperation("heapBU_assgin", size);
    for (int i = size / 2 - 1; i >= 0; i--)
        max_heapify(v, i, size, comp, assign);
}

void heapsort_BU(int* v, int size)
{
    build_max_heapBU(v, size);
    for (int i = size; i >= 2; i--)
    {
        int aux = v[0];
        v[0] = v[i-1];
        v[i-1] = aux;
        size=size-1;
        max_heapifydemo(v, 0, size);
    }
}
void push_heap(int* v, int i, Operation comp, Operation assign) //push function for top down 
{
    while (i > 0 && v[i] > v[parent(i)])
    {
        comp.count();
        assign.count(3);
        int aux = v[i];
        v[i] = v[parent(i)];
        v[parent(i)] = aux;
        i = parent(i);
    }
}

void build_heap_TD(int* v, int size) // we create de top down heap
{
    Operation comp = profiler.createOperation("heapTD_comp", size);
    Operation assign = profiler.createOperation("heapTD_assgin", size);
    for (int i = 0; i < size; i++)
        push_heap(v, i, comp, assign);
}

void heapsort_TD(int* v, int size) //top down sort
{
    build_heap_TD(v, size);
    for (int i = size; i >= 2; i--)
    {
        int aux = v[0];
        v[0] = v[i - 1];
        v[i - 1] = aux;
        size = size - 1;
        max_heapifydemo(v, 0, size);
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
            FillRandomArray(v, i, 10, 5000, false, UNSORTED); //function to generate a random array unsorted for average case 
        else
            FillRandomArray(v, i, 10, 5000, false, ASCENDING); // function to generate an ascending array for worst case 
        CopyArray(m, v, i); //function to copy from an array to another 
        build_max_heapBU(v, i);
        CopyArray(v, m, i);
        build_heap_TD(v, i);
    }
}

void demoBU() 
{
    const int size = 20;
    int v[size];
    FillRandomArray(v, size, 10, 100, true, UNSORTED);

    for (int i = 0; i < size; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";

   heapsort_BU(v, size);

    for (int i = 0; i < size; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void demoTD()
{
    const int size = 20;
    int v[size];
    FillRandomArray(v, size, 10, 100, true, UNSORTED);

    for (int i = 0; i < size; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";

    heapsort_TD(v, size);

    for (int i = 0; i < size; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main()
{
    demoBU();
    cout << "\n";
    demoTD();
    /*perf(0);
    profiler.addSeries("op_heapBU", "heapBU_assgin", "heapBU_comp");
    profiler.addSeries("op_heapTD", "heapTD_assgin", "heapTD_comp");

    profiler.createGroup("op", "op_heapBU", "op_heapTD");
    profiler.createGroup("assign", "heapBU_assgin", "heapTD_assgin");
    profiler.createGroup("comp", "heapBU_comp", "heapTD_comp");

    profiler.reset("WORST");

    perf(1);
    profiler.addSeries("op_heapBU", "heapBU_assgin", "heapBU_comp");
    profiler.addSeries("op_heapTD", "heapTD_assgin", "heapTD_comp");

    profiler.createGroup("op_WORST", "op_heapBU", "op_heapTD");
    profiler.createGroup("assign_WORST", "heapBU_assgin", "heapTD_assgin");
    profiler.createGroup("comp_WORST", "heapBU_comp", "heapTD_comp");

    profiler.showReport();*/
    return 0;
}