#include <iostream>
#include <string>
// #include "defn.h"
#include <typeinfo>
#include <cstring>

using namespace std;

void maxHeapify(float *max_heap, int i, int n)
{
	int largest = i;
	int l = 2*i;
	int r = 2*i+1;

	if(l<n && max_heap[l]>max_heap[i])
	{
		largest = l;
	}
	if(r<n && max_heap[largest] < max_heap[r])
	{
		largest = r;
	}

	if(largest!=i)
	{
		float temp = max_heap[largest];
		max_heap[largest] = max_heap[i];
		max_heap[i] = temp;

		maxHeapify(max_heap,largest,n);
	}
}

void build_max_heap(float *max_heap, int n)
{
	for(int i=n/2;i>=0;i--)
	{
		maxHeapify(max_heap,i,n);
	}
}