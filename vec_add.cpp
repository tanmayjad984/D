#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define MAX 100

int main()
{
    int m1[MAX], m2[MAX], m3[MAX], i;

    srand(time(NULL)); // Initialize random seed

    printf("\n First Vector:\t");

    #pragma omp parallel for private(i)
    for(i=0; i<MAX; i++)
    {
        unsigned int seed = omp_get_thread_num();
        m1[i] = rand_r(&seed) % 1000;
    }

    for(i=0;i<MAX; i++)
    {
        printf("%d\t",m1[i]);
    }

    printf("\n Second Vector:\t");

    #pragma omp parallel for private(i)
    for(i=0; i<MAX; i++)
    {
        unsigned int seed = omp_get_thread_num();
        m2[i] = rand_r(&seed) % 1000;
    }

    for(i=0;i<MAX; i++)
    {
        printf("%d\t",m2[i]);
    }

    printf("\n Parallel-vector Addition:(m1,m2,m3)\t");

    #pragma omp parallel for private(i)
    for(i=0; i<MAX; i++)
    {
        m3[i] = m1[i] + m2[i];
    }

    for(i=0;i<MAX; i++)
    {
        printf("\n%d\t%d\t%d",m1[i], m2[i], m3[i]);
    }

    return 0;
}

