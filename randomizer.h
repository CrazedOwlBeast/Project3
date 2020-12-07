#include <vector>

using namespace std;

//RNG - stores ints as a vector and an array, also the max value if needed
//ints range from 1 to max

class RNG {
public:
    vector<int> vec;
    int* arr;
    int size;
    int max;
    RNG(int size);
    RNG(int size, int max);
};

//parameter: number of elements in array
RNG::RNG(int size) {
    srand(time(0));
    int r;
    this->size = size;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
        r = rand() % INT_MAX;
        arr[i] = r;
        vec.push_back(r);
    }
}

//parameters: number of elements, maximum element
RNG::RNG(int size, int max) {
    srand(time(0));
    int r;
    this->size = size;
    this->max = max;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
        r = rand() % max + 1;
        arr[i] = r;
        vec.push_back(r);
    }
}