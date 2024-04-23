#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Merge two subarrays of arr[]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
// Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort
void sequential_merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sequential_merge_sort(arr, l, m);
        sequential_merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
// Parallel merge sort with OpenMP
void parallel_merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_merge_sort(arr, l, m);

            #pragma omp section
            parallel_merge_sort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Function to generate random array
void generate_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }
}

// Function to print array
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 10000; // Size of the array
    int arr[n];

    // Generate random array
    generate_array(arr, n);

    // Measure sequential merge sort performance
    double start_time = omp_get_wtime();
    sequential_merge_sort(arr, 0, n - 1);
    double end_time = omp_get_wtime();
    printf("Sequential merge sort time: %f seconds\n", end_time - start_time);

    // Generate random array again for parallel sorting
    generate_array(arr, n);

    // Measure parallel merge sort performance
    start_time = omp_get_wtime();
    parallel_merge_sort(arr, 0, n - 1);
    end_time = omp_get_wtime();
    printf("Parallel merge sort time: %f seconds\n", end_time - start_time);

    return 0;
}