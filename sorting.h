#include <vector>
#include <cmath>

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
    int n = arr.size();

    int index = 0;
    vector<vector<int>> buckets;
    for (int i = 0; i < n; i++) {
        vector<int> temp;
        buckets.push_back(temp);
    }

    for (int i = 0; i < n; i++) {
        index = floor(n * arr[i] / (max + 1));
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