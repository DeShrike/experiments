#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <locale.h>

#define USHRT_MIN 0
#define UINT_MIN 0
#define ULONG_MIN 0
#define ULLONG_MIN 0

int main(int argc, char *argv[])
{
   setlocale(LC_ALL, "");

   printf("\n");

   printf("SCHAR_MIN/MAX  : %'27d - %'27d \n", (signed char) SCHAR_MIN, (signed char) SCHAR_MAX);
   printf("CHAR_MIN/MAX   : %'27u - %'27u \n", (unsigned char) CHAR_MIN, (unsigned char) CHAR_MAX);

   printf("SHRT_MIN/MAX   : %'27hd - %'27hd \n", (short) SHRT_MIN, (short) SHRT_MAX);
   printf("USHRT_MIN/MAX  : %'27hu - %'27hu \n", (unsigned short) USHRT_MIN, (unsigned short) USHRT_MAX);

   printf("INT_MIN/MAX    : %'27d - %'27d \n", (int) INT_MIN, (int) INT_MAX);
   printf("UINT_MIN/MAX   : %'27u - %'27u \n", (unsigned int) UINT_MIN, (unsigned int) UINT_MAX);

   printf("LONG_MIN/MAX   : %'27ld - %'27ld \n", (long) LONG_MIN, (long) LONG_MAX);
   printf("ULONG_MIN/MAX  : %'27lu - %'27lu \n", (unsigned long) ULONG_MIN, (unsigned long) ULONG_MAX);

   printf("LLONG_MIN/MAX  : %'27lld - %'27lld \n", (long long) LLONG_MIN, (long long) LLONG_MAX);
   printf("ULLONG_MIN/MAX : %'27llu - %'27llu \n", (unsigned long long) ULLONG_MIN, (unsigned long long) ULLONG_MAX);

   printf("FLT_MIN/MAX    : %'27e - %'27e \n", (float) FLT_MIN, (float) FLT_MAX);
   printf("DBL_MIN/MAX    : %'27e - %'27e \n", (double) DBL_MIN, (double) DBL_MAX);

   printf("\n");

   printf("signed char / char             : %d bytes, %d bytes \n", sizeof(signed char), sizeof(char));
   printf("short / unsigned short         : %d bytes, %d bytes \n", sizeof(short), sizeof(unsigned short));
   printf("int / unsigned int             : %d bytes, %d bytes \n", sizeof(int), sizeof(unsigned int));
   printf("long / unsigned long           : %d bytes, %d bytes \n", sizeof(long), sizeof(unsigned long));
   printf("long long / unsigned long long : %d bytes, %d bytes \n", sizeof(long long), sizeof(unsigned long long));
   printf("float                          : %d bytes \n", sizeof(float));
   printf("double                         : %d bytes \n", sizeof(double));

   printf("\n");
}
