#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int array[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (array[j] > array[j + 1]) 
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void pbubble_sort(int arr[], int n)
#pragma omp parallel
{
    #pragma omp parallel for
	for (int i=0; i<n;i++)
	{
		for(int j=0; j<n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
		    {			
                swap(arr[j], arr[j+1]);		    	
		    }
        }        
	}
}



// Function to generate random array
void generate_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }
}

void printArray(int arr[], int n)
{
	
    cout<<"Sorted Array: ";	
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}	
	cout<<endl;	
}

int main()
{
	int n = 10000; 
    int arr[n];   
    
    generate_array(arr, n);

    
    double start_time = omp_get_wtime();
    bubble(arr, n);
    double end_time = omp_get_wtime();
    printf("Sequential bubble sort time: %f seconds\n", end_time - start_time);

    // Generate random array again for parallel sorting
    generate_array(arr, n);

 // Measure parallel bubble sort performance
    start_time = omp_get_wtime();
    pbubble_sort(arr, n);
    end_time = omp_get_wtime();
    printf("Parallel bubble sort time: %f seconds\n", end_time - start_time);

	
	return 0;
}
