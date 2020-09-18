#include "factorial.hpp"

Factorial::Factorial()
{
}

unsigned int Factorial::Calculate(unsigned int number)
{
	if (number > 12)
	{
		return 0;
	}

	if (number <= 2)
	{
		return number;
	}

	return number * Calculate(number - 1);
}

unsigned long long Factorial::CalculateLongLong(unsigned long long number)
{
	if (number > 20)
	{
		return 0;
	}

	if (number <= 2)
	{
		return number;
	}

	return number * CalculateLongLong(number - 1);
}
