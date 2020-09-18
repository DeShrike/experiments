#ifndef PERMUTATIONS_HPP
#define PERMUTATIONS_HPP

typedef bool (*PermutationsCallback)(int, int*, int);

class Permutations
{
private:
	int size;
	int index;
	int *array;
	PermutationsCallback callback;
	void Swap(int, int);
	bool Generate(int);

public:
	Permutations(int, PermutationsCallback);
	~Permutations();
	int Length();
	void Print();
	void Iterate();
};

#endif // PERMUTATIONS_HPP
