#include <stdio.h>

int arrij[] = {1, 2, 5, 7, 10, 20, 15, 70, 50, 100};

extern int add(int a, int b);
extern int sum_arr(int *a, int b);

int main()
{
	int a = 0xcafe;
	printf("Number: %d\n", a);
	int b = 0xbabe;
	printf("Number: %d\n", b);
	int c = add(a, b);
	printf("   Sum: %d\n", c);

	printf("\n");
	int d = sum_arr(arrij, 10);

	printf("Array Address: 0x%X\n", (int)arrij);
	printf("Array Sum: %d\n", d);

	return 0xabba;
}
