#include <iostream>
#include <string>
#include <vector>
#include "tut2.hpp"
using namespace std;

int main()
{
    vector<int> v1 = {1, 34, 56, 78};

    cout << v1.front() << endl;
    cout << v1.back() << endl;
    v1.push_back(23);
    cout << "Size: " << v1.size() << endl;
    cout << "Capacity: " << v1.capacity() << endl;
    cout << v1[0] << endl;
    v1.pop_back();
    cout << "Size: " << v1.size() << endl;
    cout << "Capacity: " << v1.capacity() << endl;
    v1.shrink_to_fit();

    v1.insert(v1.begin(), 78);
    v1.insert(v1.begin(), 90);
    v1.insert(v1.begin(), 80);
    v1.insert(v1.begin() + 2, 70);

    v1.erase(v1.begin());
    v1.erase(v1.begin() + 4);

    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << endl;
    }

    for (auto itr = v1.begin(); itr != v1.end(); itr++)
    {
        cout << *itr << endl;
    }

    return 0;
}
