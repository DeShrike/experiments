#include <iostream>
#include <string>
#include <iomanip>
#include "permutations.hpp"
#include "factorial.hpp"

using namespace std;

Permutations::Permutations(int size, PermutationsCallback callback)
{
	this->array = new int[size];
	this->size = size;
	this->callback = callback;

	for (int i = 0; i < this->size; i++)
	{
		this->array[i] = i;
	}
}

Permutations::~Permutations()
{
	delete[] this->array;
}	

int Permutations::Length()
{
	Factorial f;
	return f.Calculate(this->size);
}

void Permutations::Swap(int ix1, int ix2)
{
	int temp = this->array[ix1];
	this->array[ix1] = this->array[ix2];
	this->array[ix2] = temp;
}

void Permutations::Print()
{
	for (int i = 0; i < size; i++)
	{
		cout << this->array[i] << " ";
	}

	cout << endl;
}

bool Permutations::Generate(int n)
{
	bool cont;
	if (n == 1)
	{
		bool cont = callback(this->index, this->array, this->size);
		this->index++;
		return cont;
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			cont = Generate(n - 1);
			if (cont == false)
			{
				return false;
			}

			if (n % 2 == 0)
			{
				Swap(i, n - 1);
			}
			else
			{
				Swap(0, n - 1);
			}
		}

		cont = Generate(n - 1);
		if (cont == false)
		{
			return false;
		}
	}

	return true;
}

void Permutations::Iterate()
{
	this->index = 0;
	Generate(this->size);
}
