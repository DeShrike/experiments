#ifndef BOARD_HPP
#define BOARD_HPP

#include "grid.hpp"

#define ROWS 	         6
#define COLUMNS          7

class Board
{
private:
	int Data[ROWS][COLUMNS];

	int fallingPlayer;		// if 0 then no peg is falling
	int fallingColumn;
	int fallingProgress;

	int selectingPlayer;	// if 0 then no peg is selecting
	int selectingColumn;
protected:
	Grid *grid;
public:
	Board(Grid *grid);
	void Draw();
	int Winner();
	void DoMove(int move);
	void SetPeg(int column, int row, int player);
};

#endif // BOARD_HPP
