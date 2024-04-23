// implementing min max sum and average operations using parallel computing


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// Function to generate random array
void generateRandomArray(int arr[], int n, int lower_bound, int upper_bound) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = lower_bound + rand() % (upper_bound - lower_bound + 1);
    }
}


// Function to find the minimum value in an array using parallel reduction
int findMin(int arr[], int n) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
int findMax(int arr[], int n) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}


int main() {
    const int n = 10;
    int arr[n];
    int lower = 24;
    int upper = 78;

    // Generate random array
    generateRandomArray(arr, n, lower, upper);
    
    for(int i = 0; i < n; i ++){
    	cout << arr[i] << " ";
	}
	cout << endl;

    // Find minimum value
    int min_val = findMin(arr, n);
    cout << "Minimum value: " << min_val << endl;

    // Find maximum value
    int max_val = findMax(arr, n);
    cout << "Maximum value: " << max_val << endl;

    return 0;
}

