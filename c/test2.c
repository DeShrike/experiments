#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i;
    int dice[6];

    for (i = 0; i < 6; i++)
    {
       dice[i] = 0;
    }

    srand(time(NULL));

    const int TOTAL = 10000000;

    for (i = 0; i < TOTAL; i++)
    {
      dice[(rand() % 6)] += 1;
    }

    double pers = 0.0, tpers = 0.0;
    for (i = 0; i < 6; i++)
    {
       pers = (dice[i] * 100.0) / TOTAL;
       printf("\t%1d  %5.2f%%\n", dice[i], pers);
       tpers += pers;
    }

    printf("\ttotal:  %6.2f%%\n", tpers);
}
