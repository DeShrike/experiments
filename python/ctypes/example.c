#include <stdio.h>

int sum(int from,int to)
{
   int result = 0;
   for (int i = from; i <= to; ++i)
   {
      result += i;
   }

   return result;
}

char* test(char *name, int age)
{
   printf("Name: %s, age: %d\n", name, age);
   return "Done";
}

