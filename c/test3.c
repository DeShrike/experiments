#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

#define COUNT 25000000

char BRIGHTRED[] = "\033[31;1m";
char BRIGHTGREEN[] = "\033[32;1m";
char BRIGHTYELLOW[] = "\033[33;1m";
char BRIGHTBLUE[] = "\033[34;1m";
char BRIGHTMAGENTA[] = "\033[35;1m";
char BRIGHTCYAN[] = "\033[36;1m";
char BRIGHTWHITE[] = "\033[37;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";

int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
}
 
void Qsort(unsigned int* data, int array_size)
{
	qsort(data, array_size, sizeof(unsigned int), intcmp);
}

void BubbleSort(unsigned int* a, int array_size)
{
    int i, j, temp;
    int swapped;
    for (i = 0; i < (array_size - 1); ++i)
    {
    	swapped = 0;
        for (j = 0; j < array_size - 1 - i; ++j)
        {
            if (a[j] > a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
        {
        	return;
        }
    }
}


// Radix sort based on Geeks for Geeks:
// https://www.geeksforgeeks.org/radix-s...
static void RadixSort256(unsigned int* arr, int n)
{
	if (n <= 1)
	{
		return; // Added base case
	}

	unsigned int* output = malloc(n * sizeof(unsigned int)); // output array
	int* count = malloc(256 * sizeof(int));
	unsigned int* originalArr = arr; // So we know which was input

	for (int shift = 0, s = 0; shift < 4; shift++, s += 8)
	{
		// Zero the counts
		for (int i = 0; i < 256; i++)
		{
			count[i] = 0;
		}

		// Store count of occurrences in count[] 
		for (int i = 0; i < n; i++)
		{
			count[(arr[i] >> s) & 0xff]++;
		}

		// Change count[i] so that count[i] now contains 
		// actual position of this digit in output[] 
		for (int i = 1; i < 256; i++)
		{
			count[i] += count[i - 1];
		}

		// Build the output array 
		for (int i = n - 1; i >= 0; i--)
		{
			// precalculate the offset as it's a few instructions
			int idx = (arr[i] >> s) & 0xff;

			// Subtract from the count and store the value
			output[--count[idx]] = arr[i];
		}

		// Copy the output array to input[], so that input[] 
		// is sorted according to current digit

		// We can just swap the pointers
		unsigned int* tmp = arr;
		arr = output;
		output = tmp;
 	}

 	// If we switched pointers an odd number of times,
 	// make sure we copy before returning
 	if (originalArr == output)
	{
		unsigned int* tmp = arr;
		arr = output;
		output = tmp;
	 
		for (int i = 0; i < n; i++)
		{
			arr[i] = output[i];
		}
	}

	free(output);
	free(count);
}

int CheckData(unsigned int* data, int array_size)
{
	int i;
	for (i = 1; i < array_size; i++)
	{
		if (data[i - 1] > data[i])
		{
			return 0;
		}
	}

	return 1;
}

unsigned int state = 123;
unsigned int xorshift32()
{
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
	return state;
}

void GenerateRandomData(unsigned int* arr, int count, int seed, int max)
{
	state = seed;
	for (int i = 0; i < count; i++)
	{
		arr[i] = xorshift32() % max;
	}
}

/*void GenerateRandomData(unsigned int* arr, int count, int seed)
{
	state = seed;
	for (int i; i< count; i++)
	{
		arr[i] = xorshift32();
	}
}*/

unsigned int* CreateData()
{
	int i;
	long long sum = 0;

	unsigned int* data = malloc(COUNT * sizeof(unsigned int));

	GenerateRandomData(data, COUNT, 12 * state, 9999);
	for (i = 0; i < COUNT; i++)
	{
		sum = sum + (long long)data[i];
	}

	float ave = (float)((double)sum / (double)COUNT);

	printf("Data Size: %s%'d%s \n", BRIGHTBLUE, COUNT, RESET);
	printf("Total: %s%'lld%s \n", BRIGHTCYAN, sum, RESET);
	printf("Average: %s%'f%s \n", BRIGHTMAGENTA, ave, RESET);
	printf("\n");

	return data;
}

void Dummy()
{
	int *p;
	int i = 12345;

	p = &i;

	/* address stored in pointer variable */
	printf("Address stored in p variable: %x\n", p );

	/* access the value using the pointer */
	printf("Value of *p variable: %d\n", *p );
}

void Sort1()
{
	unsigned int* data = CreateData();
	printf("Sorting - %sBubbleSort%s\n", BRIGHTYELLOW, RESET);

   	start = clock();
	BubbleSort(data, COUNT);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTYELLOW, cpu_time_used, RESET);
	
	if (CheckData(data, COUNT) == 0)
	{
		printf("%sFAILED%s \n", BRIGHTRED, RESET);
	}
	else
	{
		printf("%sSUCCESS%s \n", BRIGHTGREEN, RESET);
	}

    printf("\n");
    free(data);
}

void Sort2()
{
	unsigned int* data = CreateData();
	printf("Sorting - %sQsort%s\n", BRIGHTYELLOW, RESET);
	
   	start = clock();
	Qsort(data, COUNT);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTYELLOW, cpu_time_used, RESET);
	
	if (CheckData(data, COUNT) == 0)
	{
		printf("%sFAILED%s \n", BRIGHTRED, RESET);
	}
	else
	{
		printf("%sSUCCESS%s \n", BRIGHTGREEN, RESET);
	}

    printf("\n");
    free(data);
}

void Sort3()
{
	unsigned int* data = CreateData();
	printf("Sorting - %sRadixSort%s\n", BRIGHTYELLOW, RESET);

   	start = clock();
	RadixSort256(data, COUNT);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTYELLOW, cpu_time_used, RESET);
	
	if (CheckData(data, COUNT) == 0)
	{
		printf("%sFAILED%s \n", BRIGHTRED, RESET);
	}
	else
	{
		printf("%sSUCCESS%s \n", BRIGHTGREEN, RESET);
	}

    printf("\n");
    free(data);
}

int main()
{
	time_t t;
	srand((unsigned) time(&t));
	setlocale(LC_ALL, "");

	printf("%sSORTING%s\n\n", BRIGHTWHITE, RESET);

	// Sort1();
	Sort2();
	Sort3();
}
