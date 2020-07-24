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

#define WIDTH            24
#define HEIGHT           12
#define LINES_PER_CHAR   5
#define COLUMNS_PER_CHAR 4
#define CHARS            12
#define LETTERSPACING    1
#define LINEHEIGHT       6
#define PIXELWIDTH       2
#define PIXELHEIGHT      1
#define COLORCOUNT       (sizeof(Colors) / sizeof(int))
#define OFFSETX          ((80 - (WIDTH * PIXELWIDTH)) / 2)
#define OFFSETY          4

static volatile int keepRunning = 1;

char Grid[HEIGHT][WIDTH];
int GridCursorX = 0;
int GridCursorY = 0;
int CurrentColor = -1;

int Colors[] = { 0 /*5*/, 41, 42, 43, 44, 45, 46, 47 };

int CharsWidths[CHARS] = {  4,   2,   4,   4,   4,   4,   4,   3,   4,   4,   1,   2  };
char Chars[CHARS] =      { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ' ' };
int CharData[CHARS][LINES_PER_CHAR][COLUMNS_PER_CHAR] = 
{
    { 
        // 0 - Width 4
        { 0, 1, 1, 0 }, 
        { 1, 0, 0, 1 }, 
        { 1, 0, 0, 1 }, 
        { 1, 0, 0, 1 }, 
        { 0, 1, 1, 0 }
    },
    { 
        // 1 - Width 3
        { 0, 1, 0, 0 }, 
        { 1, 1, 0, 0 }, 
        { 0, 1, 0, 0 }, 
        { 0, 1, 0, 0 }, 
        { 0, 1, 0, 0 }
    },
    { 
        // 2
        { 1, 1, 1, 0 }, 
        { 0, 0, 0, 1 }, 
        { 0, 1, 1, 0 }, 
        { 1, 0, 0, 0 }, 
        { 1, 1, 1, 1 }
    },
    { 
        // 3
        { 1, 1, 1, 0 }, 
        { 0, 0, 0, 1 }, 
        { 0, 1, 1, 0 }, 
        { 0, 0, 0, 1 }, 
        { 1, 1, 1, 0 }
    },
    {
        // 4
        { 1, 0, 0, 1 },
        { 1, 0, 0, 1 },
        { 1, 1, 1, 1 },
        { 0, 0, 0, 1 },
        { 0, 0, 0, 1 }
    },
    {
        // 5
        { 1, 1, 1, 1 },
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 1 },
        { 1, 1, 1, 0 }
    },
    {
        // 6
        { 0, 1, 1, 0 },
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 1, 0, 0, 1 },
        { 0, 1, 1, 0 }
    },
    {
        // 7
        { 1, 1, 1, 0 }, 
        { 0, 0, 1, 0 }, 
        { 0, 0, 1, 0 }, 
        { 0, 0, 1, 0 }, 
        { 0, 0, 1, 0 }
    },
    { 
        // 8
        { 0, 1, 1, 0 }, 
        { 1, 0, 0, 1 }, 
        { 0, 1, 1, 0 }, 
        { 1, 0, 0, 1 }, 
        { 0, 1, 1, 0 }
    },
    { 
        // 9
        { 0, 1, 1, 0 }, 
        { 1, 0, 0, 1 }, 
        { 0, 1, 1, 1 }, 
        { 0, 0, 0, 1 }, 
        { 0, 1, 1, 0 }
    },
    { 
        // : - Width 1
        { 0, 0, 0, 0 }, 
        { 1, 0, 0, 0 }, 
        { 0, 0, 0, 0 }, 
        { 1, 0, 0, 0 }, 
        { 0, 0, 0, 0 }
    },
    { 
        // Blank
        { 0, 0, 0, 0 }, 
        { 0, 0, 0, 0 }, 
        { 0, 0, 0, 0 }, 
        { 0, 0, 0, 0 }, 
        { 0, 0, 0, 0 }
    }
};

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

    MoveGridCursor(0, 0);
}

int FindIndexOfChar(char c)
{
    for (int ix = 0; ix < CHARS; ix++)
    {
        if (Chars[ix] == c)
        {
            return ix;
        }
    }

    return -1;
}

int MeasureGridChar(char c)
{
    if (c == '\n')
    {
        return 0;
    }

    int ix = FindIndexOfChar(c);
    if (ix < 0)
    {
        return 0;
    }

    return CharsWidths[ix] + LETTERSPACING;
}

void PrintGridChar(char c, int color)
{
    if (c == '\n')
    {
        GridCursorX = 0;
        GridCursorY += LETTERSPACING + LINES_PER_CHAR;
    }

    int ix = FindIndexOfChar(c);
    if (ix < 0)
    {
        return;
    }

    typedef int chardata[LINES_PER_CHAR][COLUMNS_PER_CHAR];

    chardata *theChar = &CharData[ix];
    int charWidth = CharsWidths[ix];

    for (int y = 0; y < LINES_PER_CHAR; y++)
    {
        for (int x = 0; x < charWidth; x++)
        {
            int value = (*theChar)[y][x];
            Grid[GridCursorY + y][GridCursorX + x] = value == 0 ? 0 : color;
        }
    }

    GridCursorX += charWidth + LETTERSPACING;
}

int MeasureGridString(char *s)
{
    int width = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        width += MeasureGridChar(s[i]);
    }

    return width - LETTERSPACING;
}

void PrintGridString(char *s, int color)
{
    int m = MeasureGridString(s);
    int offset = (WIDTH - m) / 2;
    GridCursorX = offset;

    for (int i = 0; i < strlen(s); i++)
    {
        PrintGridChar(s[i], s[i] == ':' ? color + 1 : color);
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

void ShowTime()
{
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /*
    printf("Hour: %d \n", timeinfo->tm_hour);
    printf("Minute: %d \n", timeinfo->tm_min);
    printf("Second: %d \n", timeinfo->tm_sec);
    printf("Month: %d \n", timeinfo->tm_mon);
    printf("Year: %d \n", timeinfo->tm_year);
    printf("Day: %d \n", timeinfo->tm_mday);
    printf("WeekDay: %d \n", timeinfo->tm_wday);
    printf("YearDay: %d \n", timeinfo->tm_yday);
    printf("Current local time and date: %s", asctime(timeinfo));
    */

    char line1[10];
    sprintf(line1, "%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    char line2[10];
    sprintf(line2, "%02d", timeinfo->tm_sec);

    ClearGrid();

    PrintGridString(line1, 1);
    PrintGridChar('\n', 0);
    PrintGridString(line2, 4);

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
        ShowTime();
        sleep(1);        
    }

    sleep(1);
    /*        
    printf(CLEARSCREEN);
    MoveCursor(1, 1);
    */
    printf(SHOWCURSOR);
    printf("\033[?1049l");
}
