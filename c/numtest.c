#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



int main(int argc, char *argv[])
{
   printf("\n");

   printf("SHRT_MAX   : %hd  \n", (short) SHRT_MAX);
   printf("USHRT_MAX  : %hu  \n", (unsigned short) USHRT_MAX);

   printf("INT_MAX    : %d  \n", (int) INT_MAX);
   printf("UINT_MAX   : %u  \n", (unsigned int) UINT_MAX);

   printf("LONG_MAX   : %ld  \n", (long) LONG_MAX);
   printf("ULONG_MAX  : %lu  \n", (unsigned long) ULONG_MAX);

   printf("LLONG_MAX  : %lld  \n", (long long) LLONG_MAX);
   printf("ULLONG_MAX : %llu  \n", (unsigned long long) ULLONG_MAX);

   printf("\n");

   printf("short size              : %d \n", sizeof(short));
   printf("unsigned short size     : %d \n", sizeof(unsigned short));
   printf("int size                : %d \n", sizeof(int));
   printf("unsigned int size       : %d \n", sizeof(unsigned int));
   printf("long size               : %d \n", sizeof(long));
   printf("unsigned long size      : %d \n", sizeof(unsigned long));
   printf("long long size          : %d \n", sizeof(long long));
   printf("unsigned long long size : %d \n", sizeof(unsigned long long));

   printf("\n");
}
