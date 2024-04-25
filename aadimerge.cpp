#include<iostream>
#include<omp.h>
#include<chrono>

using namespace std;

void merge(int list[], int first, int mid, int last) {
	int temp[last+1];
	int i = first, j = mid+1, k = 0;

	// #pragma omp parallel for
	while(i<=mid || j<=last) {
		if(i<=mid && j<=last) {
			if(list[i] < list[j]) {
				temp[k++] = list[i++];
			}
			else {
				temp[k++] = list[j++];
			}
		}
		else if(i<=mid) {
			temp[k++] = list[i++];
		}
		else if(j<=last) {
			temp[k++] = list[j++];
		}
	}

	for(i=first, j=0; i<=last; i++, j++) {
		list[i] = temp[j];
	}
}

void mergesort(int list[], int first, int last) {
	if(first < last) {
    	int mid = (first + last) / 2;
    	#pragma omp parallel sections
    	{
        	#pragma omp section
        	{
            	mergesort(list, first, mid);
        	}
        	#pragma omp section
        	{
            	mergesort(list, mid+1, last);
        	}
    	}
    	merge(list, first, mid, last);
	}
}

void printList(int list[], int n) {
	for(int i=0; i<n; i++) {
		cout<<list[i]<<" ";
	}
}


int main() {
	int *list;
	cout<<"Enter No of Elements: ";
	cin>>n;
	int n = 10000;
	list = new int[n];

	

    for (int i = 0, j = n; i < n; i++, j--)
    {
        list[i] = j;
    }

	cout<<"Enter Elements:"<<endl;
	for(int i=0; i<n; i++) {
    	cin>>list[i];
	}
  auto start_p = chrono::high_resolution_clock::now();
	mergesort(list, 0, n-1);
  auto end_p = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> time_p = end_p - start_p;
	
	cout<<"Sorted Array: ";
	printList(list, n);
  cout<<"\nExecution Time: "<<time_p.count()<<"ms"<<endl;

	return 0;
}

