#include <iostream>
#include <string>
#include <set>
#include "tut5.hpp"
using namespace std;

int main()
{
    set<char> s1 = {'H', 'E', 'L', 'L', 'O'};

    s1.insert('B');
    s1.erase('E');

    if (s1.find('B') == s1.end())
    {
        cout << "B not found" << endl;
    }
    else
    {
        cout << "B found" << endl;
    }

    for (auto itr = s1.begin(); itr != s1.end(); ++itr)
    {
        cout << *itr << endl;
    }

    string zin = "Dit is een lange zin met verschillende woorden en letters.";
    set<char> exists;
    for (int i = 0; i < zin.length(); i++)
    {
        char letter = zin[i];
        exists.insert(letter);
    }

    cout << zin << endl;

    for (auto itr = exists.begin(); itr != exists.end(); ++itr)
    {
        cout << *itr << " ";
    }

    cout << endl;

    return 0;
}
