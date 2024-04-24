#include <iostream>
#include <omp.h>

using namespace std;

// Function to find the minimum value in an array
int minval(int arr[], int n)
{
    int minval = arr[0];
#pragma omp parallel for reduction(min : minval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < minval)
            minval = arr[i];
    }
    return minval;
}

// Function to find the maximum value in an array
int maxval(int arr[], int n)
{
    int maxval = arr[0];
#pragma omp parallel for reduction(max : maxval)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxval)
            maxval = arr[i];
    }
    return maxval;
}

// Function to find the sum of elements in an array
int sum(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

// Function to find the average of elements in an array
int average(int arr[], int n)
{
    return (double)sum(arr, n) / n;
}

int main()
{
    int n = 5;
    int arr[] = {1, 2, 3, 4, 5};

    // Finding and printing the minimum value
    cout << "The minimum value is: " << minval(arr, n) << '\n';

    // Finding and printing the maximum value
    cout << "The maximum value is: " << maxval(arr, n) << '\n';

    // Finding and printing the sum of elements
    cout << "The summation is: " << sum(arr, n) << '\n';

    // Finding and printing the average of elements
    cout << "The average is: " << average(arr, n) << '\n';

    return 0;
}
