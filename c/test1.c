#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

#define COUNT 10000

char BRIGHTRED[] = "\033[31;1m";
char BRIGHTGREEN[] = "\033[32;1m";
char BRIGHTYELLOW[] = "\033[33;1m";
char BRIGHTBLUE[] = "\033[34;1m";
char BRIGHTMAGENTA[] = "\033[35;1m";
char BRIGHTCYAN[] = "\033[36;1m";
char BRIGHTWHITE[] = "\033[37;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";

int data1[COUNT];
int data2[COUNT];

int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
}
 
void Qsort(int data[], int array_size)
{
	printf("Sorting - %sQsort%s\n", BRIGHTYELLOW, RESET);
	
	qsort(data, array_size, sizeof(int), intcmp);
}

void BubbleSort(int a[], int array_size)
{
	printf("Sorting - %sBubbleSort%s\n", BRIGHTYELLOW, RESET);

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

int CheckData(int data[], int array_size)
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

void DoIt()
{
   	start = clock();
	BubbleSort(data1, COUNT);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTGREEN, cpu_time_used, RESET);
	
	if (CheckData(data1, COUNT) == 0)
	{
		printf("%sFAILED%s \n", BRIGHTRED, RESET);
	}

    printf("\n");

   	start = clock();
	Qsort(data2, COUNT);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n\n", BRIGHTGREEN, cpu_time_used, RESET);
	
	if (CheckData(data2, COUNT) == 0)
	{
		printf("%sFAILED%s \n", BRIGHTRED, RESET);
	}

    printf("\n");
}

void CreateData()
{
	int i;
	int sum = 0;

	time_t t;
	srand((unsigned) time(&t));

	for (i = 0; i < COUNT; i++)
	{
		data1[i] = rand() % COUNT;
		data2[i] = rand() % COUNT;
		
		sum = sum + data1[i];
	}

	float ave = (float)sum / (float)COUNT;

	printf("Data Size: %s%d%s \n", BRIGHTBLUE, COUNT, RESET);
	printf("Total: %s%d%s \n", BRIGHTCYAN, sum, RESET);
	printf("Average: %s%f%s \n", BRIGHTMAGENTA, ave, RESET);
	printf("\n");
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

int main()
{
	printf("%sSORTING%s\n", BRIGHTWHITE, RESET);
	CreateData();
	DoIt();
}
