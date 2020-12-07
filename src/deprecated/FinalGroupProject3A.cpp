#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

//TODO:
// - Timer
// - Quick Sort
// - Heap Sort
// - Bubble Sort
// - Pancake Sort
// - Counting Sort (if done with everything else)
// - Radix Sort (if done with every thing else)

void SwapPos(int* a, int* b) // Don't really need this, can use std swap instead
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
			swap(v[up], v[down]);
	}

	swap(v[low], v[down]);
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
int FindMaxIndex(vector<int>& v, int size)
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
		int maxIndex = FindMaxIndex(v, currSize);
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

void PrintVector(vector<int> v)
{
	cout << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> nums;
	for (int i = 20; i > 0; i--)
		nums.push_back(i);

	int n = nums.size();
	PrintVector(nums);

	clock_t t = clock();
	RadixSort(nums);
	//QuickSort(nums, 0, n - 1);
	t = clock() - t;

	PrintVector(nums);
	cout << endl;
	printf("It took %d clicks or %f seconds to execute the sort.", t, ((float)t / CLOCKS_PER_SEC));
	cout << endl;
	float time = (float)t / CLOCKS_PER_SEC;
	cout << "It took " << time << " seconds to sort." << endl;
}