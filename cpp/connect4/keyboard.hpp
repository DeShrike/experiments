#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <termios.h>
#include "keyboard.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

class Keyboard
{
private:
	struct termios t;
	void Disable();
	void Enable();
public:
	Keyboard();
	int GetKey();
};

#endif // KEYBOARD_HPP
