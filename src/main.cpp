#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <climits>
#include "generator.h"
#include "sorting.h"
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

void callSort(int algorithm, vector<int>& values);

int main()
{
    while(true)
    {
        string input;

        cout << "Which sorting algorithm would you like to test?" << endl;
        cout << " 1. Selection Sort" << endl;
        cout << " 2. Bubble Sort" << endl;
        cout << " 3. Insertion Sort" << endl;
        cout << " 4. Shell Sort (gap = 2.2)" << endl;
        cout << " 5. Merge Sort" << endl;
        cout << " 6. Quick Sort" << endl;
        cout << " 7. Heap Sort" << endl;
        cout << " 8. Radix Sort" << endl;
        cout << " 9. Bucket Sort" << endl;
        cout << "10. Pancake Sort" << endl;
        cout << "11. Exit the utility" << endl;

        cin >> input;
        int algorithmSelection = stoi(input);
        if(algorithmSelection == 11)
            break; // Exits while(true) loop, ends program.
        if(algorithmSelection > 10 || algorithmSelection < 1)
        {
            cout << "Invalid input." << endl;
            continue; // Revert to main menu.
        }

        cout << "What type of array should be tested?" << endl;
        cout << "1. Randomized Array" << endl;
        cout << "2. Ascending Order (Sorted Order)" << endl;
        cout << "3. Descending Order (Reverse Order)" << endl;
        cin >> input;
        int arrayType = stoi(input);
        if(arrayType > 3 || arrayType < 1)
        {
            cout << "Invalid input." << endl;
            continue;
        }

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


        vector<int> sizes;
        vector<long> times;
        // Progress estimation calculations
        long double total = 0;
        for(int arrayLength = lower; arrayLength <= upper; arrayLength += interval)
            for(int i = 0; i < trials; i++)
                total += (arrayLength/1e120)*(arrayLength/1e120);

        long double count = 0;
        int yMax = INT_MIN;
        cout.flush();
        for(int arrayLength = lower; arrayLength <= upper; arrayLength += interval)
        {
            for(int i = 0; i < trials; i++)
            {
                // Generate the array based on user input.
                Gen values(arrayLength);
                if(arrayType == 1)
                    values.Randomize();
                else if(arrayType == 2)
                    values.Ascending();
                else if(arrayType == 3)
                    values.Descending();
                auto start = chrono::high_resolution_clock::now();
                // Call the sorting algorithm.
                callSort(algorithmSelection, values.vec);
                auto end = chrono::high_resolution_clock::now();
                auto executionTime = chrono::duration_cast<chrono::microseconds>(end - start);
                // Store the array length (x-coordinate)
                sizes.push_back(arrayLength);
                // Store the execution time (y-coordinate)
                times.push_back(executionTime.count());
                // Find max value. Needed for knowing the Y axis range to plot.
                if(executionTime.count() > yMax)
                    yMax = executionTime.count();

                // Progress Calculation and Output
                count += (arrayLength/1e120)*(arrayLength/1e120);
                cout << "[" << count / total * 100 << "%]                    \r"; // Spaces needed to overwrite all characters.
                cout.flush();
            }
        }
        cout << endl;

        // Get the name of the algorithm used to put in the title of the plot
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
                algorithmName = "Pancake Sort";
        }

        // Get the name of the test type to put in the title of the plot.
        string testType;
        switch(arrayType)
        {
            case 1:
                testType = "Arrays Randomized";
                break;
            case 2:
                testType = "Arrays in Sorted Order";
                break;
            case 3:
                testType = "Arrays in Reverse Sorted Order";
        }

        // Plotting
        plt::figure_size(1200, 780);
        plt::scatter(sizes, times);
        plt::title("Execution time of " + algorithmName + ", " + testType);
        plt::xlim(0,upper);
        plt::ylim(0, yMax);
        plt::xlabel("Array Size, n");
        plt::ylabel("Execution Time (Microseconds)");
        cout << "Would you like to save the plot? (Y/N)" << endl;
        cin >> input;
        if(input[0] == 'Y' || input[0] == 'y')
        {
            cout << "Enter a file name. Do not include a file extension." << endl;
            cin >> input;
            plt::save(input + ".png");
            cout << "Exported as " << input << ".png" << endl;
        }
        plt::show();
        cout << endl;
    }
    return 0;
}

void callSort(int algorithm, vector<int>& values)
{
    // Convert the user's number to the proper function call.
    switch(algorithm)
    {
        case 1:
            selection(values);
            break;
        case 2:
            BubbleSort(values);
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
            QuickSort(values, 0, values.size());
            break;
        case 7:
            HeapSort(values);
            break;
        case 8:
            RadixSort(values);
            break;
        case 9:
            bucket(values, INT_MAX);
            break;
        case 10:
            PancakeSort(values);
    }
}