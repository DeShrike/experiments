#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen()
#include <limits.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <unistd.h> // for sleep())
#include <signal.h> // for signal()

char BRIGHTRED[] = "\033[31;1m";

char RESET[] = "\033[0m";
char INVERSE[] = "\033[5m";
char HIDECURSOR[] ="\033[?25l";
char SHOWCURSOR[] = "\033[?25h";
char CLEARSCREEN[] = "\033[2J";

#define PIXELWIDTH       2
#define PIXELHEIGHT      1
#define WIDTH            38
#define HEIGHT           20
#define COLORCOUNT       (sizeof(Colors) / sizeof(int))
#define OFFSETX          ((80 - (WIDTH * PIXELWIDTH)) / 2)
#define OFFSETY          2

#define msleep(X) usleep(X * 1000)

static volatile int keepRunning = 1;

char Grid[HEIGHT][WIDTH];
int GridCursorX = 0;
int GridCursorY = 0;
int CurrentColor = -1;

int Colors[] = { 5, 41, 42, 43, 44, 45, 46, 47 };

void MoveCursor(int y, int x)
{
    printf("\033[%d;%dH", y, x);
}

void SetColor(int color)
{
    if (color < 0 || color >= COLORCOUNT)
    {
        return;
    }

    int colorValue = Colors[color];

    if (colorValue == CurrentColor)
    {
        return;
    }

    printf("\033[%dm", colorValue);
    CurrentColor = colorValue;
}

void ResetColor()
{
    printf("\033[0m");
    CurrentColor = 0;
}

void MoveGridCursor(int x, int y)
{
    GridCursorX = x;
    GridCursorY = y;
}

void ClearGrid()
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            Grid[y][x] = 0;
        }
    }

    MoveGridCursor(0, 0);
}

void DrawPixel(int x, int y)
{
    int value = Grid[y][x];
    SetColor(value);
    for (int x = 0; x < PIXELWIDTH; x++)
    {
        putchar(' ');
    }

    ResetColor();
}

void DrawGrid()
{
    MoveCursor(1, 1);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int line = 0; line < PIXELHEIGHT; line++)
        {
            MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX);
            for (int x = 0; x < WIDTH; x++)
            {
                DrawPixel(x, y);
            }
        }

        ResetColor();
    }

    fflush(stdout);
}

float current = 0.0f;

int map(float x, float in_min, float in_max, int out_min, int out_max)
{
    float v = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return (int)v;
}

void DoPlasma()
{
    current += 0.01f;
    ClearGrid();

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            float v1 = sin(x * 10.0f + current);
            float v2 = sin(10.0f * (x * sin(current / 2.0f)
                      + y * cos(current / 3.0f)) + current);

            float cx = x + 0.5f * sin(current / 5.0f);
            float cy = y + 0.5f * cos(current / 3.0f);
            float v3 = sin(sqrt(100.0f * (cx * cx) + (cy * cy) + 1.0) + current);

            float v = (v1 + v2 + v3) / 3.0f;

            Grid[y][x] = map(v, -1.0f, 1.0f, 0, COLORCOUNT);
        }
    }

    DrawGrid();
}

void intHandler(int dummy)
{
    keepRunning = 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, intHandler);

    printf("\033[?1049h\033[H");

    printf(CLEARSCREEN);
    printf(HIDECURSOR);

    while (keepRunning)
    {
        DoPlasma();
        // sleep(1);
        msleep(50);
    }

    sleep(1);

    printf(SHOWCURSOR);
    printf("\033[?1049l");
}
