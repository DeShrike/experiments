#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include "permutations.hpp"

using namespace std;
using namespace std::chrono;

bool ProcessOnePermutation(int index, int *data, int size)
{
	/*if (index % 100000 == 0)
	{
		cout << setw(3) << index << ": ";
		for (int i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}

		cout << endl;
	}*/

	return true;
}

void CardOrder(int size)
{
	Permutations permutations(size, ProcessOnePermutation);
	permutations.Iterate();

	cout << "Permutation count: " << permutations.Length() << endl;
}

int main()
{
	const int s = 11;

	cout << "CardOrder with " << s << " cards" << endl;

	// Get starting timepoint
    auto start = high_resolution_clock::now();

	CardOrder(s);

	// Get ending timepoint
    auto stop = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(stop - start);
	auto milliseconds = duration.count();
	auto seconds = duration.count() / 1000.0;

	cout << "Time taken: " << milliseconds << " milliseconds - " << seconds << " seconds" << endl; 

	return 0;
}
