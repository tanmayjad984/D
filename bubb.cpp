#include<iostream>
#include<cstdlib>
#include<ctime>
#include<omp.h>

using namespace std;

// Bubble Sort algorithm
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to generate random array
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

// Function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to check if array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

// Function to measure execution time
double measureExecutionTime(void (*sortFunction)(int[], int), int arr[], int n, int n_threads)
{
    double start_time, end_time;
    omp_set_num_threads(n_threads);
    start_time = omp_get_wtime();
    sortFunction(arr, n);
    end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
	
    const int n = 100;
    int arr[n];
    int n_threads = omp_get_max_threads();
    
    // Generate random array
    generateRandomArray(arr, n);
    
    // Print unsorted array
    cout << "Unsorted array: " << endl;
    printArray(arr, n);
    
    // Measure execution time of Bubble Sort
    double bubbleSortSequentialTime = measureExecutionTime(bubbleSort, arr, n, 1);
    double bubbleSortParallelTime = measureExecutionTime(bubbleSort, arr, n, n_threads);
    
	// Print results
    cout << "Bubble Sort execution time with " << n_threads << " threads: " << bubbleSortParallelTime << " seconds" << endl;
    cout << "Bubble Sort execution time without parallelism: " << bubbleSortSequentialTime << " seconds" << endl;
    
	// Check if array is sorted
    if (isSorted(arr, n)) {
        cout << "Array is sorted" << endl;
    } else {
        cout << "Array is not sorted" << endl;
    }
    
	// Print sorted array
    cout << "Sorted array: " << endl;
    printArray(arr, n);
    return 0;
}

