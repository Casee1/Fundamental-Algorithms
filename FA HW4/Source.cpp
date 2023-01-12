#include <list>
#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler profiler("lists");
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

void min_heapify(list<int> v[], int i, int size,Operation op) //heapify it's the same like in the second homework but we change the condition to find the min value 
{
    int l = left(i);
    int r = right(i);
    int min_value = i;
    op.count();
    if (l < size && v[l].front() < v[i].front())
    {
        min_value = l;
    }
    else
        min_value = i;
    op.count();
    if (r < size && v[r].front() < v[min_value].front())
    {
        min_value = r;
    }
    op.count();
    if (min_value != i)
    {
        /*int aux = v[i].front();
        v[i].front() = v[min_value].front();
        v[min_value].front() = aux;*/
        op.count(3);
        swap(v[i], v[min_value]);
        min_heapify(v, min_value, size,op);
    }

}
void min_heapifydemo(list<int> v[], int i, int size) //heapify it's the same like in the second homework but we change the condition to find the min value 
{
    int l = left(i);
    int r = right(i);
    int min_value = i;
    if (l < size && v[l].front() < v[i].front())
    {
        min_value = l;
    }
    else
        min_value = i;
    if (r < size && v[r].front() < v[min_value].front())
    {
        min_value = r;
    }
    if (min_value != i)
    {
        /*int aux = v[i].front();
        v[i].front() = v[min_value].front();
        v[min_value].front() = aux;*/
        swap(v[i], v[min_value]);
        min_heapifydemo(v, min_value, size);
    }

}

void build_min_heapBU(list<int> v[], int size,Operation op) // we build the bottom up heap exactly like in the second homework
{
    for (int i = size / 2 - 1; i >= 0; i--)
        min_heapify(v, i, size,op);
}
void build_min_heapBUdemo(list<int> v[], int size) // we build the bottom up heap exactly like in the second homework
{
    for (int i = size / 2 - 1; i >= 0; i--)
        min_heapifydemo(v, i, size);
}


void Merge(int n, list<int> lists[], int k, Operation op) //Merge
{
    list<int>MergeList; 
    while (!lists->empty()) //we go throw the whole lists while it's not empty
    {
        op.count();
        build_min_heapBU(lists, k, op); //we call the build heap
        MergeList.push_back(lists[0].front()); // we put in the final list, the first element of the lists because it's the minimum
        op.count();
        lists[0].pop_front();//after we delete it 
        op.count();
        op.count();
        if (lists[0].empty()) // if the first list is empty we put the last list in the first position and after delete the last lists
        {
            op.count(3);
            swap(lists[0], lists[k - 1]);
            k--;
            build_min_heapBU(lists, k, op);
        }

    }
    //while (!MergeList.empty()) // while the list is not empty we print the elements from the list
    //{
    //    cout << MergeList.front() << " ";
    //    MergeList.pop_front(); // after printing the first element we delete it to not print it again 
    //}
}
void Mergedemo(int n, list<int> lists[], int k) //Merge
{
    list<int>MergeList;
    while (!lists->empty()) //we go throw the whole lists2 until it's not empty
    {
        build_min_heapBUdemo(lists, k); //we call the build heap
        MergeList.push_back(lists[0].front()); // we put in the final list, the first element of the lists because it's the minimum
        lists[0].pop_front();//after we delete it 
        if (lists[0].empty()) // if the first list is empty we put the last list in the first position and after delete the last lists
        {
            swap(lists[0], lists[k - 1]);
            k--;
            build_min_heapBUdemo(lists, k);
        }

    }
    cout << endl;
    while (!MergeList.empty()) // while the list is not empty we print the elements from the list
    {
        cout << MergeList.front() << " ";
        MergeList.pop_front(); // after printing the first element we delete it to not print it again 
    }
}

void generate(int n, int k,Operation op)
{
    list<int> lists[10000];
    //srand(time(0)); //function for generate random values each run
	int arr[100000]; //auxiliar array of integers to save the elements to put it in the lists
    int lenght[10000]; //here we save the lenght of each list
    int var = 0; // numaram cate elemente am generat pana atunci 
    int div = 0; //we use it to calculate the lenght of the list
    for (int i = 0; i < k-1; i++) //generate the lenght for all lists without the last one 
    {
        div = n - k - var;
        if (div <= 0)
        {
            div = 1;
        }
        lenght[i] = rand() % div+1;
        var = var + lenght[i];
    }
    lenght[k - 1] = n - var; //lenght for the last one  
    for (int i = 0; i < k; i++) //generate random sorted lists
    {
        FillRandomArray(arr, lenght[i], 10, 50000, true, ASCENDING);
        for (int j = 0; j < lenght[i]; j++)
        {   
            lists[i].push_back(arr[j]); //we put in the lists
        }
    }
    Merge(n, lists, k,op); //we call the function for merge
}
void generatedemo(int n, int k)
{
    list<int> lists[10000];
    srand(time(0)); //function for generate random values each run
    int arr[100000]; //auxiliar array of integers to save the elements to put it in the lists
    int lenght[10000]; //here we save the lenght of each list
    int var = 0; // numaram cate elemente am generat pana atunci 
    int div = 0; //we use it to calculate the lenght of the list
    for (int i = 0; i < k - 1; i++) //generate the lenght for all lists without the last one 
    {
        div = n - k - var;
        if (div <= 0)
        {
            div = 1;
        }
        lenght[i] = rand() % div + 1;
        var = var + lenght[i];
    }
    lenght[k - 1] = n - var; //lenght for the last one  
    for (int i = 0; i < k; i++) //generate random sorted lists
    {
        FillRandomArray(arr, lenght[i], 10, 50000, true, ASCENDING);
        for (int j = 0; j < lenght[i]; j++)
        {
            lists[i].push_back(arr[j]); //we put in the lists
        }
        for (int t : lists[i])
        {
            cout << t << " ";
            
        }
        cout << endl;
    }
    
    Mergedemo(n, lists, k); //we call the function for merge
}

void demo()
{
    list<int>H[500];
    generatedemo(17,4);


}

void n_variating() {

    for (int j = 0; j < 33; j++)
    {

        for (int i = 100; i <= 10000; i = i + 100) {
            Operation ops5 = profiler.createOperation("ops_5", i);
            generate(i, 5, ops5);
        }
        for (int i = 100; i <= 10000; i = i + 100) {
            Operation ops10 = profiler.createOperation("ops_10", i);
            generate(i, 10, ops10);
        }
        for (int i = 100; i <= 10000; i = i + 100) {
            Operation ops100 = profiler.createOperation("ops_100", i);
            generate(i, 100, ops100);
        }
    }
    profiler.divideValues("op5", 32);
    profiler.divideValues("op10", 32);
    profiler.divideValues("op100", 32);

    profiler.createGroup("comparison_vary_n", "ops_5", "ops_10", "ops_100");

    profiler.reset();

}
void k_variating() {
    for (int j = 0; j < 5; j++) {
        for (int i = 10; i <= 500; i = i + 10) {
            Operation ops = profiler.createOperation("ops_vary_k", i);
            generate(10000, i, ops);
        }
    }

    profiler.divideValues("ops_vary_k", 5);

    profiler.reset();

}

int main() {

    demo();
    //n_variating();
    //k_variating();
	return 0;
}