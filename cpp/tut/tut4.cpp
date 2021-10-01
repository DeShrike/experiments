#include <iostream>
#include <string>
#include <tuple>
#include "tut4.hpp"
using namespace std;

int main()
{
    tuple<int, string, char> something;
    tuple<int, string, char> other;
    tuple<int, string, char> whatever(20, "Bob", 'M');

    cout << get<0>(whatever) << endl;
    cout << get<1>(whatever) << endl;
    cout << get<2>(whatever) << endl;

    get<0>(something) = 202;
    get<1>(something) = "Jane";
    get<2>(something) = 'F';

    other = make_tuple(99, "Bill", 'M');

    cout << get<0>(other) << endl;
    cout << get<1>(other) << endl;
    cout << get<2>(other) << endl;

    get<0>(other) = 202;
    get<1>(other) = "Jane";
    get<2>(other) = 'F';

    other.swap(something);

    int xx;
    string yy;
    char zz;

    tie(xx, yy, zz) = other;

    auto eda = tuple_cat(other, something);

    cout << sizeof(eda) << endl;

    return 0;
}
