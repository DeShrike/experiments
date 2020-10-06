#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "board.hpp"
#include "player.hpp"
#include "keyboard.hpp"

class Human : public Player
{
protected:
	Keyboard *keyboard;
public:
	Human();
	~Human();
	int GetNextMove(Board *board);
};

#endif // HUMAN_HPP
