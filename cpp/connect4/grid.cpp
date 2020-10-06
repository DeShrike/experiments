#include <iostream>
#include "grid.hpp"

using namespace std;

Grid::Grid()
{
    cout << STORESCREEN;
    cout << CLEARSCREEN;
    cout << HIDECURSOR;
    Clear();
}

Grid::~Grid()
{
    cout << SHOWCURSOR;
    cout << RESTORESCREEN;
}

void Grid::Draw()
{
    bool shouldSetCursor = false;
    MoveCursor(1, 1);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int line = 0; line < PIXELHEIGHT; line++)
        {
            MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX);
            for (int x = 0; x < WIDTH; x++)
            {
                char prev = PreviousData[y][x];
                if (prev != Data[y][x])
                {
                    if (shouldSetCursor)
                    {
                        MoveCursor(y * PIXELHEIGHT + line + 1 + OFFSETY, 1 + OFFSETX + (x * PIXELWIDTH));
                        shouldSetCursor = false;
                    }

                    DrawPixel(x, y);
                }
                else
                {
                    shouldSetCursor = true;
                }
            }
        }

        ResetColor();
    }

    fflush(stdout);
	CopyGridToPrevious();
}

void Grid::MoveCursor(int y, int x)
{
    // printf("\033[%d;%dH", y, x);
    cout << "\033[" << y << ";" << x << "H";
}

void Grid::SetColor(int color)
{
    if (color < 0 || color >= COLORCOUNT)
    {
        return;
    }

    int colorValue = this->Colors[color];

    if (colorValue == this->CurrentColor)
    {
        return;
    }

    // printf("\033[%dm", colorValue);
    cout << "\033[" << colorValue << "m";
    this->CurrentColor = colorValue;
}

void Grid::ResetColor()
{
    // printf("\033[0m");
    cout << "\033[0m";
    CurrentColor = 0;
}

void Grid::Clear()
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            Data[y][x] = 0;
        }
    }
}

void Grid::DrawPixel(int x, int y)
{
    int value = this->Data[y][x];

    SetColor(value);
    for (int x = 0; x < PIXELWIDTH; x++)
    {
    	cout << ' ';
        // putchar(' ');
    }

    // ResetColor();
}

void Grid::PlotPoint(int x, int y, int c)
{
    Data[y][x] = c;
}

void Grid::CopyGridToPrevious()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            PreviousData[y][x] = Data[y][x];
        }
    }
}
