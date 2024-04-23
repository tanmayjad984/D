// implementing min max sum and average operations using parallel computing

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

// Function to generate random array
void generateRandomArray(int arr[], int n, int lower_bound, int upper_bound)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = lower_bound + rand() % (upper_bound - lower_bound + 1);
    }
}


// Function to find the sum of values in an array using parallel reduction
int findSum(int arr[], int n)
{
    int sum = 0;
	#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

// Function to find the average value in an array using parallel reduction
double findAverage(int arr[], int n)
{
    double avg = 0;
	#pragma omp parallel for reduction(+ : avg)
    for (int i = 0; i < n; i++)
    {
        avg += arr[i];
    }
    avg /= n;
    return avg;
}

int main()
{
    const int n = 100;
    int arr[n];
    int lower = 5;
    int upper = 78;

    // Generate random array
    generateRandomArray(arr, n, lower, upper);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;


    // Find sum of values
    int sum = findSum(arr, n);
    cout << "Sum of values: " << sum << endl;

    // Find average value
    double avg = findAverage(arr, n);
    cout << "Average value: " << avg << endl;

    return 0;
}

