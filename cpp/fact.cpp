#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include "factorial.hpp"

using namespace std;


void reverseStr(string& str) 
{ 
    int n = str.length(); 
  
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++)
    { 
        swap(str[i], str[n - i - 1]); 
    }
} 

string FormatWithThousandSeperators(unsigned long long number)
{
	auto src = std::to_string(number);
    auto dest = std::string();

    auto count = 3;

    for(auto i = src.crbegin() ; i != src.crend() ; ++i) 
    {
        if (count == 0)
        {
            dest.push_back(',');
            count = 3;
        }

        if (count--) 
        {
            dest.push_back(*i);
        }
    }

    reverseStr(dest);

    return dest;
}

int main()
{
	bool pastUintMax = false;
	bool pastUshortMax = false;
	Factorial fac;
	for (int i = 1; i < 21; i++)
	{
		unsigned long long result = fac.CalculateLongLong(i);
		if (result > USHRT_MAX && pastUshortMax == false)
		{
			unsigned short us = USHRT_MAX;
			cout << "      " << setw(26)<< FormatWithThousandSeperators(us) << " -> Max unsigned short (16 bit)" << endl;
			pastUshortMax = true;
		}

		if (result > UINT_MAX && pastUintMax == false)
		{
			unsigned int ui = UINT_MAX;
			cout << "      " << setw(26) << FormatWithThousandSeperators(ui) << " -> Max unsigned int (32 bit)" << endl;
			pastUintMax = true;
		}

		cout << setw(2) << i << "! = ";
		cout << setw(26) << FormatWithThousandSeperators(result) << endl;
	}

	unsigned long long t = ULLONG_MAX;
	cout << "      " << setw(26) << FormatWithThousandSeperators(t) << " -> Max unsigned long long (64 bit)" << endl;

	return 0;
}
