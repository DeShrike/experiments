#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

class Player
{
public:
	Player();
	int GetNextMove(Board *board);
};

#endif // PLAYER_HPP
