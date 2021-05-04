#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

char BRIGHTRED[] = "\033[31;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";

extern unsigned int sum_arr_asm(unsigned int *array, unsigned int count);

unsigned int sum_arr_c(unsigned int* array, unsigned int count)
{
	unsigned int i = 0;
	unsigned int sum = 0;
	for (unsigned int i = 0; i < count; i++)
	{
		sum += array[i];
	}

	return sum;
}

int main()
{
	int array_size = 1000 * 1000 * 20;
	unsigned int* the_array = malloc(array_size * sizeof(unsigned int));

	for (unsigned int i = 0; i < array_size; i++)
	{
		the_array[i] = i % 100;
	}

	printf("Summing in C...\n");
	start = clock();
	unsigned int sum_c = sum_arr_c(the_array, array_size);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

	printf("Summing in ASM...\n");
	start = clock();
	unsigned int sum_asm = sum_arr_asm(the_array, array_size);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

	printf("Array Sum   C: %d\n", sum_c);
	printf("Array Sum ASM: %d\n", sum_asm);

	free(the_array);
	return 0;
}
