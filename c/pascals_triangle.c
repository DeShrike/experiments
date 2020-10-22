#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

typedef unsigned long long ull;

#define MAXLINE 128

ull* pascal1;
ull* pascal2;

void Swap()
{
   ull* temp = pascal1;
   pascal1 = pascal2;
   pascal2 = temp;
}

void Show(int line)
{
   for (int i = 0; i < line; i++)
   {
      printf("%'llu ", pascal1[i]);
   }

   printf("\n");
}


void Calculate(int line)
{
   for (int i = 0; i < line; i++)
   {
      pascal1[i + 1] = pascal2[i] + pascal2[i + 1];
      if (pascal1[i + 1] < pascal2[i])
      {
          printf("\n Overflow %d \n", line);
          return;
      }
   }
}

int main(int argc, char *argv[])
{
   ull maxValue = ULLONG_MAX;
   printf("Max: %'27llu \n", maxValue);

   pascal1 = (ull*)malloc(MAXLINE * sizeof(ull));
   pascal2 = (ull*)malloc(MAXLINE * sizeof(ull));

   pascal1[0] = 1;
   pascal2[0] = 1;

   for (int i = 1; i <= MAXLINE; i++)
   {
      pascal1[i - 1] = 1;
      if (i > 2)
      {
          Calculate(i);
      }

      Show(i);

      Swap();
   }

   free(pascal1);
   free(pascal2);
   printf("\n");
}
