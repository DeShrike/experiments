#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int* MakeArray(int size)
{
	int* result = new int[size];
	for (int i = 0; i < size; i++)
	{
		result[i] = i;
	}

	return result;
}

int main()
{
	int* p = new int(1);
	cout << *p << " ";
	delete p;

	p = new int(2);
	cout << *p << " ";
	delete p;

	int* p1 = new int[50];
	int* p2 = new int[50]();   // Default value 0

	cout << p1[0] << " " << p2[0] << endl;
	cout << endl;

	delete[] p1;
	delete[] p2;

	const int s = 100;
	int* xyz = MakeArray(s);
	delete[] xyz;

	int gridwidth = 19;
	int gridHeight = 19;
	
	// Create
	int** grid = new int*[gridHeight];
	for (int y = 0; y < gridHeight; y++)
	{
		grid[y] = new int[gridwidth];
	}

	// Use
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridwidth; x++)
		{
			grid[y][x] = (x + 1) * (y + 1);
		}
	}

	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridwidth; x++)
		{
			cout << setw(3) << grid[y][x] << " ";
		}

		cout << endl;
	}

	// Delete
	for (int y = 0; y < gridHeight; y++)
	{
		delete[] grid[y];
	}

	delete[] grid;

	double x = 1234.567;
	double y = 3.141592654;
	int z = 42;
	cout << fixed << showpoint << setprecision(2);
	cout << endl;
	cout << "x = " << x << " ";
	cout << setprecision(5); 
	cout << "y = " << y << " ";
	cout << "z = " << z << endl;

	return 0;
}
