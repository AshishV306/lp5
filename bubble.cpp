#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void serial_bubble(int arr[], int n) {
    bool swapped;
    for (int i=0; i<n-1; i++) {
        swapped = false;
        for (int j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}

void parallel_bubble(int arr[], int n) {
    bool swapped;
    // #pragma omp parallel for
    for (int i=0; i<n-1; i++) {
        swapped = false;

        #pragma omp parallel for shared(arr, swapped)
        for (int j=0; j<n-i-1; j++) {
          if (arr[j] > arr[j+1]) {
            #pragma omp critical
            {
              swap(arr[j], arr[j+1]);
              swapped = true;
            }
          }
        }
            
        if(!swapped) {
            break;
        }
    }
}



int main()
{
    // Set up variables
    const int n = 10000;
    int arr[n];
    int brr[n];
    double start_time, end_time;

    // Create an array with numbers starting from n to 1
    for (int i = 0, j = n; i < n; i++, j--){
        arr[i] = j;
    }

    // Sequential time
    auto start = chrono::high_resolution_clock::now();
    serial_bubble(arr, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seq_time = end - start;
    cout << seq_time.count() << " " << endl;

    for (int i = 0, j = n; i < n; i++, j--){
        brr[i] = j;
    }

    //parallel
    auto startp = chrono::high_resolution_clock::now();
    parallel_bubble(brr, n);
    auto endp = chrono::high_resolution_clock::now();
    chrono::duration<double> seq_timep = endp - startp;
    cout << seq_timep.count() << " " << endl;
}