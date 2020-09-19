#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include "permutations.hpp"

using namespace std;
using namespace std::chrono;

int correct = 0;

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
	
	int c = 1;
	int last = data[0];
	int start = 1; 
	if (last == size - 1)
	{
		last = data[1];
		start = 2;
	}
	
	for (int i = start; i < size; i++)
	{
		if (data[i] > last)
		{
			c++;
			last = data[i];
		}
	}
	
	if (c == size - 1)
	{
		correct++;
		cout << setw(3) << index << ": ";
		for (int i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}

		cout << " -> " << c << endl;
	}

	return true;
}

void CardOrder(int size)
{
	Permutations permutations(size, ProcessOnePermutation);
	permutations.Iterate();

	int l = permutations.Length();
	cout << "Permutation count: " << l << endl;
	cout << "Correct: " << correct << " (" << (correct / (float)l * 100.0) << " %)"<< endl;
}

int main()
{
	const int s = 4;

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
