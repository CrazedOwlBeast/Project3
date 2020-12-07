#pragma once
#include <vector>
#include <cmath>

using namespace std;

//Selection
void selection(vector<int> &arr) {
    int min;
    for (int i = 0; i < arr.size()-1; i++) {
        min = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[min])
                min = j;
        if (arr[min] < arr[i])
            swap(arr[i], arr[min]);
    }
}

//Insertion
void insertion(vector<int> &arr) {
    int val, j;
    for (int i = 1; i < arr.size(); i++) {
        val = arr[i];
        j = i;
        while (j > 0 && val < arr[j-1]) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = val;
    }
}

//Shell - gap = n/2.2
void shell(vector<int>& arr) {
    int gap = arr.size() / 2;
    while (gap > 0) {
        for (int i = 0; i < arr.size() - gap; i++)
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                for (int j = i; j > gap; j = j-gap)
                    if (arr[j] < arr[j - gap])
                        swap(arr[j], arr[j - gap]);
                    else
                        break;
            }
        if (gap == 2)
            gap = 1;
        else
            gap = gap / 2.2;
    }

}

//Merge
void merge(int arr[], int front, int back) {
    if (front < back) {
        int mid = (front + back) / 2;
        merge(arr, front, mid);
        merge(arr, mid + 1, back);

        int size1 = mid - front + 1;
        int size2 = back - mid;
        int* sub1 = new int[size1];
        int* sub2 = new int[size2];
        for (int i = 0; i < size1; i++) {
            sub1[i] = arr[i + front];
        }
        for (int i = 0; i < size2; i++) {
            sub2[i] = arr[i + mid + 1];
        }

        int i = 0;
        int j = 0;
        int k = front;
        while (i < size1 && j < size2) {
            if (sub1[i] < sub2[j]) {
                arr[k] = sub1[i];
                i++;
            }
            else {
                arr[k] = sub2[j];
                j++;
            }
            k++;
        }

        while (i < size1) {
            arr[k] = sub1[i];
            i++;
            k++;
        }
        while (j < size2) {
            arr[k] = sub2[j];
            j++;
            k++;
        }

        delete[] sub1;
        delete[] sub2;
    }
}

//Bucket
//max = maximum value of the arr
void bucket(vector<int>& arr, int max) {
    long long n = arr.size();

    long long index = 0;
    vector<vector<int>> buckets;
    for (int i = 0; i < n; i++) {
        vector<int> temp;
        buckets.push_back(temp);
    }

    for (int i = 0; i < n; i++) {
        index = floor(n * arr[i] / ((long long)max + 1));
        buckets[index].push_back(arr[i]);
    }

    for (int i = 0; i < n; i++) {
        insertion(buckets[i]);
    }

    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            arr[k++] = buckets[i][j];
}

void SwapPos(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(vector<int>& v, int low, int high)
{
    int pivot = v[low], up = low, down = high;

    while (up < down)
    {
        for (int i = up; i < high; i++)
        {
            if (v[up] > pivot)
                break;
            up++;
        }
        for (int i = high; i > low; i--)
        {
            if (v[down] < pivot)
                break;
            down--;
        }

        if (up < down)
            SwapPos(&v[up], &v[down]);
    }

    SwapPos(&v[low], &v[down]);
    return down;
}

void QuickSort(vector<int>& v, int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(v, low, high);
        QuickSort(v, low, pivot - 1);
        QuickSort(v, pivot + 1, high);
    }
}

void Heapify(vector<int>& v, int n, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (n > left && v[left] > v[i])
    {
        largest = left;
    }
    if (n > right && v[right] > v[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(v[i], v[largest]);
        Heapify(v, n, largest);
    }
}

void HeapSort(vector<int>& v)
{
    int size = v.size();
    for (int i = (size / 2) - 1; i >= 0; i--)
        Heapify(v, size, i);

    for (int i = size - 1; i > 0; i--)
    {
        swap(v[0], v[i]);
        Heapify(v, i, 0);
    }
}

void BubbleSort(vector<int>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < v.size() - i - 1; ++j)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void Flip(vector<int>& v, int endIndex)
{
    int temp, i = 0;
    while (i < endIndex)
    {
        temp = v[i];
        v[i] = v[endIndex];
        v[endIndex] = temp;
        i++;
        endIndex--;
    }
}

int FindMax(vector<int>& v, int size)
{
    int maxIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (v[i] > v[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

void PancakeSort(vector<int>& v)
{
    int size = v.size();
    for (int currSize = size; currSize > 1; currSize--)
    {
        int maxIndex = FindMax(v, currSize);
        if (maxIndex != currSize - 1)
        {
            Flip(v, maxIndex);
            Flip(v, currSize - 1);
        }
    }
}

int GetMax(vector<int>& v)
{
    int max = v[0];
    for (int i = 1; i < v.size(); i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

void CountSort(vector<int>& v, int decPlace)
{
    vector<int> output;
    vector<int> count;
    count.resize(10);
    output.resize(v.size());

    for (int i = 0; i < v.size(); i++)
        count[(v[i] / decPlace) % 10]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = v.size() - 1; i >= 0; i--)
    {
        output[count[(v[i] / decPlace) % 10] - 1] = v[i];
        count[(v[i] / decPlace) % 10]--;
    }

    for (int i = 0; i < v.size(); i++)
        v[i] = output[i];
}

void RadixSort(vector<int>& v)
{
    int max = GetMax(v);
    for (int decPlace = 1; (max / decPlace) > 0; decPlace *= 10)
        CountSort(v, decPlace);
}