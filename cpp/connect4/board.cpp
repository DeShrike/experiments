#include "board.hpp"
#include "grid.hpp"

#define BLOCKWIDTH       4

#define BOARDCOLOR	     4
#define PLAYER1COLOR     1
#define PLAYER2COLOR     3

Board::Board(Grid *grid)
{
	this->grid = grid;

	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLUMNS; x++)
		{
			this->Data[y][x] = 0;			
		}
	}
}

void Board::SetPeg(int column, int row, int player)
{
	if (column < 0 || column >= COLUMNS)
	{
		return;
	}

	if (row < 0 || row >= ROWS)
	{
		return;
	}

	this->Data[row][column] = player;
}

void Board::Draw()
{
	int topsize = COLUMNS * (BLOCKWIDTH + 1) + 1;
	int y = 1;
	for (int x = 1; x <= topsize; x++)
	{
		this->grid->PlotPoint(x, y, BOARDCOLOR);
	}

	y++;
	for (int row = 0; row < ROWS; row++, y += 3)
	{
		int x = 1;
		for (int col = 0; col < COLUMNS; col++, x += BLOCKWIDTH + 1)
		{
			this->grid->PlotPoint(x, y, BOARDCOLOR);
			for (int bw = 1; bw <= BLOCKWIDTH; bw++)
			{
				this->grid->PlotPoint(x + bw, y, PLAYER1COLOR);
			}

			this->grid->PlotPoint(x, y + 1, BOARDCOLOR);
			for (int bw = 1; bw <= BLOCKWIDTH; bw++)
			{
				this->grid->PlotPoint(x + bw, y + 1, PLAYER1COLOR);
			}
		}

		for (int x = 1; x <= topsize; x++)
		{
			this->grid->PlotPoint(x, y + 2, BOARDCOLOR);
		}

		this->grid->PlotPoint(x, y, BOARDCOLOR);
		this->grid->PlotPoint(x, y + 1, BOARDCOLOR);
	}

	this->grid->Draw();
}

void Board::DoMove(int move)
{

}

int Board::Winner()
{
	return 0;
}
