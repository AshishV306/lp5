#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to merge two sorted subarrays
void merge(vector<int>&arr, int low, int mid, int high)
{
    vector<int> v;

    int left = low;
    int right = mid + 1;
    while (left <= mid && right <= high)
    {
        if (arr[left] < arr[right])
        {
            v.push_back(arr[left]);
            left++;
        }
        else
        {
            v.push_back(arr[right]);
            right++;
        }
    }
    while (left <= mid)
    {
        v.push_back(arr[left]);
        left++;
    }
    while (right <= high)
    {
        v.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++)
    {
        arr[i] = v[i - low];
    }
}

// Sequential merge sort
void mergeSort(vector<int>&arr, int low, int high)
{
    if (low == high)
    {
        return;
    }

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}


// Parallel merge sort
void mergeSortParallel(vector<int>&arr, int low, int high)
{
    if (low == high)
    {
        return;
    }
    
    #pragma omp parallel sections
    int mid = (low + high) / 2;
{
    #pragma omp section
    mergeSortParallel(arr, low, mid);
    #pragma omp section
    mergeSortParallel(arr, mid + 1, high);

}
    merge(arr, low, mid, high);
}

int main()
{

    int size = 10000;
    vector<int> arr(size);

    for (int i = 0, j = size; i < size; i++, j--)
    {
        arr[i] = j;
    }

    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seq_time = end - start;
    cout << seq_time.count() << " " << endl;

    vector<int> arr_parr(size);

    for (int i = 0, j = size; i < size; i++, j--)
    {
        arr_parr[i] = j;
    }

    start = chrono::high_resolution_clock::now();
    mergeSortParallel(arr_parr, 0, arr_parr.size() - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> par_time = end - start;
    cout << par_time.count() << endl;

    return 0;
}
