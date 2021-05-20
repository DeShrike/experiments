#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
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
char STORESCREEN[] = "\033[?1049h\033[H";
char RESTORESCREEN[] = "\033[?1049l";

#define WIDTH            39
#define HEIGHT           20

#define PIXELWIDTH       2
#define PIXELHEIGHT      1
#define COLORCOUNT       (sizeof(Colors) / sizeof(int))
#define OFFSETX          ((80 - (WIDTH * PIXELWIDTH)) / 2)
#define OFFSETY          0

static volatile int keepRunning = 1;

// int WIDTH;
// int HEIGHT;

char Grid[HEIGHT][WIDTH];
int CurrentColor = -1;
char PreviousGrid[HEIGHT][WIDTH];

int Colors[] = { 0 /*5*/, 41, 42, 43, 44, 45, 46, 47 };

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

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while( (now-then) < pause )
    {
        now = clock();
    }
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
}

void DrawPixel(int x, int y)
{
    int value = Grid[y][x];

    SetColor(value);
    for (int x = 0; x < PIXELWIDTH; x++)
    {
        putchar(' ');
    }

    // ResetColor();
}

void CopyGridToPrevious()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            PreviousGrid[y][x] = Grid[y][x];
        }
    }
}

void DrawGrid()
{
	int shouldSetCursor = 0;
    MoveCursor(1, 1);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int line = 0; line < PIXELHEIGHT; line++)
        {
            MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX);
            for (int x = 0; x < WIDTH; x++)
            {
            	char prev = PreviousGrid[y][x];
            	if (prev != Grid[y][x])
            	{
            		if (shouldSetCursor == 1)
            		{
			            MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX + (x * PIXELWIDTH));
            			shouldSetCursor = 0;
            		}

                	DrawPixel(x, y);
            	}
            	else
            	{
					shouldSetCursor = 1;
            	}
            }
        }

        ResetColor();
    }

    fflush(stdout);
	CopyGridToPrevious();
}

typedef struct
{
	int x;
	int y;
	int dx;
	int dy;
} Point;

typedef struct
{
	int c;
	Point a;
	Point b;
} Line;

#define LINECOUNT 7

Line lines[LINECOUNT];

void PlotPoint(int x, int y, int c)
{
	Grid[y][x] = c;
}

void PlotLineLow(int x0, int y0, int x1, int y1, int colorIx)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {
		PlotPoint(x, y, colorIx);
		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
		{
			D = D + 2 * dy;
		}
	}
}

void PlotLineHigh(int x0, int y0, int x1, int y1, int colorIx)
{
	int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y < y1; y++)
    {
		PlotPoint(x, y, colorIx);
		if (D > 0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else
		{
			D = D + 2 * dx;
		}
    }
}

void PlotLine(int x0, int y0, int x1, int y1, int colorIx)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
        if (x0 > x1)
        {
            PlotLineLow(x1, y1, x0, y0, colorIx);
        }
        else
        {
            PlotLineLow(x0, y0, x1, y1, colorIx);
        }
    }
    else
    {
        if (y0 > y1)
        {
            PlotLineHigh(x1, y1, x0, y0, colorIx);
        }
        else
        {
            PlotLineHigh(x0, y0, x1, y1, colorIx);
        }
    }
}

void Init()
{
	for (int i = 0; i < LINECOUNT; i++)
	{
		// lines[i].c = rand() % (COLORCOUNT - 1) + 1;
		lines[i].c = i % (COLORCOUNT - 1) + 1;

		lines[i].a.x = rand() % WIDTH;
		lines[i].a.y = rand() % HEIGHT;
		lines[i].a.dx = (rand() % 10 < 5) ? 1 : -1;
		lines[i].a.dy = (rand() % 10 < 5) ? 1 : -1;

		lines[i].b.x = rand() % WIDTH;
		lines[i].b.y = rand() % HEIGHT;
		lines[i].b.dx = -lines[i].a.dx;
		lines[i].b.dy = -lines[i].a.dy;
	}
}

void MovePoint(Point *p)
{
	int changed = 0;

	p->x += p->dx;
	p->y += p->dy;

	if (p->x < 0 || p->x >= WIDTH)
	{
		p->dx *= -1;
		changed = 1;
	}

	if (p->y < 0 || p->y >= HEIGHT)
	{
		p->dy *= -1;
		changed = 1;
	}

	if (changed == 1)
	{
		MovePoint(p);
	}
}

void Draw()
{
    ClearGrid();

	for (int i = 0; i < LINECOUNT; i++)
	{
		PlotLine(
					lines[i].a.x, lines[i].a.y,
					lines[i].b.x, lines[i].b.y,
					lines[i].c
				);
        //Grid[lines[i].a.y][lines[i].a.x] = lines[i].c;
        //Grid[lines[i].b.y][lines[i].b.x] = lines[i].c;
	}

	for (int i = 0; i < LINECOUNT; i++)
	{
		MovePoint(&lines[i].a);
		MovePoint(&lines[i].b);
	}

    DrawGrid();
}

void intHandler(int dummy)
{
    keepRunning = 0;
}

int main(int argc, char *argv[])
{
    time_t t;
    srand((unsigned) time(&t));

    /*
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    WIDTH = w.ws_col / 2;
    HEIGHT = w.ws_row;
    */

    signal(SIGINT, intHandler);

    printf(STORESCREEN);
    printf(CLEARSCREEN);
    printf(HIDECURSOR);

    Init();

    while (keepRunning)
    {
    	Draw();
        usleep(100000);
    }

    sleep(1);
    printf(SHOWCURSOR);
    printf(RESTORESCREEN);
}
