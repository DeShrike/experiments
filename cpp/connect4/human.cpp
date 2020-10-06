#include "player.hpp"
#include "human.hpp"
#include "keyboard.hpp"

Human::Human()
{
	this->keyboard = new Keyboard();
}

Human::~Human()
{
	delete this->keyboard;
}

int Human::GetNextMove(Board *board)
{
	return 0;
}
