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
	for (int i = 2000; i > 0; i--)
		nums.push_back(i);

	//PrintVector(nums);
	clock_t t = clock();
	int n = nums.size();
	QuickSort(nums, 0, n - 1);
	t = clock() - t;
	//PrintVector(nums);
	cout << endl;
	printf("It took %d clicks or %f seconds to execute the sort.", t, ((float)t / CLOCKS_PER_SEC));
	cout << endl;
	float time = (float)t / CLOCKS_PER_SEC;
	cout << "It took " << time << " seconds to sort." << endl;
}