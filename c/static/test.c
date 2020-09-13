#include <stdio.h>
#include "basic.h"

int main()
{
	int a = 42;
	int b = 666;
	printf("A: %d\n", a);
	printf("B: %d\n", b);
	printf("A + B = %d\n", add(a, b));
	printf("A * B = %d\n", mult(a, b));
	printf("A! = %llu\n", factorial(a));

	return 0;
}
