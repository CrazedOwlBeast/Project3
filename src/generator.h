#pragma once
#include <vector>
#include <limits.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Gen class stores an array and vector (for flexibility). Constructor requires a size for array initialization.
// Class member functions are used to populate the array and vector with values. 

class Gen {
public:
    vector<int> vec;
    int* arr;
    int size;
    int max;
    Gen(int size);
    void Randomize();
    void Ascending();
    void Descending();
};

//parameter: number of elements in array
Gen::Gen(int size) {
    this->size = size;
    arr = new int[size];
}

void Gen::Randomize()
{
    vec.clear();
    srand(time(0));
    int r;
    for (int i = 0; i < size; i++) {
        r = rand() % INT_MAX;
        arr[i] = r;
        vec.push_back(r);
    }
}

void Gen::Ascending()
{
    vec.clear();
    for (int i = 0; i < size; i++) {
        arr[i] = i;
        vec.push_back(i);
    }
}

void Gen::Descending()
{
    vec.clear();
    for (int i = 0; i < size; i++) {
        arr[i] = size - 1 - i;
        vec.push_back(size - 1 - i);
    }
}