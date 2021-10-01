#include <iostream>
#include <string>
#include <map>
#include "tut3.hpp"
using namespace std;

int main()
{
    map<char, int> mp = {
        {'A', 123},
        {'B', 213},
        {'C', 876},
    };

    mp['D'] = 873;
    pair<char, int> p1('E', 766);
    mp.insert(p1);

    cout << mp['D'] << " " << p1.first << " " << p1.second << endl;
    cout << mp.empty() << mp.size() << endl;
    mp.erase('B');
    cout << mp.empty() << mp.size() << endl;

    for (map<char, int>::iterator itr = mp.begin(); itr != mp.end(); ++itr)
    {
        cout << (*itr).first << endl;
        cout << itr->first << "=" << itr->second << endl;
    }

    mp.clear();
    cout << mp.empty() << mp.size() << endl;

    string zin = "Dit is een lange zin waarvan ik de letter-frequetie wil kennen.";
    map<char, int> freq;
    for (int i = 0; i < zin.length(); i++)
    {
        char letter = zin[i];
        if (freq.find(letter) == freq.end())
        {
            freq[letter] = 0;
        }

        freq[letter]++;
    }

    for (map<char, int>::iterator itr = freq.begin(); itr != freq.end(); ++itr)
    {
        cout << itr->first << ": " << itr->second << endl;
    }

    return 0;
}
