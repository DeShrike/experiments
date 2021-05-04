#include <stdio.h>

int myfunc();

char arrij[] = {1, 2, 5, 7};

extern int add(int a, int b);
extern int get_arr(char *a, int b);

int main()
{
	int a = 0xcafe;
	printf("Number: %d\n", a);
	int b = myfunc();
	printf("Number: %d\n", b);
	int c = add(a, b);
	printf("   Sum: %d\n", c);

	int d = get_arr(arrij, 4);
	printf("Array Sum: %d\n", d);

	return 0xabba;
}

int myfunc()
{
	int a = 0xbabe;
	printf("Number: %d\n", a);
	return a;
}

