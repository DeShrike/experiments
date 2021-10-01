#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include "tut1.hpp"
using namespace std;

int main()
{
    const int gravity = -9.8;

    int arr[] {1, 2, 3, 4};

    cout << "Hello World !!!" << endl;
    std::cout << "Hello World !!!" << endl;

    int arr_size = sizeof(arr) / sizeof(int);
    for (int i = 0; i < arr_size; i++)
    {
        cout << arr[i] << endl;
    }

    bool flag = true;
    int a = 234;
    int &b = a;

    cout << a << " " << &a << endl;
    cout << b << " " << &b << endl;
    b = 123;
    cout << a << " " << &a << endl;
    cout << b << " " << &b << endl;

    int x = 2;
    int* y = &x;
    int* z = NULL;

    int* h = arr;

    return 0;
}
