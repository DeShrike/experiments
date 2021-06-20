#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "sort1.hpp"

#define MAX 500000
#define MODULO 5000

using namespace std;

void swap(int a[], int x, int y)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void sort(int arr[], int size)
{
    for (int i; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[i])
            {
                swap(arr, i, j);
            }
        }
    }
}

void print_array(string title, int arr[], int count)
{
    cout << title << endl;
    for (int i = 0; i < count; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    int n = MAX;
    int arr[MAX];
    int count[MODULO];

    srand(time(NULL));

    for (int i = 0; i < MODULO; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % MODULO;
        count[arr[i]]++;
    }

    // print_array("Unsorted", arr, n);
    cout << "Sorting" << endl;
    sort(arr, n);
    sort(count, MODULO);
    cout << endl;

    // print_array("Sorted", arr, n);
    print_array("Counts", count, MODULO);

    return 0;
}
