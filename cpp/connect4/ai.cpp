#include "player.hpp"
#include "ai.hpp"

Ai::Ai(int smartness)
{
	this->smartness = smartness;
}

int Ai::GetNextMove(Board *board)
{
	return 0;
}
