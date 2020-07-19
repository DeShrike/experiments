#include <time.h>
#include <stdio.h>

FILE *filePointer;

int main()
{
   time_t timeStamp;
   time(&timeStamp);
   printf("It is now %s", ctime(&timeStamp));

   filePointer = fopen("filetest.txt", "a");
   fprintf(filePointer, "\nThis is a test run at: ");
   fprintf(filePointer, ctime(&timeStamp));
   fclose(filePointer);
   return 0;
}
