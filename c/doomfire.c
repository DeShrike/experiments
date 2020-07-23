#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <float.h>

char BRIGHTRED[] = "\033[31;1m";
char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";
char HIDECURSOR[] ="\033[?25l";
char SHOWCURSOR[] = "\033[?25h";
char CLEARSCREEN[] = "\033[2J";

#define FIRE_WIDTH 79
#define FIRE_HEIGHT 26
#define NUM_COLORS 9

char COLORS[] = " .,oO0%@#";

int firePixels[FIRE_HEIGHT][FIRE_WIDTH];

void MoveCursor(int y, int x)
{
	printf("\033[%d;%dH", y, x);
}

void InitFire()
{
    srand(time(0)); 
   	for (int x = 0; x < FIRE_WIDTH; x++)
	{
		for (int y = 0; y < FIRE_HEIGHT; y++)
		{
			firePixels[y][x] = y == 0 ? 255 : 0;
			if (x % 10 == 0)
			{
				firePixels[y][x] = y == 0 ? 100 : 0;
			}
		}
	}
}

void SpreadFire(int x, int y)
{
	int speed = 30;
	int rand = (int)round(random() * 2.0) & 2;
	int rand2 = (int)round(random() * speed) & speed;
    int xx = x + rand - 1;
    
    if (xx < 0)
    {
    	xx = 0;
    }
    
    if (xx >= FIRE_WIDTH)
    {
    	xx = FIRE_WIDTH - 1;
    }

    /*if (y == 0)
    {
    	printf("firePixels[%d][%d] = firePixels[%d][%d] - %d \n", y + 1, xx, y, x, rand2);
    }*/

    firePixels[y + 1][xx] = firePixels[y][x] - rand2;
}

void DoFire()
{
    for (int y = 0; y < FIRE_HEIGHT - 1; y++) 
	{
		for (int x = 0; x < FIRE_WIDTH; x++) 
        {
            SpreadFire(x, y);
        }
    }
}

int FireToChar(int fire)
{
	int step = (int)(256 / NUM_COLORS);
	for (int i = 0; i < NUM_COLORS; i++)
	{
		if (fire < (i + 1) * step)
		{
			return COLORS[i];
		}
	}
	
	return COLORS[NUM_COLORS - 1];
}

void DrawFire()
{
	for (int y = 4; y < FIRE_HEIGHT; y++)
	{
		int line = FIRE_HEIGHT - y;
		MoveCursor(line, 1);
		for (int x = 0; x < FIRE_WIDTH; x++)
		{
			putchar( FireToChar(firePixels[y][x]) );
		}
	}
}

int main(int argc, char *argv[])
{
	InitFire();
	printf(CLEARSCREEN);
	printf(HIDECURSOR);
	for (int i = 0; i < 10000; i++)
	{
		// if (i % 30 == 0)
		{
			DoFire();
		}

		DrawFire();
	}

	MoveCursor(23, 1);
	printf(SHOWCURSOR);
}
