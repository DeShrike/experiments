#ifndef GRID_HPP
#define GRID_HPP

#include <string>

#define WIDTH            38
#define HEIGHT           22
#define PIXELWIDTH       1
#define PIXELHEIGHT      1
#define OFFSETX          ((80 - (WIDTH * PIXELWIDTH)) / 2)
#define OFFSETY          1
#define COLORCOUNT       8

using namespace std;

class Grid
{
private:
	string RESET = "\033[0m";
	string INVERSE = "\033[5m";
	string HIDECURSOR = "\033[?25l";
	string SHOWCURSOR = "\033[?25h";
	string CLEARSCREEN = "\033[2J";
	string STORESCREEN = "\033[?1049h\033[H";
	string RESTORESCREEN = "\033[?1049l";

	string BRIGHTRED = "\033[31;1m";

	int Colors[COLORCOUNT] = { 
		0 /*5*/,    // Black
		41, 		// Red
		42, 		// Green
		43, 		// Yellow
		44, 		// Blue
		45, 		// Magenta
		46, 		// Cyan
		47 			// White
	};

	char Data[HEIGHT][WIDTH];
	char PreviousData[HEIGHT][WIDTH];

	void ResetColor();
	void SetColor(int color);
	void MoveCursor(int y, int x);
	void Clear();
	void DrawPixel(int x, int y);
	void CopyGridToPrevious();
protected:
	int CurrentColor = -1;
public:
	Grid();
	~Grid();
	void Draw();
	void PlotPoint(int x, int y, int c);
};

#endif // GRID_HPP
