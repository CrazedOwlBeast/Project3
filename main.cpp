#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "matplotlibcpp.h"
#include <climits>
#include "randomizer.h"
#include "sorting.h"

using namespace std;
namespace plt = matplotlibcpp;

void CompareAlgorithms();
void SpecialCases();
void callSort(int algorithm, vector<int>& values);

int main()
{
    while(true)
    {
        string input;
        cout << "Main Menu. Select an option." << endl;
        cout << "1. Compare Algorithms" << endl;
        cout << "2. Special Cases" << endl;
        cout << "3. End" << endl;
        cin >> input;
        if(input[0] == '3')
            break;
        if(input[0] == '1')
        {
            CompareAlgorithms();
        }
        else if(input[0] == '2')
        {
            SpecialCases();
        }
        else
            cout << "Invalid input. Please type a number from 1 to 3." << endl;
    }
    return 0;
}

void CompareAlgorithms()
{
    string input;
    vector<int> arrayLengths;
    cout << "What range of array sizes should be tested? Enter a lower bound, upper bound, and interval separated by spaces. Example: 10 1000 10" << endl;
    cin >> input;
    int lower = stoi(input);
    cin >> input;
    int upper = stoi(input);
    cin >> input;
    int interval = stoi(input);

    cout << "How many trials should be done for each size?" << endl;
    cin >> input;
    int trials = stoi(input);

    cout << "Which sorting algorithm would you like to test?" << endl;
    cout << "1.  Selection Sort" << endl;
    cout << "2.  Bubble Sort" << endl;
    cout << "3.  Insertion Sort" << endl;
    cout << "4.  Shell Sort (gap = 2.2)" << endl;
    cout << "5.  Merge Sort" << endl;
    cout << "6.  Quick Sort" << endl;
    cout << "7.  Heap Sort" << endl;
    cout << "8.  Radix Sort" << endl;
    cout << "9.  Bucket Sort" << endl;
    cout << "10. Counting Sort" << endl;
    cout << "11. Pancake Sort" << endl;

    cin >> input;
    int algorithmSelection = stoi(input);
    if(algorithmSelection > 11 || algorithmSelection < 1)
    {
        cout << "Invalid input." << endl;
        return;
    }

    vector<int> sizes;
    vector<long> times;
    int totalTrials = trials * ((upper - lower) / interval + 1);
    int count = 0;
    int yMax = INT_MIN;
    cout << "[0/" << arrayLengths.size() * trials << "]\r";
    cout.flush();
    for(int arrayLength = lower; arrayLength <= upper; arrayLength += interval)
    {
        for(int i = 0; i < trials; i++)
        {
            RNG values(arrayLength);
            auto start = chrono::high_resolution_clock::now();
            callSort(algorithmSelection, values.vec);
            auto end = chrono::high_resolution_clock::now();
            auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start);
            sizes.push_back(arrayLength);
            times.push_back(executionTime.count());
            if(executionTime.count() > yMax)
                yMax = executionTime.count();
            count++;
            cout << "[" << count << "/" << totalTrials << "]\r";
            cout.flush();
        }
    }
    cout << endl;

    string algorithmName;
    switch(algorithmSelection)
    {
        case 1:
            algorithmName = "Selection Sort";
            break;
        case 2:
            algorithmName = "Bubble Sort";
            break;
        case 3:
            algorithmName = "Insertion Sort";
            break;
        case 4:
            algorithmName = "Shell Sort";
            break;
        case 5:
            algorithmName = "Merge Sort";
            break;
        case 6:
            algorithmName = "Quick Sort";
            break;
        case 7:
            algorithmName = "Heap Sort";
            break;
        case 8:
            algorithmName = "Radix Sort";
            break;
        case 9:
            algorithmName = "Bucket Sort";
            break;
        case 10:
            algorithmName = "Counting Sort";
            break;
        case 11:
            algorithmName = "Pancake Sort";
    }

    plt::figure_size(1200, 780);
    plt::scatter(sizes, times);
    plt::title("Execution time of " + algorithmName);
    plt::xlim(0,upper);
    plt::ylim(0, yMax);
    plt::xlabel("Array Size, n");
    plt::ylabel("Execution Time (Microseconds)");
    plt::show();

    cout << "Would you like to save this plot?" << endl;

}

void SpecialCases()
{

}

void callSort(int algorithm, vector<int>& values)
{
    switch(algorithm)
    {
        case 1:
            selection(values);
            break;
        case 2:
//            bubble(values);
            break;
        case 3:
            insertion(values);
            break;
        case 4:
            shell(values);
            break;
        case 5:
            merge(&values[0], 0, values.size() - 1);
            break;
        case 6:
//            quick(values);
            break;
        case 7:
//            heap(values);
            break;
        case 8:
//            radix(values);
            break;
        case 9:
            bucket(values, INT_MAX);
            break;
        case 10:
//            counting(values);
            break;
        case 11:
//            pancake(values);
            break;
    }
}