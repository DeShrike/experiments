#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <time.h>

clock_t start, end;
double cpu_time_used;

char BRIGHTRED[] = "\033[31;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";

void int_test_real(long long max)
{
   long long result = 0;
   for (long long num = 0; num < max; num++)
   {
      if (num % 3 == 0 || num % 5 == 0)
      {
      	 result += num;
      }
   }

   printf("Sum is %s%lli%s\n", BRIGHTRED, (long long)result, RESET);
}

void float_test_real(long max)
{
   double angle = 0.0;
   double delta = 0.1;
   double result = 0.0;
   for (long num = 0; num < max; num++)
   {
      result = result + sin(angle) + cos(angle);
      angle = angle + delta;
   }

   printf("Sum is %s%.4f%s\n", BRIGHTRED, (double)result, RESET);
}

void int_test()
{
  int_test_real(10000000UL);
}

void float_test()
{
  float_test_real(10000000L);
}

int main(int argc, char *argv[])
{
  printf("%s *** C *** %s\n", INVERSE, RESET);

  printf("Starting int_test\n");
  start = clock();
  int_test();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

  printf("\n");

  printf("Starting float_test\n");
  start = clock();
  float_test();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Ellapsed: %s%f%s seconds\n", BRIGHTRED, cpu_time_used, RESET);

  /*
  printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
  printf("int size : %d \n", sizeof(int));
  printf("long size : %d \n", sizeof(long));
  printf("unsigned long size : %d \n", sizeof(unsigned));
  printf("long long size : %d \n", sizeof(long long));
  */
}
