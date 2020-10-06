#ifndef AI_HPP
#define AI_HPP

#include "board.hpp"
#include "player.hpp"

class Ai : public Player
{
protected:
	int smartness;
public:
	Ai(int smartness);
	int GetNextMove(Board *board);
};

#endif // AI_HPP
