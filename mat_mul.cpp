#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int main()
{
    int r = 4, c = 5; // Define the number of rows and columns

    int **matrix = new int*[r];
    for(int i = 0; i < r; ++i)
        matrix[i] = new int[c];

    int *vector = new int[c];
    int *out = new int[r];

    srand(time(0)); // Initialize random seed

    cout << "\nInput Matrix:\n";
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            matrix[row][col] = rand() % 100;
            cout << "\t" << matrix[row][col];
        }
        cout << "\n";
    }

    cout << "\nInput Vector:\n";
    for (int col = 0; col < c; col++)
    {
        vector[col] = rand() % 100;
        cout << vector[col] << "\n";
    }

    cout << "\nParallel-vector Multiplication:\n";

    #pragma omp parallel for
    for (int row = 0; row < r; row++)
    {
        out[row] = 0;
        for (int col = 0; col < c; col++)
        {
            out[row] += matrix[row][col] * vector[col];
        }
    }

    for (int row = 0; row < r; row++)
    {
        cout << "\nvector[" << row << "]: " << out[row] << "\n";
    }

    // Deallocate memory
    for(int i = 0; i < r; ++i)
        delete [] matrix[i];
    delete [] matrix;
    delete [] vector;
    delete [] out;

    return 0;
}

