#pragma once
#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

// using namespace std;

void maxHeapify(float *max_heap, int i, int n);

void build_max_heap(float *max_heap, int n);

float ret_maximum(float *max_heap);